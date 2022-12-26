#ifndef AIRPORT_H
#define AIRPORT_H

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
        Airport(): name(""), city(""), country(""), latitude(0.0), longitude(0.0) {}
        Airport(std::string code, std::string name, std::string city, std::string country, double latitude, double longitude): code(code), name(name), city(city), country(country), longitude(longitude), latitude(latitude) {};
        std::string getCode() const {return code;}
        std::string getName() const {return name;}
        std::string getCity() const{return city;}
        std::string getCountry() const{return country;}
        double getLatitude() {return latitude;}
        double getLongitude() {return longitude;}


};


#endif
