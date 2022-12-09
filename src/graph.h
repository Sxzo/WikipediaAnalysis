#pragma once
#include <vector> 
#include <string> 
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <unordered_map>
#include <limits.h>
#include "/workspaces/cs225/Final-Project/lib/cs225/PNG.h"
#include "Animation.h"
#include "Point.h"
#include "/workspaces/cs225/Final-Project/src/colorPicker/ColorPicker.h"
#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace std; 
using namespace cs225;
class Graph {
    public:
        struct Node {
            Node(string article) : data(article), degree(0) {}; // Node constructor
            vector<pair<int, Node*>> adjList;  // list of adjacent nodes and their edge weights
            string data; // Article name
            int degree; // Number of total edges connected to node (adjList.size())
            pair<int,int> coord; //coordinate of the center for BFS visualization
            //to avoid duplicate edges:
            set<Node*> drawn; // set of all the adjacent nodes where an edge has already been drawn

        };
       
        Graph(); 
        void removeVertex(Node* v);
        vector<string> incidentEdges(Node* v); //returns the list of edges adjacent to node v
        bool areAdjacent(Node* v1, Node* v2); 
        void insertEdge(Node* v1, Node* v2);
        void insertEdge(Node* v1, Node* v2, int weight);
        int getNodeDegree(Node* v);
        
        //Graph Algorithms:
        vector<Graph::Node*> BFS(Node* start);
        Animation visualizeBFS();
        PNG* drawBase();
        Animation visualizeBFS(PNG* picture);
        int dijkstrasAlgorithm(Graph::Node* start,Graph::Node* end);



        //Helper functions for visualizeBFS
        void drawEdge(Node* node1, Node* node2); //PNG* image
        void drawNode(Node* node, PNG* image);

        Animation Animate(unsigned frameInterval, PNG* image);

        void populateCoords(Node* node);

        //stoer wagner
        int stoerWagnerHelper(vector<Node*> otherNodes, Node*& s, Node*& t);
        vector<pair<string, string>> stoerWagner(Node* startNode);
        Graph::Node* mergeNodes(Node* node1, Node* node2);

      

        //functions added so tests will compile
        int getNodeListSize();
        Node* getNode(string article);
        
        // Need to add rule of 3 functions because the nodes are dynamically allocated
        ~Graph();
        Graph(const Graph& other);
        Graph& operator=(const Graph& other);
        
        vector<pair<Graph::Node*, int>> connectedComponents();


    private:
    //if int2 = 1 then node, if int2 = 0 then edge, int3 = node -> degree, int4 = node -> coord
        vector<tuple<Point,int,int, pair<int,int>>> traversal; 
        int size = 750; // Just testing for visualizeBFS
        void readFromFile();
        string decodeHTTP(string title);
        vector<Node*> nodeList_;
        unordered_map<string, string> converted;

        //helpers for rule of three
        void clear();
        void copy(const Graph& other);

        
};

