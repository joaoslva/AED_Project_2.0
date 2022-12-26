#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <vector>
#include <iostream>

using namespace std;

class Graph {
    struct Edge {
        int dest;
        int weight;
    };

    struct Node {
        list<Edge> adj;
        bool visited;
    };

    int n;
    bool hasDir;
    vector<Node> nodes;

public:
    Graph(int nodes, bool dir = false);
    void addEdge(int src, int dest, int weight = 1);
    void dfs(int v);
};

#endif
