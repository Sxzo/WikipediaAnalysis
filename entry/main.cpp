#include "graph.h"
#include <iostream>
using namespace std;

int main() {
    Graph g;
    for (auto i : g.incidentEdges(g.getNode("Time"))) {
        cout << i << endl;
    }
    cout << g.areAdjacent(g.getNode("Time"), g.getNode("11th century")) << endl;
    return 0;
}