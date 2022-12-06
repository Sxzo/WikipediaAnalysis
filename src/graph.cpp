#include "graph.h"


using namespace std;

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

PNG* Graph::visualizeBFS() {
     
    int num_nodes = nodeList_.size(); //Approx 4,500 nodes
    PNG* image = new PNG(size,size);
    for (int i = 0; i < num_nodes; i++) {
        Node* node = nodeList_[i];
        drawNode(node, image);
        
    }

    for (int i = 0; i < num_nodes; i++) {
        Node* node = nodeList_[i];
        for (size_t k = 0; k < node -> adjList.size(); k++) {
            drawEdge(node, node -> adjList[k].second, image);
        }
    }
    
    return image;
}

void Graph::drawEdge(Node* node1, Node* node2, PNG* image) {
    //y = mx + b
    int x1 = node1 -> coord.first;
    int y1 = node1 -> coord.second;
    int x2 = node2 -> coord.first;
    int y2 = node2 -> coord.second;

    int x_dist = abs(x2 - x1);
    int y_dist = abs(y2 - y1);

    int start_x = x1 < x2 ? x1 : x2;
    int start_y = x1 < x2 ? y1 : y2;
    if (x_dist == 0) { //draw vertical line
        for (int i = 0; i < y_dist; i++) {
            image -> getPixel(start_x,start_y + i) = HSLAPixel(0,1,0.5,1);
        }
        return;
    }

    double slope = (y2 - y1)/(x2 - x1);
    for (int i = 0; i < x_dist; i++) {
        int y = floor(slope*i);
        if (slope == 0) {
            image -> getPixel(start_x + i, start_y) = HSLAPixel(0,1,0.5,1);
        } else { //slope > 0
            image -> getPixel(start_x + i, start_y + y) = HSLAPixel(0,1,0.5,1);
        }
        
    }

}

void Graph::drawNode(Node* node, PNG* image) {
    int radius = node -> degree;
    //x^2 + y^2 = r^2
    int center_x = rand() % (size - 2*radius) + radius;
    int center_y = rand() % (size - 2*radius) + radius;
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

// vector<Graph::Node*> Graph::dijkratasAlgorithm(Graph::Node* start,Graph::Node* end)
// {
    
//     // create a priority queue for storing the minimum index distance
//    priority_queue<pair<int,Graph::Node*>,vector<pair<int,Graph::Node*> >,greater<pair<int,Graph::Node*> > > pq;
//    // indexed array for calculating distance.
//    vector<Graph::Node*> dist(1000000,INT_MAX);
//    dist[start]=0;
//    pq.push(make_pair(0,start));
//    // iterate through the priority queue
//    while(!pq.empty()){
//        // this d is the distance which will be taken from priority queue.
//        int d=pq.top().first;
//        Graph::Node* p=pq.top().second;
//        pq.pop();
//        // visit all adjacent node to p
//        for (pair<int, Graph::Node*> adjacent_edge : p -> adjList) {
//             Graph::Node* adjacent_node = adjacent_edge.second;
//             // check if the distance is minimum or not. 
//             // if not then update the new distance. 
//             if(dist[adjacent_node] > dist[p] + adjacent_edge.first)
//             {
//                 dist[adjacent_node]=dist[p]+adjacent_edge.first;
//                 pq.push(make_pair(dist[adjacent_node]),adjacent_node);
//             }
//         }
//    }
//    return dist;

// }
