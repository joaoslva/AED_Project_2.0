#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <vector>
#include <iostream>
#include <unordered_map>


class Graph {
    struct Edge {
        int dest;
        int weight;
    };

    struct Airport {
        std::string code;
        std::string name;
        std::string city;
        std::string country;
        double latitude;
        double longitude;
        std::list<Edge> adj;
        bool visited;
        int distance;
    };

    struct nodeHash {
        int operator() (const std::string& n) const {
            std::string s = n;
            int v = 0;
            for (unsigned int i = 0; i < s.size(); i++)
                v = 37 * v + s[i];

            return v;
        }
        bool operator() (const std::string& n1, const std::string& n2) const {
            return n1 == n2;
        }
    };

    typedef std::unordered_map<std::string, Airport, nodeHash, nodeHash> Nodes;
    typedef std::unordered_map<std::string, Airport, nodeHash, nodeHash>::iterator nodesItr;
    Nodes nodes;

public:
    void addAirport(std::string &code, std::string &name, std::string &city, std::string &country, double &latitude, double &longitude);
    int nodesSize() {return nodes.size();}
    void dfs(int v);
};

#endif
