#pragma once
#include <vector> 
#include <string> 
#include <iostream>
#include <fstream>
#include <map>

using namespace std; 

class Graph {
    private:
        struct Node {
            Node(string article) : data(article) {}; // Node constructor
            vector<pair<int, Node*>> adjList;  // list of adjacent nodes and their edge weights
            pair<int, Node*> connection;  // int: the weight of the edge, Node: the adjacent node connected by the edge
            string data; // Article name
            int degree; // Number of total edges connected to node (adjList.size())
        };
        void readFromFile();
        string decodeHTTP(string title);
        vector<Node> nodeList_; 
    public:
        Graph(); 
        void removeVertex(Node v);
        vector<pair<int, Node>> incidentEdges(Node v); //returns the list of edges adjacent to node v
        bool areAdjacent(Node v1, Node v2); 
        void insertEdge(Node v1, Node v2, int weight); // Weight = v1.degree + v2.degree
           
};

