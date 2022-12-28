#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <vector>
#include "Airport.h"
#include <iostream>
#include <unordered_set>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <unordered_map>


using namespace std;

class Graph {
    struct Edge {
        int dest;
        int weight;
    };

    struct node {
        Airport airport;
        list<Edge> adj;
        bool visited;
        int distance;
    };

    int n = 0;

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

    typedef std::unordered_map<string, node, nodeHash, nodeHash> Nodes;
    typedef std::unordered_map<string, node, nodeHash, nodeHash>::iterator nodesItr;
    Nodes nodes;
public:
    Graph();
    void addAirports(const std::string& pathName);
    void getNumberAirports();
    void addEdge(int src, int dest, int weight = 1);
    void dfs(int v);
};

#endif
