#include "graph.h"



Graph::Graph() {
    readFromFile();
}

string Graph::decodeHTTP(string title) {
    static unordered_map<string, string> decoded {
        {"%28", "("},
        {"%29", ")"},
        {"%27", "'"},
        {"%2C", ","},
        {"%C3%81", "Á"},
        {"%C3%A1", "á"}, 
        {"%C3%85", "Å"},
        {"%C3%89", "É"},
        {"%C3%93", "Ó"},
        {"%E2%82%AC", "€"},
        {"%26", "&"},   
        {"%C3%BC", "ü"},
        {"%C3%A9", "é"},
        {"%C3%AD", "í"},
        {"%C5%99", "ř"},
        {"%C3%B3", "ó"},
        {"%C3%B6", "ö"},
        {"%C3%B8", "ø"},
        {"%C3%B4", "ô"},
        {"%C3%BA", "ú"},
        {"%C3%B1", "ñ"},
        {"%C3%A6", "æ"},
        {"%C3%A4", "ä"},
        {"%E2%80%93", "-"}, // –
        {"%C5%A1","š"},
        {"%C4%8D","č"},
        {"%C4%87", "ć"},
        {"%C5%82", "ł"},
        {"%C4%AB", "ī"},
        {"%2A", "*"},
        {"%C5%8D", "ō"},
        {"%C4%83", "ă"},
        {"%C3%B2", "ò"},
        {"%C3%A3", "ã"},
        {"%C3%A5", "å"},
        {"%21", "!"}
    };
    string toReturn = "";
    for (unsigned i = 0; i < title.length(); i++) {
        if (title.substr(i, 2) == "__") {
            toReturn += ": ";
            i++;
            continue;
        } else if (title.at(i) == '_') {
            toReturn += " ";
            continue;
        } else {
            string threeChar = title.substr(i, 3);
            string sixChar = title.substr(i, 6);
            string nineChar = title.substr(i, 9);
            for (auto entry : decoded) {
                if (threeChar == entry.first) {
                    toReturn += entry.second;
                    i += 3;
                    break;
                } else if (sixChar == entry.first) {
                    toReturn += entry.second;
                    i += 6;
                    break;
                } else if (nineChar == entry.first) {
                    toReturn += entry.second;
                    i += 9;
                    break;
                }
            }
        }
        if (i >= title.length()) {
            break;
        }
        if (title.at(i) != '\n' && title.at(i) != '\t' && title.at(i) != '\r') {
            toReturn += title.at(i);
        }
    }
    return toReturn;
}

void Graph::readFromFile() {
    ifstream ifs("/workspaces/cs225/Final-Project/data/articles.tsv");
    for (string line; getline(ifs, line); line = "") { //populate nodeList_ with each article
        if (line.substr(0, 1) == "#") { // skip heading information
            continue;
        }
        if (converted.find(line) != converted.end()) {
            nodeList_.push_back(new Node(converted[line]));
        } else {
            string toAdd = decodeHTTP(line);
            converted[line] = toAdd;
            nodeList_.push_back(new Node(toAdd));
        }
        
    }
    ifstream ifs2("/workspaces/cs225/Final-Project/data/links.tsv");
    int idx = -1;
    string first = ""; //variables to avoid looping through nodeList
    for (string line; getline(ifs2, line); line = "") { // create an unweighted, directed edge between every article that has a link
        if (line.substr(0, 1) == "#") { // skip heading information
            continue;
        }
        string article;
        string link;
        //split tsv line into the article and the link
        if (converted.find(line.substr(0, line.find("\t"))) != converted.end()) {
            article = converted[line.substr(0, line.find("\t"))];
        } else {
            article = decodeHTTP(line.substr(0, line.find("\t")));
            converted[line.substr(0, line.find("\t"))] = article;
        }
        if (converted.find(line.substr(line.find("\t") + 1, line.length())) != converted.end()) {
            link = converted[line.substr(line.find("\t") + 1, line.length())];
        } else {
            link = decodeHTTP(line.substr(line.find("\t") + 1, line.length()));
            converted[line.substr(0, line.find("\t"))] = link;
        }
        
        while (first != article) { //checks to see if the article has changed yet
            idx++;
            first = nodeList_[idx]->data;
        }
        Node* v2 = nullptr;
        for (unsigned i = 0; i < nodeList_.size(); i++) {
            if (link == nodeList_[i]->data) {
                v2 = nodeList_[i];
                break;
            }
        }
        insertEdge(nodeList_[idx], v2);
        nodeList_[idx]->degree++;
    }
    for (unsigned i = 0; i < nodeList_.size(); i++) { //give each edge the proper weight
        Node node = *nodeList_[i];
        for (unsigned j = 0; j < nodeList_[i]->adjList.size(); j++) {
            nodeList_[i]->adjList[j].first += node.degree;
            nodeList_[i]->adjList[j].first += getNodeDegree(nodeList_[i]->adjList[j].second);
            Node* otherNode = getNode(nodeList_[i]->adjList[j].second->data);
            insertEdge(otherNode, nodeList_[i], nodeList_[i]->adjList[j].first);
        }
    }
}

