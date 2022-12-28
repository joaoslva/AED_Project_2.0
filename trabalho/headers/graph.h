#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "Airport.h"

using namespace std;

class Graph {
    struct Edge {
        int dest;
        int weight;
    };

    struct Node {
        Airport airport;
        list<Edge> adj;
        bool visited;
        int distance;
    };

    struct nodeHash {
        int operator() (const string& n) const {
            string s = n;
            int v = 0;
            for (unsigned int i = 0; i < s.size(); i++)
                v = 37 * v + s[i];

            return v;
        }
        bool operator() (const string& n1, const string& n2) const {
            return n1 == n2;
        }
    };

    typedef std::unordered_map<string, Node, nodeHash, nodeHash> Nodes;
    typedef std::unordered_map<string, Node, nodeHash, nodeHash>::iterator nodesItr;
    Nodes nodes;

public:
    void addNode(const Airport& airport);
    int nodesSize() {return nodes.size();}
    void dfs(int v);
};

#endif
