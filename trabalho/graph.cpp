#include "headers/graph.h"


/*
void Graph::addEdge(int src, int dest, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
}

void Graph::dfs(std::string v) {
    // show node order
    // cout << v << " ";
    airports[std::string].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}*/
void Graph::addAirports(const string& pathName) {
    string name;
    string city;
    string country;
    string code;
    double latitude;
    double longitude;

    int count = 0;

    ifstream file;
    file.open(pathName);

    Airport airport1 = Airport();

    for(string line; getline(file, line);){
        if(count == 0){
            count++;
            continue;
        }

        stringstream inputString(line);
        string data;

        getline(inputString, data, ',');
        code = data;
        getline(inputString, data, ',');
        name = data;
        getline(inputString, data, ',');
        city = data;
        getline(inputString, data, ',');
        country = data;
        getline(inputString, data, ',');
        latitude = std::stod(data);
        getline(inputString, data, '\r');
        longitude = std::stod(data);
        node node;
        node.airport = Airport(code, name, city, country, latitude, longitude);
        node.visited = false;
        node.distance = 0;
        nodes['code'] = 5;

    }
}