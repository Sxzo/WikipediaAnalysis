#include "graph.h"

//--------------------------------Graph Interaction / Construction Functions---------------------------------------

Graph::Graph() {
    readFromFile();
}

Graph::Graph(bool b) {
    for (int i = 0; i < 20; i++) {
        nodeList_.push_back(new Node(to_string(i)));
    }
    for (int i = 0; i < 19; i++) {
        for (int j = 2; j < 20; j++) {
            insertEdge(nodeList_[i], nodeList_[j], 10);
        }
    }
    insertEdge(nodeList_[19], nodeList_[0], 1);
}

void Graph::readFromFile() {
    ifstream ifs("../data/articles.tsv");
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
    ifstream ifs2("../data/links.tsv");
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

vector<string> Graph::incidentEdges(Node* v) {
    vector<string> toReturn;
    for (unsigned i = 0; i < v->adjList.size(); i++) {
        toReturn.push_back(v->adjList[i].second->data);
    }
    return toReturn;
}

bool Graph::areAdjacent(Node* v1, Node* v2) {
    for (unsigned i = 0; i < v1->adjList.size(); i++) {
        if ((v1->adjList[i].second->data) == v2->data) {
            return true;
        }
    }
    return false;
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

int Graph::getNodeDegree(Node* v) {
    if (v == NULL) return -1; 
    for (unsigned i = 0; i < nodeList_.size(); i++) {
        if (nodeList_[i] == v) {
            return v->degree;
        }
    }
    return 999999999;
}

Graph::Node* Graph::getNode(string article) {
    for (unsigned i = 0; i < nodeList_.size(); i++) {
        if (nodeList_[i]->data == article) {
            return nodeList_[i];
        }
    }
    return nullptr;
}

int Graph::getIndex(string article) {
    for (unsigned i = 0; i < nodeList_.size(); i++) {
        if (nodeList_[i]->data == article) {
            return i;
        }
    }
    return -1;
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

//--------------------------------------------Graph Algorithms--------------------------------------------

vector<Graph::Node*> Graph::BFS(Graph::Node* start) {
    queue<Graph::Node*> queue;
    vector<Graph::Node*> output;
    set<Graph::Node*> visited;
    if (start == NULL) return output;
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

bool compare(pair<int, string> lhs, pair<int, string> rhs) { // Used to change decltype of priority queue in dijkstras
    return lhs.first > rhs.first;
}

int Graph::dijkstras(Node* start,Node* end) { 
    
    if (end == NULL || start == NULL) return INT_MAX;
    if (start->data == end->data) return 0;
    
    // Priority queue is initialized with specific decltype based on compare
    // This is done in order to make the priority queue properly usable with a std::pair for dijsktras
    priority_queue<pair<int,string>, vector<pair<int, string>>, std::function<bool(pair<int, string>, pair<int, string>)>> pq(compare);
    
    unordered_map<string, int> dist;
    dist[start -> data]=0;
    for (Node* n : nodeList_) {
        if (n != start) {
            dist[n->data] = INT_MAX;
        }
    }
    pq.push(make_pair(0,start -> data));
    while(!pq.empty()) {
        string prev_data = pq.top().second;

        if (prev_data == end->data) {
            break;
        }

        pq.pop();
        
        for (pair<int, Node*> ae : getNode(prev_data) -> adjList) {
            int weight = ae.first;
            string curr_data = ae.second -> data;

            if (dist[curr_data]>dist[prev_data]+weight) {
                dist[curr_data] = dist[prev_data]+weight;
                pq.push(make_pair(dist[curr_data], curr_data));
            }        
        }
    }
    if (dist.find(end -> data) == dist.end()) return INT_MAX;
    return dist[end -> data];
}

vector<Graph::Node*> Graph::dijkstrasVector(Node* start, Node* end) {
    priority_queue<pair<int,string>, vector<pair<int, string>>, std::function<bool(pair<int, string>, pair<int, string>)>> pq(compare);
    unordered_map<string, int> dist;
    dist[start -> data]=0;

    // Initializes all nodes to max distance
    for (Node* n : nodeList_) {
        if (n != start) {
            dist[n->data] = INT_MAX;
        }
    }

    pq.push(make_pair(0,start -> data));

    unordered_map<string, pair<pair<int, Node*>, Node*>> previous; 
    vector<Node*> path; 
    while(!pq.empty()) {
        string prev_data = pq.top().second;

        if (prev_data == end->data) {
            break;
        }

        pq.pop();
        
        for (pair<int, Node*> ae : getNode(prev_data) -> adjList) {
            int weight = ae.first;
            string curr_data = ae.second -> data;

            if (dist[curr_data]>dist[prev_data]+weight) {
                dist[curr_data] = dist[prev_data]+weight;
                pq.push(make_pair(dist[curr_data], curr_data));
                previous[curr_data] = make_pair(ae, getNode(prev_data));
            }        
        }
    }
    if (dist.find(end -> data) == dist.end()) return path;
    
    path.push_back(start);
    vector<pair<int, Node*>> edge_path; 
    string curr = end->data; 
    while (previous.count(curr) != 0) {
        edge_path.push_back(previous[curr].first);
        curr = previous[curr].second->data;
    } 

    std::reverse(edge_path.begin(), edge_path.end());
    
    for (auto edge : edge_path) {
        path.push_back(edge.second);
    }

    return path;
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
}

int Graph::stoerWagnerHelper(vector<Graph::Node*> otherNodes, Node*& s, Node*& t) { 
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
        Node* maxVertex;
        int maxWeight = -1;
        for (Node* node : otherNodes) {
            int weight = 0; // initializes the edge weight between this node and the super node
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

//--------------------------------------------Visualizations--------------------------------------------

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

Animation Graph::visualizeDijkstras(Node* start, Node* end) {
    PNG* image = new PNG(size, size); 
    std::vector<Node*> dijkstra = dijkstrasVector(start,end);

    // int index1 = getIndex(start -> data);
    // int index2 = getIndex(end -> data);
    // int startIndex = index1 > index2 ? index2 : index1;
    // int endIndex = index1 > index2 ? index1 : index2;
    //draws all the nodes on the base image
    for (size_t i = 0; i < nodeList_.size(); i++) {
        drawNode(nodeList_[i],image, dijkstra);
    }
    
    
    //draws all adjacent edges of dijkstra
    for (size_t i = 0; i < dijkstra.size(); i++) {
        Node* node = dijkstra[i];
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

    //adds the first node to the traversal:
    int r = start -> degree/6;
    for (int y =- r; y <= r; y++) {
        for (int x = -r; x<= r; x++) {
            if (x * x + y * y <= r * r) traversal.push_back(make_tuple(Point(start->coord.first + x, start->coord.second + y), 1, start -> degree, start -> coord)); 
        }
    }

    for (size_t i = 0; i < dijkstra.size() - 1; i++) {
        drawEdge(dijkstra[i], dijkstra[i+1]);
    }
    
    Animation animation = Animate(frameRate, image);
    return animation;
}



void Graph::drawDijkstra(PNG* image) {
    // Iterates through traversal and colors in PNG based on object type
    for (tuple<Point,int,int, pair<int,int>> tuple : traversal) {
        HSLAPixel& pixel = image->getPixel(get<0>(tuple).x,get<0>(tuple).y); 
        if (get<1>(tuple) == 0) { // if we're coloring in an edge
            SolidColorPicker color = SolidColorPicker(HSLAPixel(0,1,0.5,1));
            pixel = color.getColor(get<0>(tuple).x,get<0>(tuple).y);  // fill pixel
        } else { // if we're coloring in a node
            GradientColorPicker color = GradientColorPicker(HSLAPixel(0,1,0.5,1), HSLAPixel(50,1,0.5,1), Point(get<3>(tuple).first, get<3>(tuple).second), (get<2>(tuple)));
            pixel = color.getColor(get<0>(tuple).x,get<0>(tuple).y);  // fill pixel
        }
    }
}

PNG* Graph::drawBase() {
    int num_nodes = nodeList_.size(); //Approx 4,500 nodes
    PNG* image = new PNG(size,size);

    for (int i = 0; i < num_nodes; i++) {
        Node* node = nodeList_[i];
        drawNode(node, image);
    }
    return image;
}

void Graph::drawEdge(Node* node1, Node* node2) { 
    //Just to make sure we're not drawing an edge between two nodes that haven't been drawn yet:
    if (node1 -> coord.first == 0 || node2 -> coord.first == 0) {
        std::cout << std::endl;
        std::cout << "Node hasn't been drawn yet" << std::endl;
        std::cout << std::endl;
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

    // Circle Filling Algorithm: 
    int r = node2->degree/6;
    for (int y =- r; y <= r; y++) {
        for (int x = -r; x<= r; x++) {
            if (x * x + y * y <= r * r) traversal.push_back(make_tuple(Point(x2 + x, y2 + y),1, r, node2 -> coord)); 
        }
    }
}

void Graph::drawNode(Node* node, PNG* image) {
    int radius = node -> degree/6;   
    if (radius == 0) { // in case node -> degree < 6
        radius = 1;
    }
    int center_x = (rand() % (size - 2*radius)) + radius;
    int center_y = (rand() % (size - 2*radius)) + radius;

    int x = 0; 
    while (collision(center_x, center_y, radius)) { // Generates a coordinate up to 10,000 times until a collision is resolved
        x++;
        if (x > 10000)  {
            break;
        }
        center_x = rand() % (size - 2 * radius) + radius;
        center_y = rand() % (size - 2 * radius) + radius;
        
    }

    coord_list.push_back(make_tuple(center_x, center_y, radius)); // Adds new coordinate to collision coordinate list

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

void Graph::drawNode(Node* node, PNG* image, vector<Node*> dijkstra) {
    int radius = node -> degree/6;   
    if (radius == 0) { // in case node -> degree < 6
        radius = 1;
    }
    int center_x = (rand() % (size - 2*radius)) + radius;
    int center_y = (rand() % (size - 2*radius)) + radius;

    int x = 0; 
    while (collision(center_x, center_y, radius)) { // Generates a coordinate up to 10,000 times until a collision is resolved
        x++;
        if (x > 10000)  {
            break;
        }
        center_x = rand() % (size - 2 * radius) + radius;
        center_y = rand() % (size - 2 * radius) + radius;
        
    }

    coord_list.push_back(make_tuple(center_x, center_y, radius)); // Adds new coordinate to collision coordinate list

    node -> coord = make_pair(center_x,center_y);
    
    for (size_t i = 0; i < dijkstra.size(); i++) {
        if (dijkstra[i] -> data == node -> data) {
            dijkstra[i] -> coord = make_pair(center_x,center_y);
        }
    }

    //this code draws the circle
    // for (int i = 0; i <= radius; i++) { // i = x
    //     int y = sqrt(pow(radius,2) - pow(i,2));
    //     image -> getPixel(center_x + i, center_y + y).l = 0;
    //     image -> getPixel(center_x + i, center_y - y).l = 0;
    //     image -> getPixel(center_x - i, center_y + y).l = 0;
    //     image -> getPixel(center_x - i, center_y - y).l = 0;
    // }
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

//--------------------------------------------Testing Functions--------------------------------------------

int Graph::getNodeListSize() {
    return nodeList_.size();
}

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

int Graph::dijkstrasStr(string start,string end, unordered_map<string, vector<pair<int, string>>> adj) {
    priority_queue<pair<int,string>> pq;
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

void Graph::clear() { // Destructor helper
    for (unsigned i = 0; i < nodeList_.size(); i++) {
        delete nodeList_[i];
    }
    
}

void Graph::copy(const Graph& other) { // Copy constructor helper
    for (unsigned i = 0; i < other.nodeList_.size(); i++) {
        nodeList_.push_back(new Node(other.nodeList_[i]->data));
    }
    for (unsigned i = 0; i < other.nodeList_.size(); i++) {
        for (unsigned j = 0; j < other.nodeList_[i]->adjList.size(); j++) {
            insertEdge(nodeList_[i], getNode(other.nodeList_[i]->adjList[j].second->data), other.nodeList_[i]->adjList[j].first);
        }
    }
}