#ifndef AIRLINE_H
#define AIRLINE_H

#include <string>


class Airline {
    private:
        std::string code;
        std::string name;
        std::string callSign;
        std::string country;
    public:
        Airline(std::string code, std::string name, std::string callSign, std::string country): code(code), name(name), callSign(callSign), country(country){};
        Airline(): code(""), name(""), callSign(""), country("") {}
        std::string getCode() const {return code;}
        std::string getName()const {return name;}
        std::string getCallSign() const{return callSign;}
        std::string getCountry() const {return country;}

};


#endif