void Graph::insertEdge(Node* v1, Node* v2) {
    v1->adjList.push_back(pair(0, v2));
}

void Graph::insertEdge(Node* v1, Node* v2, int weight) {
    if (areAdjacent(v1, v2)) {
        return;
    }
    v1->adjList.push_back(pair(weight, v2));
}

bool Graph::areAdjacent(Node* v1, Node* v2) {
    for (unsigned i = 0; i < v1->adjList.size(); i++) {
        if ((v1->adjList[i].second->data) == v2->data) {
            return true;
        }
    }
    return false;
}

vector<string> Graph::incidentEdges(Node* v) {
    vector<string> toReturn;
    for (unsigned i = 0; i < v->adjList.size(); i++) {
        toReturn.push_back(v->adjList[i].second->data);
    }
    return toReturn;
}

int Graph::getNodeDegree(Node* v) {
    for (unsigned i = 0; i < nodeList_.size(); i++) {
        if (nodeList_[i] == v) {
            return v->degree;
        }
    }
    return 999999999;
}

int Graph::getNodeListSize() {
    return nodeList_.size();
}

Graph::Node* Graph::getNode(string article) {
    for (unsigned i = 0; i < nodeList_.size(); i++) {
        if (nodeList_[i]->data == article) {
            return nodeList_[i];
        }
    }
    return nullptr;
}

void Graph::removeVertex(Node* v) {
    for (unsigned i = 0; i < nodeList_.size(); i++) {
        if (nodeList_[i]->data == v->data) {
            nodeList_.erase(nodeList_.begin() + i);
            i--;
            continue;
        }
        for (unsigned j = 0; j < nodeList_[i]->adjList.size(); j++) {
            if (nodeList_[i]->adjList[j].second->data == v->data) {
                nodeList_[i]->adjList.erase(nodeList_[i]->adjList.begin() + j);
                break;
            }
        }
    }
    delete v;
}

Graph::~Graph() {
    clear();
}

Graph::Graph(const Graph& other) {
    copy(other);
}

Graph& Graph::operator=(const Graph& other) {
    clear();
    copy(other);
    return *this;
}

void Graph::clear() {
    for (unsigned i = 0; i < nodeList_.size(); i++) {
        delete nodeList_[i];
    }
    
}



void Graph::copy(const Graph& other) {
    for (unsigned i = 0; i < other.nodeList_.size(); i++) {
        nodeList_.push_back(new Node(other.nodeList_[i]->data));
    }
    for (unsigned i = 0; i < other.nodeList_.size(); i++) {
        for (unsigned j = 0; j < other.nodeList_[i]->adjList.size(); j++) {
            insertEdge(nodeList_[i], getNode(other.nodeList_[i]->adjList[j].second->data), other.nodeList_[i]->adjList[j].first);
        }
    }
}

vector<Graph::Node*> Graph::BFS(Graph::Node* start) {
    queue<Graph::Node*> queue;
    vector<Graph::Node*> output;
    set<Graph::Node*> visited;
    Graph::Node* current;
    queue.push(start);
    visited.insert(start);
    
    while (!(queue.empty())) {
        current = queue.front();
        queue.pop();
        output.push_back(current);

        //visit all adjacent nodes:
        for (pair<int, Graph::Node*> adjacent_edge : current -> adjList) {
            Graph::Node* adjacent_node = adjacent_edge.second;
            if (visited.count(adjacent_node) == 0) { //if the node hasnt been visited
                queue.push(adjacent_node);
                visited.insert(adjacent_node);
            } 
        }
    }
    return output;
}

Animation Graph::visualizeBFS() {
    PNG* image = new PNG(size,size);
    Node* node = getNode("Zulu");
    
    std::vector<Node*> bfs = BFS(node); //size:4056

    //draws all the nodes on the base image
    for (size_t i = 0; i < iter_limit; i++) {
        drawNode(bfs[i],image);
    }
    
    //adds the first node to the traversal:
    int r = node -> degree/6;
    for (int y =- r; y <= r; y++) {
        for (int x = -r; x<= r; x++) {
            if (x * x + y * y <= r * r) traversal.push_back(make_tuple(Point(node->coord.first + x, node->coord.second + y), 1, node -> degree, node -> coord)); 
        }
    }

    //adds all the edges to the traversal
    for (size_t i = 0; i < iter_limit; i++) {
        drawEdge(bfs[i], bfs[i+1]);
    }

    //animate the image:
    Animation animation = Animate(frameRate, image);
    return animation;
}

