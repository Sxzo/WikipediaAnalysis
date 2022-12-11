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
    bool run = true;
    while (run) {
        cout << "\n"; 
        cout << "|-----------------------CRYPTIC WIKI PROJECT-----------------------|" << endl;
        cout << "\n"; 
        cout << "                       Choose your function:                        " << endl;
        cout << "\n"; 
        cout << "         1. BFS            2. Dijkstra's            3. Stoer-Wagner  " << endl;
        cout << "\n"; 
        cout << "              Enter number and press ENTER to continue...           " << endl; 
        cout << "\n";
        int function; 
        cin >> function;
        cout << "\n"; 
        string node; 
        string end_node;
        int choice; 
        int choice2;
            if (function == 1) {     
                cout << "|-------------------------------BFS--------------------------------|" << endl;
                cout << "\n";
                cout << "                        Enter a starting node:                      " << endl;
                cout << "\n"; 
                cout << "    Suggested choices: Viking, Global city, Zulu, Directdebit, Glass" << endl;
                cout << "\n"; 
                cout << "                Enter node and press ENTER to continue...           " << endl; 
                cout << "\n";
                cin >> node;
                vector<Graph::Node*> bfs = g.BFS(g.getNode(node));
                cout << "\n";
                cout << "                       Choose your function:                        " << endl;
                cout << "\n"; 
                cout << " 1. Print                  2. Visualize             3. Size         " << endl;
                cout << "\n"; 
                cout << "              Enter number and press ENTER to continue...           " << endl; 
                cout << "\n";
                cin >> choice;
                if (choice == 1) {
                    for (Graph::Node* n : bfs) cout << n -> data << endl;
                } else if (choice == 2) {
                    Animation animation = g.visualizeBFS();
                        animation.write("BFS.gif");
                cout << "              Visualization written to build directory!             " << endl;
                } else if (choice == 3) {
                cout << "           Your selected BFS traversal has a size of: " << bfs.size() << endl; 
                }
            } else if (function == 2) {
            cout << "|-----------------------------Dijkstras----------------------------|" << endl;
            cout << "\n";
            cout << "                        Enter a starting node:                      " << endl;
            cout << "\n"; 
            cout << "           Suggested choices: Viking, Global city, Zulu, Glass         " << endl;
            cout << "\n"; 
            cout << "                Enter node and press ENTER to continue...           " << endl; 
            cout << "\n";
            cin >> node;
            cout << "                        Enter an ending node:                      " << endl;
            cout << "\n"; 
            cout << "           Suggested choices: Viking, Global city, Zulu, Glass        " << endl;
            cout << "\n"; 
            cout << "                Enter node and press ENTER to continue...           " << endl; 
            cout << "\n";
            cin >> end_node;
            cout << "\n";
            cout << "                       Choose your function:                        " << endl;
            cout << "\n"; 
            cout << "      1. Print Path     2. Find minimum links      3. Visualize     " << endl;
            cout << "\n"; 
            cout << "              Enter number and press ENTER to continue...           " << endl; 
            cout << "\n";
            cin >> choice2;
            cout << "\n"; 
            
            if (choice2 == 1) {
                vector<Graph::Node*> path = g.dijkstrasVector(g.getNode(node), g.getNode(end_node));
                size_t num = 0; 
                
                for (Graph::Node* n : path) {
                    if (num == path.size() - 1) {
                        cout << n->data << endl;
                        cout << "\n";
                        break;
                    }
                    cout << n->data << " -> ";
                    num++;
                }
            } else if (choice2 == 2) {
                int link_count = g.dijkstras(g.getNode(node), g.getNode(end_node));
        cout << "                   Minimum Links Traversed: " << link_count << endl;
            }
            else if (choice2 == 3) {
                // Animation animation = g.visualizeDijkstras(g.getNode("South America"), g.getNode("South Africa"));
                Animation animation = g.visualizeDijkstras(g.getNode(node), g.getNode(end_node));
                    animation.write("Dijkstra.gif");
                    PNG lastFrame = animation.getFrame(animation.frameCount() - 1);
                    lastFrame.writeToFile("Dijkstra.png");
            cout << "              Visualization written to build directory!             " << endl;
            }
            } else if (function == 3) {
                cout << "|-----------------------------Stoer-Wagner----------------------------|" << endl;
                cout << "\n";
                cout << "                        Enter a starting node:                      " << endl;
                cout << "\n"; 
                cout << "           Suggested choices: Directdebit, Sponsored Directdebit         " << endl;
                cout << "            Any other nodes will take a VERY long time to run            " << endl;
                cout << "\n"; 
                cout << "                Enter node and press ENTER to continue...           " << endl; 
                cout << "\n";
                cin >> node;
                vector<pair<string, string>> result = g.stoerWagner(g.getNode(node));
                for (pair<string, string> pair : result) {
                    cout << pair.first << " " << pair.second << endl;
                }
            }
        cout << "\n";
        cout << "                       Use another function?                        " << endl;
        cout << "\n"; 
        cout << "                       1. Yes       2. No                           " << endl;
        cout << "\n"; 
        cout << "              Enter number and press ENTER to continue...           " << endl;
        int keepGoing;
        cin >> keepGoing;
        if (keepGoing != 1) {
            run = false;
        }
        }
    
    
   
    // Animation animation = g.visualizeBFS();
    // animation.write("BFS.gif");
    
    
    // Graph::Node* start = g.getNode("Global city");
    // vector<Graph::Node*> bfs = g.BFS(start); 
    // cout << "BFS size " << bfs.size() << endl;
    // Graph::Node* end = bfs[850];
    // cout << "End Node: " << bfs[800]->data << endl;
    // cout << "Distance: " << g.dijkstras(start,end) << endl; 
    // vector<Graph::Node*> to_return = g.dijkstrasVector(start,end);
    // int x = 0;
    // for (Graph::Node* n : to_return) {
    //     x++;
    //     cout << "Node " << x << ": " << n->data << " Degree: " << n->degree << endl;
    // } 

    // cout << "Returns: " << g.dijkstrasAlgorithm(start,end) << endl;

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
    //      cout << "Name: " << output[i].first -> data << " || " << "Size: " << output[i].second << endl;
    //  }
    // std::cout << node -> data << std::endl;
    // std::cout << std::endl;
    // vector<Graph::Node*> bfs = g.BFS(node);
    // std::cout << "Size: " + to_string(bfs.size()) << std::endl; 

    // Animation animation = g.visualizeBFS("Zulu");
    // PNG image = animation.getFrame(animation.frameCount() - 1);
    // image.writeToFile("BFS" + string(".png"));
    // animation.write("BFS.gif");
    //Animation animation = g.visualizeBFS();
    //animation.write("BFS.gif");


    //for (auto edge : g.incidentEdges(g.getNode("Global city"))) {
    //    cout << edge << endl;
    //}
    //PNG* image = g.visualizeBFS();
    //image->writeToFile("BFS" + string(".png"));
    // string function;
    // int f;
    // cout << "Which function do you want to use?" << "\n" << "1. BFS" << "\n" << "2. Djikstra's Algorithm" << endl;
    // int func;
    // cin >> func;
    // string node;
    // string node2;
    // vector<Graph::Node*> vect;
    // switch (func) {
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
    //     vect = g.dijkstrasVector(g.getNode(node), g.getNode(node2));
    //     for (Graph::Node* n : vect) {
    //         cout << n->data << endl;
    //     }
    //     break;
    // }
    return 0;
}