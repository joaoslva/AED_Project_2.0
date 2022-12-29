#include "headers/FlightManager2000.h"

void FlightManager2000::addAirports(const std::string& pathName) {
    std::string name;
    std::string city;
    std::string country;
    std::string code;
    double latitude;
    double longitude;

    int count = 0;

    std::ifstream file;
    file.open(pathName);


    for(std::string line; getline(file, line);){
        if(count == 0){
            count++;
            continue;
        }

        std::stringstream inputString(line);
        std::string data;

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

        airportsGraph.addAirport(code, name, city, country, latitude, longitude);
    }
}

void FlightManager2000::addAirlines(std::string pathName) {
    std::string code;
    std::string name;
    std::string callSign;
    std::string country;

    int count = 0;

    std::ifstream file;
    file.open(pathName);

    Airline airline = Airline();

    for(std::string line; std::getline(file, line);){
        if(count == 0){
            count++;
            continue;
        }

        std::stringstream inputString(line);
        std::string data;

        std::getline(inputString, data, ',');
        code = data;
        std::getline(inputString, data, ',');
        name = data;
        std::getline(inputString, data, ',');
        callSign = data;
        std::getline(inputString, data, '\r');
        country = data;

        airline = Airline(code, name, callSign, country);

        airlines.insert(airline);
    }
}

void FlightManager2000::addEdges(const std::string &pathName) {
    std::string src;
    std::string dest;
    std::string airlineCode;
    std::string airlineName;


    int count = 0;

    std::ifstream file;
    file.open(pathName);

    Airline airline1 = Airline();
    Airline airline2 = Airline();

    for(std::string line; std::getline(file, line);){
        if(count == 0){
            count++;
            continue;
        }

        std::stringstream inputString(line);
        std::string data;

        std::getline(inputString, data, ',');
        src = data;
        std::getline(inputString, data, ',');
        dest = data;
        std::getline(inputString, data, '\r');
        airlineCode = data;

        airline2 = Airline(airlineCode,"","","");
        airlineName = airlines.find(airline2)->getName();

        airportsGraph.addEdge(src, dest, airlineCode, airlineName);
    }
}


bool FlightManager2000::checkFileOpening(){
    return airportsGraph.airportsSize() > 0 && airlinesSize() > 0;
}

void FlightManager2000::airportAirLines() {
    airportsGraph.printAirportAirlines();
}

void FlightManager2000::airportFlights(){
    airportsGraph.printAirportFlights();
}