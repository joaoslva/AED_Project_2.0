#include <utility>
#include <unordered_set>
#include <queue>

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

void Graph::addEdge(const std::string& src, std::string dest, std::string airlineCode, std::string airlineName) {
    if (airports.find(src) == airports.end()) return;
    airports[src].adj.push_back({dest , airlineCode, airlineName });
}

void Graph::printAirportFlights() {
    bool airportFlightsRunning = true;
    std::string airportCode;

    struct result{
        std::string airportCode;
        std::string airportName;
        double distance;
    };

    while(airportFlightsRunning){
        std::string airportFlightsChoice;
        std::cout << "| Please enter an airport code                             \n";
        std::cout << "| Enter here: ";
        std::cin >> airportCode;
        std::cout << "|                                                          \n";

        if(airportCode == "back"){
            break;
        }

        auto itr1 = airports.find(airportCode);

        if(itr1 == airports.end()){
            std::cout << "| Error: Airport doesn't exist in the database             \n";
            std::cout << "|                                                          \n";
            airportFlightsRunning = false;
        }

        else{
            std::string outputChoice;
            std::vector<result> output;
            std::vector<std::string> countries;
            double distance;

            for(auto itr2 = itr1->second.adj.begin(); itr2 != itr1->second.adj.end(); itr2++){
                if(std::find_if(output.begin(), output.end(), [&] (const result& element) {return element.airportCode == itr2->dest;}) == output.end()) {
                    if(std::find(countries.begin(), countries.end(), airports.find(itr2->dest)->second.country) == countries.end()){
                        countries.push_back(airports.find(itr2->dest)->second.country);
                    }
                    distance = haversine(itr1->second.latitude, itr1->second.longitude, airports.find(itr2->dest)->second.latitude, airports.find(itr2->dest)->second.longitude);
                    output.push_back({itr2->dest, airports.find(itr2->dest)->second.name, distance});
                }
            }

            std::cout << "| There are a total of " + std::to_string(output.size()) + " destinations in " + airportCode + " airport,\n";
            std::cout << "| for a total of " + std::to_string(countries.size()) + " countries\n";
            std::cout << "| Do you wish to see them all?                             \n";

            while(true){
                std::cout << "| Enter here ('yes'/'no'): ";
                std::cin >> outputChoice;

                if(outputChoice == "yes"){
                    std::sort(output.begin(), output.end(), [](const result& element1, const result& element2) {return element1.airportName < element2.airportName;});
                    std::cout << "|                                                          \n";
                    std::cout << "| Here are the flight destinations in " + airportCode + " airport:      \n";
                    std::cout << "|                                                          \n";

                    for(const result& result: output){
                        std::cout << "| Destination: " + result.airportName + "; Airport Code: " + result.airportCode +"; Distance: " + std::to_string((int)result.distance) + " km\n";
                    }
                    break;
                }

                else if(outputChoice == "no"){
                    break;
                }

                else if(std::cin.eof()){
                    std::cout << "| Not a valid input, please try again                      \n";
                    std::cout << "|                                                          \n";
                    outputChoice = "";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                else{
                    std::cout << "| Not a valid input, please try again                      \n";
                    std::cout << "|                                                          \n";
                    outputChoice = "";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            airportFlightsRunning = false;
        }
    }
    std::cout << "|                                                          \n";
}

void Graph::printAirportAirlines() {
    bool airportAirlinesRunning = true;
    std::string airportCode;

    while (airportAirlinesRunning) {
        std::string airportFlightsChoice;
        std::cout << "| Please enter an airport code                             \n";
        std::cout << "| Enter here: ";
        std::cin >> airportCode;
        std::cout << "|                                                          \n";

        if (airportCode == "back") {
            break;
        }

        auto itr1 = airports.find(airportCode);

        if (itr1 == airports.end()) {
            std::cout << "| Airport doesn't exist in the database                    \n";
            std::cout << "|                                                          \n";
            airportAirlinesRunning = false;
        } else {
            std::vector<std::pair<std::string, std::string>> output;
            std::string outputChoice;

            for (auto itr2 = itr1->second.adj.begin(); itr2 != itr1->second.adj.end(); itr2++) {
                if (std::find_if(output.begin(), output.end(), [&](const std::pair<std::string, std::string> &element) {
                    return element.first == itr2->airLineName;
                }) == output.end()) {
                    output.push_back({itr2->airLineName, itr2->airlineCode});
                }
            }

            std::cout << "| There are a total of " + std::to_string(output.size()) + " destinations in " + airportCode +
                         " airport\n";
            std::cout << "| Do you wish to see them all?                             \n";

            while (true) {
                std::cout << "| Enter here ('yes'/'no'): ";
                std::cin >> outputChoice;
                
                if(outputChoice == "yes"){
                    sort(output.begin(), output.end(), [](const std::pair<std::string, std::string> &element1,
                                                          const std::pair<std::string, std::string> &element2) {
                        return element1.first < element2.first;
                    });

                    std::cout << "|                                                          \n";
                    std::cout << "| Here are the airlines that operate in " + airportCode + " airport:       \n";
                    std::cout << "|                                                          \n";

                    for (const std::pair<std::string, std::string> &pair: output) {
                        std::cout << "| Name: " + pair.first + "; Code: " + pair.second + '\n';
                    }
                    break;
                }
                
                else if(outputChoice == "no"){
                    break;
                }
                
                else if(std::cin.eof()){
                    std::cout << "| Not a valid input, please try again                      \n";
                    std::cout << "|                                                          \n";
                    outputChoice = "";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                
                else{
                    std::cout << "| Not a valid input, please try again                      \n";
                    std::cout << "|                                                          \n";
                    outputChoice = "";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            airportAirlinesRunning = false;
        }
    }
    std::cout << "|                                                          \n";
}    

int Graph::airportsSize() {
    return airports.size();
}

int Graph::numberFlightsInShortestPath(const std::string& src, const std::string& destination){
    std::unordered_map<std::string, std::string> predecessor;
    std::queue<std::string> queue;
    airports[src].distance = 0;
    queue.push(src);
    airports[src].visited = true;

    while (!queue.empty()) {
        std::string current = queue.front();
        queue.pop();
        if(destination == current) break;
        for (Edge &edge: airports[current].adj){
            std::string dest = edge.dest;
            if(!airports[dest].visited){
                airports[dest].distance = airports[current].distance +1;
                predecessor[dest] = current;
                airports[dest].visited = true;
                queue.push(dest);
            }
        }
    }

    std::vector<std::string> path;
    std::string curr = destination;

    while (curr != src){
        path.push_back(curr);
        curr = predecessor[curr];
    }

    path.push_back(src);
    std::reverse(path.begin(),path.end());
    return (int) path.size();
}

void Graph::simpleShortestPath(const std::string& src, const std::string& destination, std::vector<std::string> &airlines) {
    if(airports.find(src) == airports.end()){
        std::cout << "|                                                          \n";
        std::cout << "| Error: Source airport doesn't exist in the data base!    \n";
        std::cout << "|                                                          \n";
    }

    if(airports.find(destination) == airports.end()){
        std::cout << "|                                                          \n";
        std::cout << "| Error: Destination airport doesn't exist in the data base!\n";
        std::cout << "|                                                          \n";
    }

    for(auto itr = airports.begin();itr != airports.end();itr++) {
        itr->second.visited = false;
        itr->second.distance = -1;
    }
    std::unordered_map<std::string, std::string> predecessor;
    std::queue<std::string> queue;
    airports[src].distance = 0;
    queue.push(src);
    airports[src].visited = true;

    while (!queue.empty()) {
        std::string current = queue.front();
        queue.pop();
        if(destination == current) break;
        for (Edge &edge: airports[current].adj){
            std::string dest = edge.dest;
            if(!airports[dest].visited){
                airports[dest].distance = airports[current].distance +1;
                predecessor[dest] = current;
                airports[dest].visited = true;
                if(airlines.empty())
                    queue.push(dest);
                else if(std::find(airlines.begin(), airlines.end(),edge.airlineCode) != airlines.end()){
                    queue.push(dest);
                }
            }
        }
    }

    std::vector<std::string> path;
    std::string curr = destination;
    if(predecessor.find(destination) != predecessor.end()){
        while (curr != src){
            path.push_back(curr);
            curr = predecessor[curr];
        }
    }

    else{
        std::cout << "|                                                          \n";
        std::cout << "| Error: With the specified airlines there isn't a way to  \n";
        std::cout << "|        reach the destination airport!";
        return;
    }

    path.push_back(src);
    std::reverse(path.begin(),path.end());

    double totalDistance = 0;
    std::cout << "|                                                          \n";
    std::cout << "| Here's the shortest flight path from " + src + " to " + destination + " airports:\n";
    std::cout << "|                                                          \n";
    std::cout << "| ";
    for(auto itr = path.begin(); itr != path.end(); itr++){
        if(itr != path.begin()){
            totalDistance += haversine(airports.find(*(itr-1))->second.latitude, airports.find(*(itr-1))->second.longitude, airports.find(*(itr))->second.latitude, airports.find(*(itr))->second.longitude);
        }

        if(itr != path.end() - 1){
            std::cout << *itr + " -> ";
        }

        else{
            std::cout << *itr + '\n';
        }
    }
    std::cout << "|                                                          \n";
    std::cout << "| The total flight distance is " + std::to_string((int) totalDistance) + " km\n";
}

 void Graph::findArticulationPoints() {
    std::list<Graph::Airport> answer;
    for (auto &node : airports) {
        node.second.visited = false;
        node.second.parent = -1;
        node.second.low = -1;
        node.second.num = -1;
    }

    int order = 1;
    for (auto &nodes : airports)
        if (!nodes.second.visited)
            dfs_articulation_points(nodes, order, answer);

    // longitude
    double tropicOfCancer = 23.439;
    double tropicOfCapricorn = -23.439;
    double equator = 0;
    double arcticPolarCircle = 66.33493;
    double antarcticPolarCircle = -66.33493;

    for (const Airport& airport : answer) {
        std::cout << airport.name << '\n';
        std::cout << airport.longitude << '\n';
        std::cout << airport.latitude << '\n';
        std::cout << airport.code << '\n';
    }
}

void Graph::dfs_articulation_points(std::pair<const std::basic_string<char>, Graph::Airport> &v, int &order, std::list<Graph::Airport> &l) {
    v.second.visited = true;
    v.second.num = v.second.low = order++;

    int children = 0;
    bool articulation = false;

    for (Edge &e : v.second.adj) {
        std::string w = e.dest;
        auto itr = airports.find(w);
        if (!itr->second.visited) {
            children++;
            dfs_articulation_points(*itr, order, l);
            v.second.low = std::min(v.second.low, itr->second.low);
            if (itr->second.low >= v.second.num) articulation = true;
        }
        else
            v.second.low = std::min(v.second.low, itr->second.num);
    }

    if ((v.second.num == 1 && children > 1) || (v.second.num > 1 && articulation))
        l.push_front(v.second);
}


void istoéoprintparaoconnectionairports(){
    int choice = 0;

    std::cout << "| Select one of the following options:                     \n";
    std::cout << "|                                                          \n";
    std::cout << "| 1 - Connection airports between the Antarctic Polar Circle\n";
    std::cout << "|        and the Tropic of Capricorn                       \n";
    std::cout << "| 2 - Connection airports between the Tropic of Capricorn  \n";
    std::cout << "|        and the Equator                                   \n";
    std::cout << "| 3 - Connection airports between the Equator and the      \n";
    std::cout << "|        Tropic of Cancer                                  \n";
    std::cout << "| 4 - Connection airports between the Tropic of Cancer     \n";
    std::cout << "|        and the Arctic Polar Circle                       \n";
    std::cout << "|                                                          \n";

    while(true){
        std::cout << "| Enter here: ";
        std::cin >> choice;

        if(choice == 1){
            break;
        }

        else if(choice == 2){
            break;
        }

        else if(choice == 3){
            break;
        }

        else if(choice == 4){

        }

        else if(std::cin.eof()){
            std::cout << "| Not a valid input, please try again                      \n";
            std::cout << "|                                                          \n";
            choice = 0;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        else{
            std::cout << "| Not a valid input, please try again                      \n";
            std::cout << "|                                                          \n";
            choice = 0;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}