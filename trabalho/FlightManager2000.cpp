#include "headers/FlightManager2000.h"

void FlightManager2000::addAirports(const std::string& pathName) {
    string name;
    string city;
    string country;
    string code;
    double latitude;
    double longitude;

    int count = 0;

    ifstream file;
    file.open(pathName);

    Airport airport = Airport();

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

        airport = Airport(code, name, city, country, latitude, longitude);
        airportsGraph.addNode(airport);
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

bool FlightManager2000::checkFileOpening(){
    return airportsGraph.nodesSize() > 0 && airlinesSize() > 0;
}
