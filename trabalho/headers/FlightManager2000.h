#ifndef TRABALHO_FLIGHTMANAGER2000_H
#define TRABALHO_FLIGHTMANAGER2000_H

#include <iostream>
#include <unordered_set>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>

#include "headers/Airport.h"
#include "headers/Airline.h"

struct airportEqualityFunction{
    bool operator() (const Airport& airport1, const Airport& airport2) const{
        return airport1.getName() == airport2.getName();
    }
};

struct airportHashFunction{
    int operator() (const Airport& airport) const {
        std::string s1 = airport.getName();
        int v = 0;
        for ( unsigned int i=0; i < s1.size(); i++ )
            v = 37*v + s1[i];
        return v;
    }
};

struct airlineEqualityFunction{
    bool operator() (const Airline& airline1, const Airline& airline2) const{
        return airline1.getName() == airline2.getName();
    }
};

struct airlineHashFunction{
    int operator() (const Airline& airline) const {
        std::string s1 = airline.getName();
        int v = 0;
        for ( unsigned int i=0; i < s1.size(); i++ )
            v = 37*v + s1[i];
        return v;
    }
};

typedef std::unordered_set<Airport,airportHashFunction,airportEqualityFunction> Airports;
typedef std::unordered_set<Airport,airportHashFunction,airportEqualityFunction>::iterator iteratorAirport;

typedef std::unordered_set<Airline,airlineHashFunction,airlineEqualityFunction> Airlines;
typedef std::unordered_set<Airline,airlineHashFunction,airlineEqualityFunction>::iterator iteratorAirline;


class FlightManager2000 {
    private:
        Airports airports;
        Airlines airlines;

    public:
        void addAirports(const std::string& pathName);
        void addAirlines(std::string pathName);
        //int airportFlights(std::string AirPortName);
        int airLinesSize(){return airlines.size();}
        int airportsSize() {return airports.size();}


};


#endif