Animation Graph::visualizeDijkstras() {
    PNG* image = new PNG(size, size); 
    Node* start = nodeList_[0]; 
    Node* end = nodeList_[100];

    std::vector<Node*> dijkstra = dijkstrasVector(start,end); //size:4056
    //draws all the nodes on the base image
    for (size_t i = 0; i < 100; i++) {
        drawNode(nodeList_[i],image);
    }
    
    //adds the first node to the traversal:
    int r = start -> degree/6;
    for (int y =- r; y <= r; y++) {
        for (int x = -r; x<= r; x++) {
            if (x * x + y * y <= r * r) traversal.push_back(make_tuple(Point(start->coord.first + x, start->coord.second + y), 1, start -> degree, start -> coord)); 
        }
    }

    //draws all adjacent edges
    for (size_t i = 0; i < 100; i++) {
        Node* node = nodeList_[i];
        for (pair<int, Node*> adjacent : node -> adjList) {
            if (node -> drawn.count(adjacent.second) == 0) {
                drawEdge(node, adjacent.second);
                node -> drawn.insert(adjacent.second);
                adjacent.second -> drawn.insert(node);
            }
        }
    }

    //draw the base image with all coloring:
    drawDijkstra(image);
    //Clear our current traversal vector
    traversal.clear();

    for (size_t i = 0; i < dijkstra.size() - 1; i++) {
        drawEdge(dijkstra[i], dijkstra[i+1]);
    }

    Animation animation = Animate(frameRate, image);
    return animation;
}


void Graph::drawEdge(Node* node1, Node* node2) { //PNG* image
    //Just to make sure we're not drawing an edge between two nodes that haven't been drawn yet:
    if (node1 -> coord.first == 0 || node2 -> coord.first == 0) {
        return;
    }

    int x1 = node1 -> coord.first;
    int y1 = node1 -> coord.second;
    int x2 = node2 -> coord.first;
    int y2 = node2 -> coord.second;

    int dx = x2 - x1;
    int dy = y2 - y1;

    double steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    double Xincrement = dx / steps;
    double Yincrement = dy / steps;

    double X = x1;
    double Y = y1;

    int i = 1;
    while (i  <= steps) {
        traversal.push_back(make_tuple(Point(floor(X), floor(Y)),0,0, make_pair(0,0)));
        X += Xincrement;
        Y += Yincrement;
        i++;
    }

    int r = node2->degree/6;
    for (int y =- r; y <= r; y++) {
        for (int x = -r; x<= r; x++) {
            if (x * x + y * y <= r * r) traversal.push_back(make_tuple(Point(x2 + x, y2 + y),1, r, node2 -> coord)); 
        }
    }
    
}


Animation Graph::Animate(unsigned frameInterval, PNG* image) {
    Animation animation;
    animation.addFrame(*image);
    unsigned int frame_counter = 0;

    for (tuple<Point,int,int, pair<int,int>> tuple : traversal) {
        HSLAPixel& pixel = image->getPixel(get<0>(tuple).x,get<0>(tuple).y); 
        if (get<1>(tuple) == 0) { // if we're coloring in an edge
            SolidColorPicker color = SolidColorPicker(HSLAPixel(100,1,0.5,1));
            pixel = color.getColor(get<0>(tuple).x,get<0>(tuple).y);  // fill pixel
        } else { // if we're coloring in a node
            GradientColorPicker color = GradientColorPicker(HSLAPixel(0,1,0.5,1), HSLAPixel(50,1,0.5,1), Point(get<3>(tuple).first, get<3>(tuple).second), (get<2>(tuple)));
            pixel = color.getColor(get<0>(tuple).x,get<0>(tuple).y);  // fill pixel
        }
        frame_counter++;
        if (frameInterval == frame_counter) {
            animation.addFrame(*image);
            frame_counter = 0;
        } 
    }
    if (*image != animation.getFrame(animation.frameCount() - 1)) {
        animation.addFrame(*image);
    }
    return animation;
}

