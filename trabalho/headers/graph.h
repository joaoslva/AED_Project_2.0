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
        Airport airport = Airport();
        list<Edge> adj;
        bool visited;
        int distance;
    };

    int n = 0;

    struct airportHash {
        int operator() (const Airport& airport) const {
            std::string s1 = airport.getCode();
            int v = 0;
            for (unsigned int i = 0; i < s1.size(); i++)
                v = 37 * v + s1[i];

            return v;
        }
        bool operator() (const Airport& airport1, const Airport& airport2) const {
            return airport1.getCode() == airport2.getCode();
        }
    };
    typedef std::unordered_map<string, int, airportHash, airportHash> nodes;
    typedef std::unordered_map<string, int, airportHash, airportHash>::iterator nodesItr;
public:
    Graph();
    void addAirports(const std::string& pathName);
    void addEdge(int src, int dest, int weight = 1);
    void dfs(int v);
};

#endif
