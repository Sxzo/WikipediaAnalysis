#include "graph.h"
#include <iostream>
#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace std;

int main() {

    
    Graph g;
    // PNG* image = g.drawBase();


    Graph::Node* start = g.getNode("Zulu");
    Graph::Node* end = g.getNode("Weapon");
    int to_return = g.dijkstras(start,end);
    std::cout << "RETURN VALUE: " + to_string(to_return) << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    // vector<Graph::Node*> d = g.dijkstrasVector(start,end);


    // std::cout << std::endl;
    // for (size_t i = 0; i < d.size(); i++) {
    //     std::cout << d[i] -> data << std::endl;
    // }
    // std::cout << std::endl;

    // PNG png;  
    // png.readFromFile("/workspaces/cs225/Final-Project/build/BFS.png");

    // vector<pair<Graph::Node*, int>> output  = g.connectedComponents();
    // for (size_t i = 0; i < output.size(); i++) {
    //     cout << "Name: " << output[i].first -> data << " || " << "Size: " << output[i].second << endl;
    // }
    // std::cout << node -> data << std::endl;
    // std::cout << std::endl;
    // vector<Graph::Node*> bfs = g.BFS(node);
    // std::cout << "Size: " + to_string(bfs.size()) << std::endl; 

    // Animation animation = g.visualizeBFS("Zulu");
    // PNG image = animation.getFrame(animation.frameCount() - 1);
    // image.writeToFile("BFS" + string(".png"));
    // animation.write("BFS.gif");


    // for (auto edge : g.incidentEdges(g.getNode("Global city"))) {
    //     cout << edge << endl;
    // }
    //PNG* image = g.visualizeBFS();
    //image->writeToFile("BFS" + string(".png"));
    // string function;
    // int f;
    // cout << "Which function do you want to use?" << "\n" << "1. BFS" << "\n" << "2. Djikstra's Algorithm" << endl;
    // cin >> function;
    // f = stoi(function);
    // string node;
    // string node2;
    // vector<Graph::Node*> vect;
    // switch (f) {
    //     case 1:
    //     cout << "Enter starting node" << endl;
    //     cin >> node;
    //     vect = g.BFS(g.getNode(node));
    //     for (Graph::Node* n : vect) {
    //         cout << n->data << endl;
    //     }
    //     break;
    //     case 2:
    //     cout << "Enter starting node" << endl;
    //     cin >> node;
    //     cout << "Enter ending node" << endl;
    //     cin >> node2;
    //     vect = g.dijkratasAlgorithm(g.getNode(node), g.getNode(node2));
    //     for (Graph::Node* n : vect) {
    //         cout << n->data << endl;
    //     }
    //     break;
    // }
    return 0;
}