void Graph::drawDijkstra(PNG* image) {
    for (tuple<Point,int,int, pair<int,int>> tuple : traversal) {
        HSLAPixel& pixel = image->getPixel(get<0>(tuple).x,get<0>(tuple).y); 
        if (get<1>(tuple) == 0) { // if we're coloring in an edge
            SolidColorPicker color = SolidColorPicker(HSLAPixel(100,1,0.5,1));
            pixel = color.getColor(get<0>(tuple).x,get<0>(tuple).y);  // fill pixel
        } else { // if we're coloring in a node
            GradientColorPicker color = GradientColorPicker(HSLAPixel(0,1,0.5,1), HSLAPixel(50,1,0.5,1), Point(get<3>(tuple).first, get<3>(tuple).second), (get<2>(tuple)));
            pixel = color.getColor(get<0>(tuple).x,get<0>(tuple).y);  // fill pixel
        }
    }
}

int Graph::stoerWagnerHelper(vector<Graph::Node*> otherNodes, Node*& s, Node*& t) { //finds the minimum cut to make two seperate connected components
    vector<Node*> superNode;
    superNode.push_back(otherNodes[0]);
    int cutWeight;

<<<<<<< HEAD
int Graph::dijkstrasAlgorithm(Node* start,Node* end) {
    // weight, data
    priority_queue<pair<int,string>> pq;
    // data:distance from start
    unordered_map<string, int> dist;
    string start_string = start->data;
    dist[start_string]=0;
    pq.push(make_pair(0,start_string));
    while(!pq.empty()) {
        string prev_data = pq.top().second;
        pq.pop();
        Graph::Node* node = getNode(prev_data);
        // for all adjecent edges, update weight
        for (pair<int, Graph::Node*> ae : node -> adjList) {
            int weight = ae.first;
            Graph::Node* adj_node = ae.second;
            string curr_data = adj_node->data;
            // if data not in dist map means curr val = INF 
            // so new val will always be lower than INF
            if (dist.find(curr_data) == dist.end() || dist[curr_data]>dist[prev_data]+weight) {
                dist[curr_data] = dist[prev_data]+weight;
                pq.push(make_pair(dist[curr_data], curr_data));
            }        
        }
    }
    string end_s = end->data;
    // did not reach the end node, graph has more than one conected components
    if (dist.find(end_s) == dist.end()) return INT_MAX;
    return dist[end_s];
}

int Graph::dijkstras(Node* start,Node* end) {
    // weight, data
    priority_queue<pair<int,string>> pq;
    // data:distance from start
    unordered_map<string, int> dist;
    dist[start -> data]=0;
    pq.push(make_pair(0,start -> data));
    while(!pq.empty()) {
        string prev_data = pq.top().second;
        pq.pop();
        
        for (pair<int, Node*> ae : getNode(prev_data) -> adjList) {
            int weight = ae.first;
            string curr_data = ae.second -> data;

            if (dist.find(curr_data) == dist.end() || dist[curr_data]>dist[prev_data]+weight) {
                dist[curr_data] = dist[prev_data]+weight;
                pq.push(make_pair(dist[curr_data], curr_data));
            }        
        }
    }
    if (dist.find(end -> data) == dist.end()) return INT_MAX;
    return dist[end -> data];
}
=======
    /*loops through every node and adds the one that has the hightest total weight to all of 
    the nodes already in the vector (represents the nodes inside it merged together).
    Takes the node with the largest weight between it and all of the nodes that are already
    in the merged node. The last two nodes found will be the ones with the cut
    */
    while (!otherNodes.empty()) { 
        Node* maxVertex;
        int maxWeight = -1;
        for (Node* node : otherNodes) {
            int weight = 0; // initializes the edge weight between this node and the super node
            for (Node* foundNode : superNode) {
                for (auto i : node->adjList) {
                    if (i.second->data == foundNode->data) {
                        weight += i.first; // adds the weight of each edge going to this node from the super node
                        break;
                    }
                }
            }
            if (weight > maxWeight) { // if this is the largest weight so far, records the weight and which node it's from
                maxVertex = node;
                maxWeight = weight;
            }
        }
        for (unsigned i = 0; i < otherNodes.size(); i++) {
            if (otherNodes[i]->data == maxVertex->data) {
                otherNodes.erase(otherNodes.begin() + i); // removes the node from the set of nodes to check and adds it into the super node
            }
        }
        superNode.push_back(maxVertex);
        cutWeight = maxWeight;
    }
>>>>>>> c7c6bd7551709b558957f99f712d7a62473f9eb2

    s = superNode[superNode.size() - 2]; 
    t = superNode[superNode.size() - 1];

<<<<<<< HEAD
//Dijkstras' Algorithm but it returns the path taken for shortest path
vector<Graph::Node*> Graph::dijkstrasVector(Node* start, Node* end) {
    // weight, data
    priority_queue<pair<int,string>> pq;
    // data:distance from start
    unordered_map<string, int> dist;
    vector<Node*> previous;
    unordered_map<Node*, Node*> prev;
    prev[start] = NULL;
    string start_string = start->data;
    dist[start_string]=0;
    pq.push(make_pair(0,start_string));
    while(!pq.empty()) {
        string prev_data = pq.top().second;
        pq.pop();
        Graph::Node* node = getNode(prev_data);
        // for all adjecent edges, update weight
        for (pair<int, Graph::Node*> ae : node -> adjList) {
            int weight = ae.first;
            Graph::Node* adj_node = ae.second;
            string curr_data = adj_node->data;
            // if data not in dist map means curr val = INF 
            // so new val will always be lower than INF
            if (dist.find(curr_data) == dist.end() || dist[curr_data]>dist[prev_data]+weight) {
                dist[curr_data] = dist[prev_data]+weight;
                prev[getNode(curr_data)] = getNode(prev_data);
                pq.push(make_pair(dist[curr_data], curr_data));
            }        
        }
    }

    //Trace backwards through the map to find shortest path
    Node* looper = end;
    while (prev[looper] != NULL) {
        previous.insert(previous.begin(), looper);
        looper = prev[looper]; 
    }
    previous.insert(previous.begin(), looper);
    return previous;
}

int Graph::stoerWagnerHelper(vector<Graph::Node*> otherNodes, Node*& s, Node*& t) { //finds the minimum cut to make two seperate connected components
    vector<Node*> superNode;
    superNode.push_back(otherNodes[0]);
    otherNodes.erase(otherNodes.begin());
    int cutWeight;
    vector<pair<int, Node*>> superAdj;
    superAdj = superNode[0]->adjList;
    /*loops through every node and adds the one that has the hightest total weight to all of 
    the nodes already in the vector (represents the nodes inside it merged together).
    Takes the node with the largest weight between it and all of the nodes that are already
    in the merged node. The last two nodes found will be the ones with the cut
    */
    while (!otherNodes.empty()) { 
        cout << otherNodes.size() << endl;
        Node* maxVertex;
        int maxWeight = -1;
        for (Node* node : otherNodes) {
            int weight = 0; // initializes the edge weight between this node and the super node
            /*for (Node* foundNode : superNode) {
                for (auto i : node->adjList) {
                    if (i.second->data == foundNode->data) {
                        weight += i.first; // adds the weight of each edge going to this node from the super node
                        break;
                    }
                }
            } */
            for (unsigned i = 0; i < superAdj.size(); i++) {
                if (superAdj[i].second->data == node->data) {
                    weight = superAdj[i].first;
                }
            }
            if (weight > maxWeight) { // if this is the largest weight so far, records the weight and which node it's from
                maxVertex = node;
                maxWeight = weight;
            }
        }
        for (unsigned i = 0; i < otherNodes.size(); i++) {
            if (otherNodes[i]->data == maxVertex->data) {
                otherNodes.erase(otherNodes.begin() + i); // removes the node from the set of nodes to check and adds it into the super node
                break;
            }
        }
        superNode.push_back(maxVertex);
        for (unsigned i = 0; i < maxVertex->adjList.size(); i++) {
            bool added = false;
            for (unsigned j = 0; j < superAdj.size(); j++) {
                if (maxVertex->adjList[i].second == superAdj[j].second) {
                    superAdj[j].first += maxVertex->adjList[i].first;
                    added = true;
                    break;
                }
            }
            if (!added) {
                superAdj.push_back(maxVertex->adjList[i]);
            }
        }
        cutWeight = maxWeight;
    }

    s = superNode[superNode.size() - 2]; 
    t = superNode[superNode.size() - 1];

    return cutWeight;
}

vector<pair<string, string>> Graph::stoerWagner(Node* startNode) { // retruns vector of edges in mincut
    Graph g = Graph(*this); // copy constructing graph to use algorithm so others can be used afterwards
    set<Node*> tempPartition;
    set<Node*> partition; // set of nodes in the partition;
    vector<Node*> nodes = g.BFS(startNode);
    int minWeight = INT_MAX;
    while (nodes.size() > 1) {
        Node* s = nullptr;
        Node* t = nullptr;
        int cutWeight = g.stoerWagnerHelper(nodes, s, t);
        if (cutWeight < minWeight) {
            minWeight = cutWeight;
            partition = tempPartition;
            partition.insert(t);
        }
        tempPartition.insert(t);
        Node* mergedNode = g.mergeNodes(s, t);
        nodes.push_back(mergedNode);
        for (unsigned i = 0; i < nodes.size(); i++) {
            if (nodes[i]->data == s->data || nodes[i]->data == t->data) {
                nodes.erase(nodes.begin() + i);
                i--;
            }
        }
    }

    for (Node* node : nodes) { //memory cleanup
        if (node->data.substr(0, 6) == "Merged") {
            delete node;
        }
    }
    vector<pair<string, string>> cutEdges;
    for (Node* node : partition) {
        if (node->data.substr(0,6) == "Merged") {
            continue;
        }
        for (auto entry : node->adjList) {
            if (entry.second->data.substr(0,6) == "Merged") {
                continue;
            }
            if (partition.find(entry.second) == partition.end()) {
                cutEdges.push_back(pair(node->data, entry.second->data));
            }
        }
    }
    return cutEdges;
=======
    return cutWeight;
}

vector<pair<string, string>> Graph::stoerWagner(Node* startNode) { // retruns vector of edges in mincut
    Graph g = Graph(*this); // copy constructing graph to use algorithm so others can be used afterwards
    set<Node*> tempPartition;
    set<Node*> partition; // set of nodes in the partition;
    vector<Node*> nodes = g.BFS(startNode);
    int minWeight = INT_MAX;
    while (nodes.size() > 1) {
        Node* s = nullptr;
        Node* t = nullptr;
        int cutWeight = g.stoerWagnerHelper(nodes, s, t);
        if (cutWeight < minWeight) {
            minWeight = cutWeight;
            partition = tempPartition;
            partition.insert(t);
        }
        tempPartition.insert(t);
        Node* mergedNode = g.mergeNodes(s, t);
        nodes.push_back(mergedNode);
        int erased = 0;
        for (unsigned i = 0; i < nodes.size(); i++) {
            if (nodes[i]->data == s->data || nodes[i]->data == t->data) {
                nodes.erase(nodes.begin() + i);
                erased++;
                i--;
            }
        }
    }

    for (Node* node : nodes) { //memory cleanup
        if (node->data.substr(0, 6) == "Merged") {
            delete node;
        }
    }
    vector<pair<string, string>> cutEdges;
    for (Node* node : partition) {
        for (auto entry : node->adjList) {
            if (partition.find(entry.second) == partition.end()) {
                cutEdges.push_back(pair(node->data, entry.second->data));
            }
        }
    }
    return cutEdges;
}

Graph::Node* Graph::mergeNodes(Node* node1, Node* node2) {
    Node* toReturn = new Node("Merged" + node1->data + node2->data);
    for (unsigned i = 0; i < node1->adjList.size(); i++) { // adds edges from node 1 to first node
        if (node1->adjList[i].second->data == node2->data) {
            continue; // skips node2 so that there isn't an edge between the merged node and one of the nodes in it
        }
        toReturn->adjList.push_back(node1->adjList[i]);
    }

    for (unsigned i = 0; i < node2->adjList.size(); i++) {
        if (node2->adjList[i].second->data == node1->data) {
            continue; // skips node1
        }
        bool added = false;
        for (unsigned j = 0; j < toReturn->adjList.size(); j++) {
            if (toReturn->adjList[j].second->data == node2->adjList[i].second->data) { //adds weight to edge if present from node1
                toReturn->adjList[j].first += node2->adjList[j].first;
                added = true;
                break;
            }
        }
        if (!added) {
            toReturn->adjList.push_back(node2->adjList[i]);
        }
    }

    for (unsigned i = 0; i < toReturn->adjList.size(); i++) {
        Node* toModify = getNode(toReturn->adjList[i].second->data);
        for (auto entry : toModify->adjList) { // changes any edges in other node to be the new merged node
            if (entry.second->data == node1->data || entry.second->data == node2->data) {
                entry.second = toReturn;
                entry.first = toReturn->adjList[i].first;
                break;
            }
            // may end up with two edges with equal weight pointing to the new merged node but for the purpose of this algorithm that is fine
        }
    }
    return toReturn;
>>>>>>> c7c6bd7551709b558957f99f712d7a62473f9eb2
}

Graph::Node* Graph::mergeNodes(Node* node1, Node* node2) {
    Node* toReturn = new Node("Merged" + node1->data + node2->data);
    for (unsigned i = 0; i < node1->adjList.size(); i++) { // adds edges from node 1 to first node
        if (node1->adjList[i].second->data == node2->data) {
            continue; // skips node2 so that there isn't an edge between the merged node and one of the nodes in it
        }
        toReturn->adjList.push_back(node1->adjList[i]);
    }

    for (unsigned i = 0; i < node2->adjList.size(); i++) {
        if (node2->adjList[i].second->data == node1->data) {
            continue; // skips node1
        }
        bool added = false;
        for (unsigned j = 0; j < toReturn->adjList.size(); j++) {
            if (toReturn->adjList[j].second->data == node2->adjList[i].second->data) { //adds weight to edge if present from node1
                toReturn->adjList[j].first += node2->adjList[j].first;
                added = true;
                break;
            }
        }
        if (!added) {
            toReturn->adjList.push_back(node2->adjList[i]);
        }
    }

    for (unsigned i = 0; i < toReturn->adjList.size(); i++) {
        Node* toModify = getNode(toReturn->adjList[i].second->data);
        for (auto entry : toModify->adjList) { // changes any edges in other node to be the new merged node
            if (entry.second->data == node1->data || entry.second->data == node2->data) {
                entry.second = toReturn;
                entry.first = toReturn->adjList[i].first;
                break;
            }
            // may end up with two edges with equal weight pointing to the new merged node but for the purpose of this algorithm that is fine
        }
    }
    return toReturn;
}

void Graph::drawNode(Node* node, PNG* image) {
    int radius = node -> degree/6;   
    int center_x = (rand() % (size - 2*radius)) + radius;
    int center_y = (rand() % (size - 2*radius)) + radius;

    int x = 0; 
    while (collision(center_x, center_y, radius)) {
        // cout << "Dealing with collision... " << "#" << x << endl;
        x++;
        if (x > 10000)  {
            cout << "UNABLE TO RESOLVE COLLISION!!!!" << endl;
            break;
        }
        center_x = rand() % (size - 2 * radius) + radius;
        center_y = rand() % (size - 2 * radius) + radius;
        
    }

    coord_list.push_back(make_tuple(center_x, center_y, radius));

    node -> coord = make_pair(center_x,center_y);
    //this code draws the circle
    for (int i = 0; i <= radius; i++) { // i = x
        int y = sqrt(pow(radius,2) - pow(i,2));
        image -> getPixel(center_x + i, center_y + y).l = 0;
        image -> getPixel(center_x + i, center_y - y).l = 0;
        image -> getPixel(center_x - i, center_y + y).l = 0;
        image -> getPixel(center_x - i, center_y - y).l = 0;
    }
    
}

bool Graph::collision(int x, int y, int r) {
    if (coord_list.size() == 0) return false; 

    for (size_t i = 0; i < coord_list.size(); i++) {
        int x2 = get<0>(coord_list[i]); 
        int y2 = get<1>(coord_list[i]); 
        int r2 = get<2>(coord_list[i]); 
        if (((x - x2) * (x - x2) + (y - y2) * (y - y2)) < ((r + r2) * (r + r2))) {
            return true; 
        }
    }

    return false; 
}

// Node* node = bfs[i];
        // for (size_t k = 0; k < node -> adjList.size(); k++) {
        //     Node* adjacent = node -> adjList[k].second;
        //     if (node -> drawn.count(adjacent) == 0) {
        //         drawEdge(node, node -> adjList[k].second, image);
        //         node -> drawn.insert(adjacent);
        //         adjacent -> drawn.insert(node);
        //     } 
        // }

PNG* Graph::drawBase() {
    int num_nodes = nodeList_.size(); //Approx 4,500 nodes
    PNG* image = new PNG(size,size);

    for (int i = 0; i < num_nodes; i++) {
        Node* node = nodeList_[i];
        drawNode(node, image);
    }
    return image;
}

<<<<<<< HEAD
=======


// Animation Graph::visualizeBFS(PNG* picture) {
//     PNG* image = picture;
//     Node* node = getNode("Global city");
//     std::vector<Node*> bfs = BFS(node); //size:4056
//     // for (size_t i = 0; i < bfs.size(); i++) {
//     //     drawNode(bfs[i], );
//     // }
    
//     // for (int y =- r; y <= r; y++) {
//     //     for (int x = -r; x<= r; x++) {
//     //         if (x * x + y * y <= r * r) traversal.push_back(Point(node->coord.first + x, node->coord.second + y)); 
//     //     }
//     // }

//     // for (size_t i = 0; i < 25; i++) {
//     //     drawEdge(bfs[i], bfs[i+1]);
//     // }
//     RainbowColorPicker picker(10);
//     Animation animation = Animate(400, image, picker);
//     return animation;
// }


// void Graph::populateCoords(Node* node) {
//     int radius = (node -> degree)/4;
//     int center_x = rand() % (size - 2*radius) + radius;
//     int center_y = rand() % (size - 2*radius) + radius;
//     node -> coord = make_pair(center_x,center_y);
//     for (int i = 0; i <= radius; i++) { // i = x
//         int y = sqrt(pow(radius,2) - pow(i,2));
//         // image -> getPixel(center_x + i, center_y + y).l = 0;
//         traversal.push_back(Point(center_x + i, center_y + y));
//         // image -> getPixel(center_x + i, center_y - y).l = 0;
//         traversal.push_back(Point(center_x + i, center_y - y));
//         // image -> getPixel(center_x - i, center_y + y).l = 0;
//         traversal.push_back(Point(center_x - i, center_y + y));
//         // image -> getPixel(center_x - i, center_y - y).l = 0;
//         traversal.push_back(Point(center_x - i, center_y - y));
//     }
// }

// Graph::Node* Graph::connectedComponents() {
//     map<Node*, bool> visited_list;

//     for (size_t i = 0;i < nodeList_.size(); i++) {
//         visited_list.insert(make_pair(nodeList_[i], false)); 
//     }

//     Node* n = getNode("Global city"); 
//     vector<Node*> bfs = BFS(n);

//     for (size_t i = 0; i < bfs.size(); i++) {
//         visited_list[bfs[i]] = true;
//     }

//     for (auto pair : visited_list) {
//         if (pair.second == false) {
//             if (BFS(pair.first).size() > 2) return pair.first;
//         }
//     }

//     return NULL;

// }

>>>>>>> c7c6bd7551709b558957f99f712d7a62473f9eb2
vector<pair<Graph::Node*, int>> Graph::connectedComponents() {
    map<Node*, bool> visited_list;

    for (size_t i = 0;i < nodeList_.size(); i++) {
        visited_list.insert({nodeList_[i], false}); 
    }

    Node* n = getNode("Global city"); 
    vector<Node*> bfs = BFS(n);

    for (size_t i = 0; i < bfs.size(); i++) {
        visited_list[bfs[i]] = true;
    }


    std::vector<pair<Node*, int>> output; 
    for (auto pair : visited_list) {
        if (pair.second == false) {
            int size = BFS(pair.first).size();
            if (size > 3) {
                output.push_back(make_pair(pair.first, size));
            }
        }
    }

    return output;
 

}
<<<<<<< HEAD

// Given that every node is a square, how many can we fit? Upper bound calcuation 
int Graph::calculateVisualizationNodeCount() {
    Node* node = getNode("Global city");

    vector<Node*> bfs = BFS(node);

    int area = size * size; 
    int counter = 0;
    int sum = 0;
    for (size_t i = 0; i < bfs.size(); i++) {
        int w = bfs[i] -> degree / 6 + 10; 
        sum += w * w;
        if (sum < area) {
            counter++;
        } else {
            return counter; 
        }
    }

    return counter; 
}
=======
int Graph::dijkstras(string start,string end, unordered_map<string, vector<pair<int, string>>> adj) {
    // weight, data
    priority_queue<pair<int,string>> pq;
    // data:distance from start
    unordered_map<string, int> dist;
    dist[start]=0;
    pq.push(make_pair(0,start));
    while(!pq.empty()) {
        string prev_data = pq.top().second;
        pq.pop();
        
        for (pair<int, string> ae : adj[prev_data]) {
            int weight = ae.first;
            string curr_data = ae.second;

            if (dist.find(curr_data) == dist.end() || dist[curr_data]>dist[prev_data]+weight) {
                dist[curr_data] = dist[prev_data]+weight;
                pq.push(make_pair(dist[curr_data], curr_data));
            }        
        }
    }
    if (dist.find(end) == dist.end()) return INT_MAX;
    return dist[end];
}

int Graph::dijkstrasAlgorithm(Node* start,Node* end) {
    // weight, data
    priority_queue<pair<int,string>> pq;
    // data:distance from start
    unordered_map<string, int> dist;
    string start_string = start->data;
    dist[start_string]=0;
    pq.push(make_pair(0,start_string));
    while(!pq.empty()) {
        string prev_data = pq.top().second;
        pq.pop();
        Graph::Node* node = getNode(prev_data);
        // for all adjecent edges, update weight
        for (pair<int, Graph::Node*> ae : node -> adjList) {
            int weight = ae.first;
            Graph::Node* adj_node = ae.second;
            string curr_data = adj_node->data;
            // if data not in dist map means curr val = INF 
            // so new val will always be lower than INF
            if (dist.find(curr_data) == dist.end() || dist[curr_data]>dist[prev_data]+weight) {
                dist[curr_data] = dist[prev_data]+weight;
                pq.push(make_pair(dist[curr_data], curr_data));
            }        
        }
    }
    string end_s = end->data;
    // did not reach the end node, graph has more than one conected components
    if (dist.find(end_s) == dist.end()) return INT_MAX;
    return dist[end_s];
}
>>>>>>> c7c6bd7551709b558957f99f712d7a62473f9eb2
