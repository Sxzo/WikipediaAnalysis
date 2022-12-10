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
#include <algorithm>
#include "../lib/cs225/PNG.h"
#include "Animation.h"
#include "Point.h"
#include "../src/colorPicker/ColorPicker.h"
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
       
        //-----------------------------------Graph Interaction / Construction Functions---------------------------------------

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

        /**
        * Returns the Node representing the article in the graph. 
        *
        * @param article Name of article to find. 
        */
        Node* getNode(string article);

        // Rule of 3:
        ~Graph();
        Graph(const Graph& other);
        Graph& operator=(const Graph& other);

        //--------------------------------------------Graph Algorithms--------------------------------------------

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
        int dijkstras(Node* start,Node* end);

        /**
        * Returns a vector containing all nodes traversed in the shortest path between two given nodes.
        *
        * @param start Node startpoint .
        * @param end Node endpoint of path. 
        */
        vector<Node*> dijkstrasVector(Node* start,Node* end);

        /**
        * Returns a vector containing the edges necessary for a minimum-cut on a given graph component.
        *
        * @param startNode Node startpoint of graph component.
        */
        vector<pair<string, string>> stoerWagner(Node* startNode);
        
        int stoerWagnerHelper(vector<Node*> otherNodes, Node*& s, Node*& t); // stoerWagner() helper function. 
        Node* mergeNodes(Node* node1, Node* node2); // stoerWagner() helper function. 

        
        //--------------------------------------------Visualizations--------------------------------------------
        
        /**
        * Returns an animation of the Breadth-First-Search traversal.
        *
        * <NOTE> This is NOT the full visualization of BFS. Memory limitations have capped it at the first ~100 nodes. 
        */
        Animation visualizeBFS();
        
        /**
        * Returns an animation of Dijkstras algoirithm.
        */
        Animation visualizeDijkstras();
        
        /**
        * Draws base of nodes on PNG in order to be used in @visualizeDijkstras().
        */
        void drawDijkstra(PNG* image);

        /**
        * Draws base of nodes on PNG in order to be used in @visualizeBFS().
        */
        PNG* drawBase();

        /**
        * Uses the differential digital analyzer algorithm to populate the traversal 
        * with the coordinates of a line between two given nodes. 
        *
        * Populates the traversal with a circle fill on node2. 
        *
        * @param node1 Node startpoint of line.
        * @param node2 Node endpoint of line. 
        */
        void drawEdge(Node* node1, Node* node2); 

        /**
        * Draws a node onto a given PNG. 
        *
        * @param node Node to draw.
        * @param image PNG base to draw node on. 
        */
        void drawNode(Node* node, PNG* image); 

        /**
        * Animates a number of PNGs by turning them into a GIF. 
        *
        * @param frameInterval Interval rate of animation updating. 
        * @param image Image to pass into animation. 
        */
        Animation Animate(unsigned frameInterval, PNG* image);

        /**
        * Returns a boolean of whether or not an inputed circle will collide with a drawn circle. 
        *
        * Used to prevent collisions of nodes in @visualizeBFS()
        *
        * @param x X-coordinate of circle.
        * @param y Y-coordinate of circle.
        * @param r Radius of circle.  
        */
        bool collision(int x, int y, int r); 

        //--------------------------------------------Testing Functions--------------------------------------------

        /**
        * Returns the total number of nodes. 
        */
        int getNodeListSize();

        /**
        * Returns absolute upper bound of nodes capable of fitting on PNG.
        */
        int calculateVisualizationNodeCount();

        /**
        * <NOTE> Naive implementation. Used to find connected components beyond component 
        * containing "Global city" with a size of 4000+.
        *
        * Returns a pair containing a node which is part of a connected component 
        * and an int representing its size. 
        */
        vector<pair<Node*, int>> connectedComponents();

        /**
        * Returns the lowest sum of edge weights to get from a startpoint to an endpoint node.
        *
        * <NOTE> This method is implemented sheerly for validity testing of the actual dijkstras function. 
        *
        * @param start Node startpoint represented as a string.
        * @param end Node endpoint of path represented as a string.
        * @param adj Temporary graph represented with an adjacency list.
        */
        int dijkstrasStr(string start,string end, unordered_map<string, vector<pair<int, string>>> adj);

    private:
        // -----Visualization------
        int size = 500;
        unsigned frameRate = 1000;
        unsigned iter_limit = 100; // Truncates BFS traversal in visualization to save space
        vector<tuple<Point,int,int, pair<int,int>>> traversal; //int2 = 1 = node || = 0 = edge, int3 = node -> degree, int4 = node -> coord
        vector<tuple<int, int, int>> coord_list; // (int1, int 2) = coords || int3 = radius

        // --Constructor helpers--
        void readFromFile();
        string decodeHTTP(string title);
        unordered_map<string, string> converted; // Map used for memoization of http decoding. 

        // --------Graph---------
        vector<Node*> nodeList_;
        
        //Rule of Three Helpers:
        void clear();
        void copy(const Graph& other);

};