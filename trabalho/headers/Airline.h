#ifndef AIRLINE_H
#define AIRLINE_H

#include <string>
#include <iostream>


class Airline {
    private:
        std::string code;
        std::string name;
        std::string callSign;
        std::string country;
    public:
        Airline(std::string code, std::string name, std::string callSign, std::string country);
        Airline();
        std::string getCode() const;
        std::string getName()const;
        std::string getCallSign() const;
        std::string getCountry() const;

};


#endif
