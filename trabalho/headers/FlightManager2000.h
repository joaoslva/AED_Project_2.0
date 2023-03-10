#ifndef FLIGHTMANAGER2000_H
#define FLIGHTMANAGER2000_H

#include <iostream>
#include <unordered_set>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include "Airline.h"
#include "graph.h"

struct airlineHash{
    int operator() (const Airline& airline) const {
        std::string s1 = airline.getCode();
        int v = 0;
        for ( unsigned int i=0; i < s1.size(); i++ )
            v = 37*v + s1[i];
        return v;
    }
    bool operator() (const Airline& airline1, const Airline& airline2) const{
        return airline1.getCode() == airline2.getCode();
    }
};

typedef std::unordered_set<Airline,airlineHash,airlineHash> Airlines;
typedef std::unordered_set<Airline,airlineHash,airlineHash>::iterator iteratorAirline;


class FlightManager2000 {
    private:
        Airlines airlines;
        Graph airportsGraph;

    public:
        void addAirports(const std::string& pathName);
        void addAirlines(const std::string& pathName);
        void bestFlightAtoB();
        void connectionAirport();

        //Airport stats functions
        void airportFlights();
        void airportAirLines();
        void airportRange();

        int airportsSize(){return airportsGraph.airportsSize();}
        int airlinesSize(){return airlines.size();}
        void addEdges(const std::string& pathName);
        bool checkFileOpening();
        void test1() {airportsGraph.findArticulationPoints();}
        void test2(){
            std::vector<std::string> teste;
            airportsGraph.superBestFlightAtoB("Lisbon", "Porto", teste, 1);
        }
};


#endif
