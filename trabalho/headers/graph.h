#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <set>
#include <vector>
#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>
#include <unordered_map>


class Graph {
    struct Edge {
        std::string dest;
        std::string airlineCode;
        std::string airLineName;
    };

    struct Airport {
        std::string code;
        std::string name;
        std::string city;
        std::string country;
        double latitude = 0;
        double longitude = 0;
        std::list<Edge> adj;
        bool visited = false;
        int distance = 0;
        int low;
        int num;
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

    typedef std::unordered_map<std::string, Airport, nodeHash, nodeHash> Airports;
    typedef std::unordered_map<std::string, Airport, nodeHash, nodeHash>::iterator AirportsItr;
    Airports airports;

public:
    void addAirport(std::string &code, std::string &name, std::string &city, std::string &country, double &latitude, double &longitude);
    void addEdge(const std::string& src, std:: string dest, std::string airlineCode, std::string airlineName);
    int airportsSize();
    void printAirportAirlines();
    void printAirportFlights();
    void simpleShortestPath(const std::string& src, const std::string& destination,std::vector<std::string> &airlines);
    void findArticulationPoints();
    void dfs_articulation_points(std::pair<const std::basic_string<char>, Graph::Airport> &v, int &order, std::list<Graph::Airport> &l);
    void numberFlightsInShortestPath(const std::string& src,std::vector<std::string> &airlines,  std::vector<std::string> &airportsFound,int distance);
    void superBestFlightAtoB(const std::string& src, const std::string& dest, std::vector<std::string> airlines, int option);
    void printAirportRange(const std::string& airportCode, int numFlights, std::vector<std::string>& airlines);
    void locationShortestPath(double latitude, double longitude, int range, const std::string& dest,std::vector<std::string>& airlines);
};

#endif
