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
       
       //Graph Functions:

        /**
        * Generates a graph implemented with an Adjacency List with data from a given Wikipedia Link Dataset.
        */
        Graph(); 

        /**
        * Removes a vertex(node) from Graph.
        *
        * @param v Node to be removed.
        */
        void removeVertex(Node* v);

        /**
        * Returns a vector containing all edges adjacent to a given node.
        *
        * @param v Node to find adjacent edges of.
        */
        vector<string> incidentEdges(Node* v); //returns the list of edges adjacent to node v

        /**
        * Returns a bool representing whether or not two nodes are adjacent.
        *
        * @param v1 Node one to compare adjacency.
        * @param v2 Node two to compare adjacency
        */
        bool areAdjacent(Node* v1, Node* v2); 

        /**
        * Inserts an edge into the graph.
        *
        * @param v1 Node representing startpoint of edge.
        * @param v2 Node representing endpoint of edge. 
        */
        void insertEdge(Node* v1, Node* v2);

        /**
        * Inserts an edge into the graph with a given weight.
        *
        * @param v1 Node representing startpoint of edge.
        * @param v2 Node representing endpoint of edge. 
        * @param weight Integer to denote weight of edge. 
        */
        void insertEdge(Node* v1, Node* v2, int weight);

        /**
        * Returns the degree of a node.
        *
        * @param v Node to return degree of. 
        */
        int getNodeDegree(Node* v);
        

        //Graph Algorithms:

        /**
        * Returns a vector of nodes containing each node from a Breadth-First-Search traversal starting on a given node. 
        *
        * @param start Node to begin Breadth-First-Search on. 
        */
        vector<Node*> BFS(Node* start);

        /**
        * Returns the lowest sum of edge weights to get from a startpoint to an endpoint node.
        *
        * @param start Node startpoint .
        * @param end Node endpoint of path. 
        */
        int dijkstrasAlgorithm(Node* start,Node* end);

        /**
        * Returns a vector containing all nodes traversed in the shortest path between two given nodes.
        *
        * @param start Node startpoint .
        * @param end Node endpoint of path. 
        */
        vector<Node*> dijkstrasVector(Node* start,Node* end);

        int stoerWagnerHelper(vector<Node*> otherNodes, Node*& s, Node*& t);
        vector<pair<string, string>> stoerWagner(Node* startNode);
        Node* mergeNodes(Node* node1, Node* node2);

        int dijkstras(Node* start,Node* end);

        //Visualizations:
        /**
        * Returns an animation of Dijkstras algoirithm.
        */
        Animation visualizeDijkstras();

        /**
        * Returns an animation of the Breadth-First-Search traversal.
        *
        * <NOTE> This is NOT the full visualization of BFS. Memory limitations have capped it at the first ~100 nodes. 
        */
        Animation visualizeBFS();
        

        void drawDijkstra(PNG* image);
        PNG* drawBase();
        Animation visualizeBFS(PNG* picture);
<<<<<<< HEAD
        void drawEdge(Node* node1, Node* node2); 
        void drawNode(Node* node, PNG* image); 
        Animation Animate(unsigned frameInterval, PNG* image);
        void populateCoords(Node* node); // Populates node coordinates
        vector<pair<Node*, int>> connectedComponents();
        bool collision(int x, int y, int r); // Detects if circle will collide with one previously drawn
        int calculateVisualizationNodeCount(); // Helper method to calculate upper bound of nodes capable of fitting
=======
        int dijkstras(string start,string end, unordered_map<string, vector<pair<int, string>>> adj);
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

      
>>>>>>> c7c6bd7551709b558957f99f712d7a62473f9eb2

        //functions added so tests will compile
        int getNodeListSize();
        Node* getNode(string article);
        
        // Need to add rule of 3 functions because the nodes are dynamically allocated
        ~Graph();
        Graph(const Graph& other);
        Graph& operator=(const Graph& other);
        
<<<<<<< HEAD
=======
        vector<pair<Graph::Node*, int>> connectedComponents();

>>>>>>> c7c6bd7551709b558957f99f712d7a62473f9eb2
    private:
        // Visualization: 
        int size = 500;
        unsigned frameRate = 1000;
        unsigned iter_limit = 100; // Truncates BFS traversal in visualization to save space
        vector<tuple<Point,int,int, pair<int,int>>> traversal; //int2 = 1 = node || = 0 = edge, int3 = node -> degree, int4 = node -> coord
        vector<tuple<int, int, int>> coord_list; // (int1, int 2) = coords || int3 = radius

        // Constructor-only helpers:
        void readFromFile();
        string decodeHTTP(string title);
        unordered_map<string, string> converted; //map used for memoization of http decoding

        // Graph:
        vector<Node*> nodeList_;
        
        //helpers for rule of three
        void clear();
        void copy(const Graph& other);
};

