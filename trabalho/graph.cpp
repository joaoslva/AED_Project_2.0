#include <utility>

#include "headers/graph.h"



void Graph::addAirport(std::string &code, std::string &name, std::string &city, std::string &country, double &latitude, double &longitude){
    Airport n;
    n.code = code;
    n.name = name;
    n.country = country;
    n.city  = city;
    n.longitude = longitude;
    n.latitude = latitude;
    n.distance = 0;
    n.visited = false;
    nodes[code] = n;
}
/*
void Graph::dfs(int v) {
    // show Airport order
    // cout << v << " ";
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}*/
