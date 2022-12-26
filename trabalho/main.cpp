#include <iostream>
#include "headers/FlightManager2000.h"
int main() {
    FlightManager2000 flightManager2000 = FlightManager2000();
    flightManager2000.addAirports("/home/joao/Desktop/AED/AED_Project_2.0/trabalho/dataset/airports.csv");
    flightManager2000.addAirlines("/home/joao/Desktop/AED/AED_Project_2.0/trabalho/dataset/airlines.csv");
    std::cout << flightManager2000.airportsSize() << '\n';
    std::cout << flightManager2000.airLinesSize() << '\n';
}
