#include <iostream>
#include "headers/graph.h"

int main(void) {
    //flightManager2000.addAirlines("/home/joao/Desktop/AED/AED_Project_2.0/trabalho/dataset/airlines.csv");
    Graph graph = Graph();
    graph.addAirports("/home/joao/Desktop/AED/AED_Project_2.0/trabalho/dataset/airports.csv");
    graph.getNumberAirports();
    //std::cout << flightManager2000.airportsSize() << '\n';
    //std::cout << flightManager2000.airlinesSize() << '\n';
}
