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

            std::cout << "| There are a total of " + std::to_string(output.size()) + " destinations in " + airportCode + " airport, for a total of " + std::to_string(countries.size()) + " countries\n";
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

            std::cout << "| There are a total of " + std::to_string(output.size()) + " airlines operating in " + airportCode +
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

void Graph::numberFlightsInShortestPath(const std::string& src, std::vector<std::string>& airlines, std::vector<std::string> &airportsFound, int distance){
    for(auto itr = airports.begin();itr != airports.end();itr++) {
        itr->second.visited = false;
        itr->second.distance = -1;
    }
    std::queue<std::string> queue;
    airports[src].distance = 0;
    queue.push(src);
    airports[src].visited = true;
    while (!queue.empty()) {
        std::string current = queue.front();
        queue.pop();
        if(airports[current].distance >= distance) break;
        for (Edge &edge: airports[current].adj){
            std::string dest = edge.dest;
            if(!airports[dest].visited){
                airports[dest].distance = airports[current].distance +1;
                if(airlines.empty()){
                    airports[dest].visited = true;
                    airportsFound.push_back(dest);
                    queue.push(dest);
                }
                else if(std::find(airlines.begin(), airlines.end(),edge.airlineCode) != airlines.end()){
                    airports[dest].visited = true;
                    airportsFound.push_back(dest);
                    queue.push(dest);
                }
            }
        }
    }
}

