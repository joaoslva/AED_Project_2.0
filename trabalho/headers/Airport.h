#ifndef AIRPORT_H
#define AIRPORT_H

#include <iostream>
#include <string>

class Airport {

    private:
        std::string code;
        std::string name;
        std::string city;
        std::string country;
        double latitude;
        double longitude;

    public:
        Airport();
        Airport(std::string code, std::string name, std::string city, std::string country, double latitude, double longitude);
        std::string getCode() const;
        std::string getName() const;
        std::string getCity() const;
        std::string getCountry() const;
        double getLatitude() const;
        double getLongitude() const;
};


#endif
