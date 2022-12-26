#include "headers/FlightManager2000.h"


void FlightManager2000::addAirports(const std::string& pathName) {
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    double latitude;
    double longitude;

    int count = 0;

    std::ifstream file;
    file.open(pathName);

    Airport airport = Airport();

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
        city = data;
        std::getline(inputString, data, ',');
        country = data;
        std::getline(inputString, data, ',');
        latitude = std::stod(data);
        std::getline(inputString, data, '\r');
        longitude = std::stod(data);

        airport = Airport(code, name, city, country, latitude, longitude);

        airports.insert(airport);
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