void Graph::simpleShortestPath(const std::string& src, const std::string& destination, std::vector<std::string> &airlines) {
    if(airports.find(src) == airports.end()){
        std::cout << "|                                                          \n";
        std::cout << "| Error: Source airport doesn't exist in the data base!    \n";
        std::cout << "|                                                          \n";
        return;
    }

    if(airports.find(destination) == airports.end()){
        std::cout << "|                                                          \n";
        std::cout << "| Error: Destination airport doesn't exist in the data base!\n";
        std::cout << "|                                                          \n";
        return;
    }

    for(auto itr = airports.begin();itr != airports.end();itr++) {
        itr->second.visited = false;
    }
    std::unordered_map<std::string, std::string> predecessor;
    std::queue<std::string> queue;
    queue.push(src);
    airports[src].visited = true;

    while (!queue.empty()) {
        std::string current = queue.front();
        queue.pop();
        if(destination == current) break;
        for (Edge &edge: airports[current].adj){
            std::string dest = edge.dest;
            if(!airports[dest].visited){
                if(airlines.empty()){
                    queue.push(dest);
                    predecessor[dest] = current;
                    airports[dest].visited = true;

                }
                else if(std::find(airlines.begin(), airlines.end(),edge.airlineCode) != airlines.end()){
                    queue.push(dest);
                    predecessor[dest] = current;
                    airports[dest].visited = true;
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
            totalDistance += haversine(airports[*itr].latitude, airports[*itr].longitude,airports[*(itr-1)].latitude, airports[*(itr-1)].longitude);
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

void Graph::superBestFlightAtoB(const std::string& src, const std::string& dest, std::vector<std::string> airlines, int option) {
    std::vector<std::string> airportsInCitySrc;
    std::vector<std::string> airportsInCityDest;
    for(const auto& x:airports){
        if(option == 2){
            if(x.second.city == src) airportsInCitySrc.push_back(x.second.code);
            if(x.second.city == dest) airportsInCityDest.push_back(x.second.code);
        }

        else if(option == 3){
            if(x.second.city == src) airportsInCitySrc.push_back(x.second.code);
            }
        else if(option == 4){
            if(x.second.city == dest) airportsInCityDest.push_back(x.second.code);
            }
    }

    if((airportsInCitySrc.empty() && (option == 2 || option == 3)) || (airportsInCityDest.empty() && (option == 2 || option == 4))){
        std::cout << "|\n";
        std::cout << "| Error: Source city or destiny city doesn't exist in the database!\n";
    }

    else{
        std::string source; std::string destiny;
        if(option == 2 || option == 3){
            std::cout << "| Chose one of the following source airports:" << std::endl;
            for(const auto& airport: airportsInCitySrc) std::cout << "| " << airport << std::endl;
            while(true) {
                std::cout << "| Enter here: ";
                std::cin >> source;
                if (std::find(airportsInCitySrc.begin(), airportsInCitySrc.end(), source) == airportsInCitySrc.end()) {
                    std::cout << "| Error: Airport code is wrong! Try again\n";
                }
                else break;
            }
        }
        else{
            source = src;
        }

        if(option == 4 || option == 2) {
            std::cout << "| Chose one of the following destiny airports:" << std::endl;
            for(const auto& airport: airportsInCityDest) std::cout << "| " << airport << std::endl;
            while(true) {
                std::cout << "| Enter here: ";
                std::cin >> destiny;
                if (std::find(airportsInCityDest.begin(), airportsInCityDest.end(), destiny) == airportsInCityDest.end()) {
                    std::cout << "| Error: Airport code is wrong! Try again\n";
                }
                else break;
            }
        }

        else{
            destiny = dest;
        }

        simpleShortestPath(source,destiny,airlines);
    }
}

 void Graph::findArticulationPoints() {
     int choice1 = 0;
     int choice2 = 0;

     std::cout << "| Select two of the following options to create an\n"
                  "| interval of longitudes to see articulation airports:     \n";
     std::cout << "|                                                          \n";
     std::cout << "| 1 - Arctic Polar Circle                                  \n";
     std::cout << "| 2 - Tropic of Cancer                                     \n";
     std::cout << "| 3 - Equator                                              \n";
     std::cout << "| 4 - Tropic of Capricorn                                  \n";
     std::cout << "| 5 - Antarctic Polar Circle                               \n";
     std::cout << "| 6 - See them all                                         \n";
     std::cout << "|                                                          \n";

     while(true){
         while(true){
             std::cout << "| Enter here the 1st choice: ";
             std::cin >> choice1;

             if(std::cin.eof()){
                 std::cout << "| Not a valid input, please try again                      \n";
                 std::cout << "|                                                          \n";
                 choice1 = 0;
                 std::cin.clear();
                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             }

             else if(1 > choice1 || choice1 > 6){
                 std::cout << "| Error: First input inputs is invalid, try again!                   \n";
                 std::cout << "|                                                                     \n";
                 choice1 = 0;
                 std::cin.clear();
                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             }

             else break;
         }

         if(choice1 != 6){
             while(true){
                 std::cout << "| Enter here the 2nd choice: ";
                 std::cin >> choice2;

                 if(std::cin.eof()){
                     std::cout << "| Not a valid input, please try again                      \n";
                     std::cout << "|                                                          \n";
                     choice2 = 0;
                     std::cin.clear();
                     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                 }

                 else if(1 > choice2 || choice2 > 6 || choice2 == 6){
                     std::cout << "| Error: Second input is invalid, try again!                   \n";
                     std::cout << "|                                                                     \n";
                     choice2 = 0;
                     std::cin.clear();
                     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                 }

                 else break;
             }
         }
         break;
     }

     std::list<Graph::Airport> answer;
     std::list<Graph::Airport> answer2;

     for (auto &node : airports) {
         node.second.visited = false;
         node.second.low = -1;
         node.second.num = -1;
     }
     int order = 1;
     for (auto &nodes : airports)
         if (!nodes.second.visited)
             dfs_articulation_points(nodes, order, answer);

             /*
             longitude
             tropicOfCancer = 23.439;
             tropicOfCapricorn = -23.439;
             equator = 0;
             arcticPolarCircle = 66.33493;
             antarcticPolarCircle = -66.33493;
             */

     std::vector<std::pair<std::string, double>> latitudes;
     latitudes.push_back({"Arctic Polar Circle", 66.335});
     latitudes.push_back({"Tropic of Cancer", 23.439});
     latitudes.push_back({"Equator", 0.000});
     latitudes.push_back({"Tropic of Capricorn", -23.439});
     latitudes.push_back({"Antarctic Polar Circle", -66.335});

     if(choice1 != 6) {
         for (const Airport &airport: answer) {
             if (airport.latitude >= std::min(latitudes[choice1 - 1].second, latitudes[choice2 - 1].second) and
                 airport.latitude <= std::max(latitudes[choice1 - 1].second, latitudes[choice2 - 1].second)) {
                 answer2.push_back(airport);
             }
         }
         std::cout << "| There were found " + std::to_string(answer2.size()) + " connection airports between " +
                      latitudes[choice1 - 1].first + " and " + latitudes[choice2 - 1].first + "\n";
     }

     else {
         std::cout << "| There were found " + std::to_string(answer.size()) + " connection airports\n";
     }

     std::cout << "| Do you wish to see them all?\n";
     std::cout << "| Do you wish to see any of them? ('yes'/'no?)?\n";
     std::string printChoice;

     while (true) {
         std::cout << "| Enter here :";
         std::cin >> printChoice;

         if (printChoice == "yes" && choice1 != 6) {
             std::cout << "| Here are the connection airports between " + latitudes[choice1 - 1].first + " and " +
                          latitudes[choice2 - 1].first + ":\n";
             for (const Airport &airport: answer2) {
                 std::cout << "| Airport Name: " + airport.name + "; Airport Code: " + airport.code +
                              "; Airport Location: " + std::to_string(airport.latitude) + ", " +
                              std::to_string(airport.longitude) + '\n';
             }
             std::cout << "|\n";
             break;
         } else if (printChoice == "yes" && choice1 == 6) {
             std::cout << "| Here are the connection airports" << ":\n";
             for (const Airport &airport: answer) {
                 std::cout << "| Airport Name: " + airport.name + "; Airport Code: " + airport.code +
                              "; Airport Location: " + std::to_string(airport.latitude) + ", " +
                              std::to_string(airport.longitude) + '\n';
             }
             std::cout << "|\n";
             break;
         } else if (printChoice == "no") break;

         else {
             std::cout << "| Not a valid input, please try again                      \n";
             std::cout << "|                                                          \n";
             printChoice = "";
             std::cin.clear();
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
         }
     }
}


void Graph::locationShortestPath(double latitude, double longitude, int range, const std::string& dest, std::vector<std::string>& airlines) {
    std::vector<std::pair<std::string,int>> output;
    double dist;
    for(auto itr = airports.begin(); itr != airports.end(); itr++){
        dist = haversine(latitude, longitude, itr->second.latitude, itr->second.longitude);
        if(dist <= range){
            output.push_back({itr->second.code,(int)dist});
        }
    }
    if(output.empty()){
        std::cout << "| \n";
        std::cout << "| Error: For the given data, no airports were found!\n";
    }

    else{
        std::string src;
        std::vector<std::string> srcAirports;
        std::cout << "| \n";
        std::cout << "| The following airports were found. Select one for departure:\n";
        for(const std::pair<std::string,int>& pair : output){
            srcAirports.push_back(pair.first);
            std::cout << "| Code: " + pair.first + "; Distance to you: " + std::to_string(pair.second) + " km\n";
        }

        while(true) {
            std::cout << "| Enter here: ";
            std::cin >> src;
            if (std::find(srcAirports.begin(), srcAirports.end(), src) == srcAirports.end()) {
                std::cout << "| Error: Airport code is wrong! Try again\n";
            }
            else break;
        }

        simpleShortestPath(src,dest,airlines);
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

void Graph::printAirportRange(const std::string& airportCode, int numFlights, std::vector<std::string> &airlines) {
    std::vector<std::string> airportsFound;
    std::set<std::string> cities;
    std::set<std::string> countries;
    for (auto &node : airports) {
        node.second.visited = false;
        node.second.distance = 0;
    }
    if (airports.find(airportCode) == airports.end()) {
        std::cout << "| \n";
        std::cout << "| Error: The given airport code doesn't exist in the database!\n";
        std::cout << "| \n";
    } else {
        std::string printChoice;

        numberFlightsInShortestPath(airportCode, airlines, airportsFound, numFlights);

        for (auto itr = airportsFound.begin(); itr != airportsFound.end(); itr++) {
            cities.insert(airports[*itr].city);
            countries.insert(airports[*itr].country);
        }
        std::cout << "| \n";
        std::cout << "| There were found " + std::to_string(airportsFound.size()) + " airports, " +
                     std::to_string(cities.size()) + " cities and " +
                     std::to_string(countries.size()) + " countries within " + std::to_string(numFlights) +
                     " flights from airport " + airportCode + '\n';
        std::cout << "| Do you wish to see any of them? ('airports'/'cities'/'countries'/'no?)?\n";
        while (true) {
            std::cout << "| Enter here:";
            std::cin >> printChoice;

            if (printChoice == "airports") {
                std::sort(airportsFound.begin(), airportsFound.end());
                std::cout << "| Here are the found airports:\n";
                for (const std::string &string: airportsFound) {
                    std::cout << "| " + string + '\n';
                }
                std::cout << "|\n";
                break;
            } else if (printChoice == "cities") {
                std::cout << "| Here are the found cities:\n";
                for (const std::string &string: cities) {
                    std::cout << "| " + string + '\n';
                }
                std::cout << "|\n";
                break;
            } else if (printChoice == "countries") {
                std::cout << "| Here are the found countries:\n";
                for (const std::string &string: countries) {
                    std::cout << "| " + string + '\n';
                }
                std::cout << "|\n";
                break;
            }
            else if(printChoice == "no") {
                std::cout << "|\n";
                break;
            }
            else {
                std::cout << "| Not a valid input, please try again                      \n";
                std::cout << "|                                                          \n";
                printChoice = "";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
}

