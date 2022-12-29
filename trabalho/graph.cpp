#include <utility>

#include "headers/graph.h"



void Graph::addAirport(std::string &code, std::string &name, std::string &city, std::string &country, double &latitude, double &longitude){
    Airport n;
    n.code = code;
    n.name = name;
    n.country = country;
    n.city  = city;
    n.longitude = longitude;
    n.latitude = latitude;
    airports[code] = n;
}

void Graph::addEdge(std::string src, std::string dest, std::string airlineCode, std::string airlineName) {
    if (airports.find(src) == airports.end()) return;
    airports[src].adj.push_back({dest , airlineCode, airlineName });
}

void Graph::dfs(const std::string& code) {
    // show Airport order
    // cout << v << " ";
    airports[code].visited = true;
    for (const auto& e : airports[code].adj) {
        std::string neighbor = e.dest;
        if (!airports[neighbor].visited)
            dfs(neighbor);
    }
}

void Graph::printAirportFlights() {
    bool airportFlightsRunning = true;
    std::string airportCode;

    while(airportFlightsRunning){
        std::string airportFlightsChoice;
        std::cout << "| Please enter an airport code                             |\n";
        std::cout << "| Enter here: ";
        std::cin >> airportCode;
        std::cout << "|                                                          |\n";

        AirportsItr itr1 = airports.find(airportCode);

        if(itr1 == airports.end()){
            std::cout << "| Airport doesn't exist in the database                    |\n";
            std::cout << "|                                                          |\n";
            airportFlightsRunning = false;
        }

        else{
            std::vector<std::pair<std::string, std::string>> output;

            for(auto itr2 = itr1->second.adj.begin(); itr2 != itr1->second.adj.end(); itr2++){
                if(std::find_if(output.begin(), output.end(), [&] (const std::pair<std::string, std::string>& element) {return element.first == itr2->airLineName;}) == output.end()) {
                    output.push_back({itr2->airLineName, itr2->airlineCode});
                }
            }

            sort(output.begin(), output.end(), [](const std::pair<std::string, std::string>& element1, const std::pair<std::string, std::string>& element2) {return element1.first < element2.first;});
            std::cout << "| Here are the airlines that operate in " + airportCode + " airport:       |\n";
            std::cout << "|                                                          |\n";

            for(const std::pair<std::string,std::string>& pair: output){
                std::cout << "| Name: " + pair.first + "; Code: " + pair.second + '\n';
            }
            airportFlightsRunning = false;
        }
    }
    std::cout << "|                                                          |\n";
}

void Graph::printAirportAirlines() {
    std::string code;
    bool airlinesRunning = true;
    int lineNum;
    auto itr = airports.find(code);
    for (auto itr1 = itr->second.adj.begin(); itr1 != itr->second.adj.end() && 0 < lineNum; itr1++) {
        std::cout << itr1->airlineCode << "sheeeesh";
        lineNum--;
    }

}

