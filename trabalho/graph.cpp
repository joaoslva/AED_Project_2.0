#include "headers/graph.h"



void Graph::addNode(const Airport& airport) {
    Node n;
    n.airport = airport;
    n.distance = 0;
    n.visited = false;
    nodes[airport.getCode()] = n;
}
/*
void Graph::dfs(int v) {
    // show Node order
    // cout << v << " ";
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}*/
