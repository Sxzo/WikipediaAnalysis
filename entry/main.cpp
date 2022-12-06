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
    
    // image->writeToFile("BFS" + string(".png"));

    // PNG png;  
    // png.readFromFile("/workspaces/cs225/Final-Project/build/BFS.png");
    Animation animation = g.visualizeBFS();
    animation.write("BFS.gif");


    for (auto edge : g.incidentEdges(g.getNode("Global city"))) {
        cout << edge << endl;
    }
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