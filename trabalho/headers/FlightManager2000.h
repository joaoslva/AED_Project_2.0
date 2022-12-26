#ifndef FLIGHTMANAGER2000_H
#define FLIGHTMANAGER2000_H

#include <iostream>
#include <unordered_set>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>

#include "Airport.h"
#include "Airline.h"
#include "graph.h"


struct airportHash{
    int operator() (const Airport& airport) const {
        std::string s1 = airport.getCode();
        int v = 0;
        for ( unsigned int i=0; i < s1.size(); i++ )
            v = 37*v + s1[i];
        return v;
    }
    bool operator() (const Airport& airport1, const Airport& airport2) const{
        return airport1.getCode() == airport2.getCode();
    }
};

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



typedef std::unordered_set<Airport,airportHash,airportHash> Airports;
typedef std::unordered_set<Airport,airportHash,airportHash>::iterator iteratorAirport;

typedef std::unordered_set<Airline,airlineHash,airlineHash> Airlines;
typedef std::unordered_set<Airline,airlineHash,airlineHash>::iterator iteratorAirline;


class FlightManager2000 {
    private:
        Airports airports;
        Airlines airlines;
        Graph airportsGraph;

    public:
        void addAirports(const std::string& pathName);
        void addAirlines(std::string pathName);
        //void bestFlightAtoB();
        //void connectionAirport();
        //void airportFlights(std::string AirPortName);
        //void airportAirLines(std::string AirPortName);
        //void airportRange(std::string AirPortName, int numFlights);

        int airlinesSize(){return airlines.size();}
        int airportsSize() {return airports.size();}
};


#endif
