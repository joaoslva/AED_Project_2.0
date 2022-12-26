#include <iostream>
#include "headers/Airport.h"

Airport::Airport() {
    this->code = "";
    this->name = "";
    this->city = "";
    this->country = "";
    this->longitude = 0.0;
    this->latitude = 0.0;
}

Airport::Airport(std::string code, std::string name, std::string city, std::string country, double latitude, double longitude) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->longitude = longitude;
    this->latitude = latitude;
}

std::string Airport::getName() const {return name;}

std::string Airport::getCountry() const {return country;}

std::string Airport::getCode() const {return code;}

std::string Airport::getCity() const {return city;}

double Airport::getLatitude() const {return latitude;}

double Airport::getLongitude() const {return longitude;}
