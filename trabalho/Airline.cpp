#include <iostream>
#include "headers/Airline.h"

Airline::Airline() {
    this->code = "";
    this->name = "";
    this->callSign = "";
    this->country = "";
}

Airline::Airline(std::string code, std::string name, std::string callSign, std::string country) {
    this->code = code;
    this->name = name;
    this->callSign = callSign;
    this->country = country;
}
std::string Airline::getCode() const {return code;}
std::string Airline::getCountry() const {return  country;}
std::string Airline::getName() const {return name;}
std::string Airline::getCallSign() const {return  callSign;}
