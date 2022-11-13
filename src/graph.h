#pragma once
#include <vector> 
#include <string> 
#include <iostream>
#include <fstream>
#include <map>

using namespace std; 

class Graph {
    public:
        struct Node {
            Node(string article) : data(article), degree(0) {}; // Node constructor
            vector<pair<int, Node*>> adjList;  // list of adjacent nodes and their edge weights
            string data; // Article name
            int degree; // Number of total edges connected to node (adjList.size())
        };
       
        Graph(); 
        void removeVertex(Node* v);
        vector<string> incidentEdges(Node* v); //returns the list of edges adjacent to node v
        bool areAdjacent(Node* v1, Node* v2); 
        void insertEdge(Node* v1, Node* v2);
        void insertEdge(Node* v1, Node* v2, int weight);
        int getNodeDegree(Node* v);
        
        //functions added so tests will compile
        int getNodeListSize();
        Node* getNode(string article);
        
        // Need to add rule of 3 functions because the nodes are dynamically allocated
        ~Graph();
        Graph(const Graph& other);
        Graph& operator=(const Graph& other);

    private:
        void readFromFile();
        string decodeHTTP(string title);
        vector<Node*> nodeList_; 

        //helpers for rule of three
        void clear();
        void copy(const Graph& other);
};

