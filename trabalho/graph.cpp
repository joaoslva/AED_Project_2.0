#include <utility>

#include "headers/graph.h"

double haversine(double lat1, double lon1, double lat2, double lon2){
    double dLat = (lat2 - lat1) *
    M_PI / 180.0;
    double dLon = (lon2 - lon1) *
    M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
    pow(sin(dLon / 2), 2) *
    cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return round(rad * c);
}

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
        struct result{
            std::string airportCode;
            std::string airportName;
            double distance;
        };

        std::string airportFlightsChoice;
        std::cout << "| Please enter an airport code                             \n";
        std::cout << "| Enter here: ";
        std::cin >> airportCode;
        std::cout << "|                                                          \n";

        if(airportCode == "back"){
            break;
        }

        AirportsItr itr1 = airports.find(airportCode);

        if(itr1 == airports.end()){
            std::cout << "| Airport doesn't exist in the database                    \n";
            std::cout << "|                                                          \n";
            airportFlightsRunning = false;
        }

        else{
            std::vector<result> output;

            for(auto itr2 = itr1->second.adj.begin(); itr2 != itr1->second.adj.end(); itr2++){
                if(std::find_if(output.begin(), output.end(), [&] (const result& element) {return element.airportCode == itr2->dest;}) == output.end()) {
                    double distance = haversine(itr1->second.latitude, itr1->second.longitude, airports.find(itr2->dest)->second.latitude, airports.find(itr2->dest)->second.longitude);
                    output.push_back({itr2->dest, airports.find(itr2->dest)->second.name, distance});
                }
            }

            std::sort(output.begin(), output.end(), [](const result& element1, const result& element2) {return element1.airportName < element2.airportName;});
            std::cout << "| Here are the flight destinations in " + airportCode + " airport:      |\n";
            std::cout << "|                                                          |\n";

            for(const result& result: output){
                std::cout << "| Destination: " + result.airportName + "; Airport Code: " + result.airportCode +"; Distance: " + std::to_string((int)result.distance) + " km\n";
            }

            airportFlightsRunning = false;
        }
    }
    std::cout << "|                                                          \n";
}

void Graph::printAirportAirlines() {
    bool airportAirlinesRunning = true;
    std::string airportCode;

    while(airportAirlinesRunning){
        std::string airportFlightsChoice;
        std::cout << "| Please enter an airport code                             \n";
        std::cout << "| Enter here: ";
        std::cin >> airportCode;
        std::cout << "|                                                          \n";

        if(airportCode == "back"){
            break;
        }

        AirportsItr itr1 = airports.find(airportCode);

        if(itr1 == airports.end()){
            std::cout << "| Airport doesn't exist in the database                    |\n";
            std::cout << "|                                                          |\n";
            airportAirlinesRunning = false;
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
            airportAirlinesRunning = false;
        }
    }
    std::cout << "|                                                          |\n";
}

