#include "headers/FlightManager2000.h"

void FlightManager2000::addAirports(const std::string& pathName) {
    std::string name;
    std::string city;
    std::string country;
    std::string code;
    double latitude;
    double longitude;

    int count = 0;

    std::ifstream file;
    file.open(pathName);


    for(std::string line; getline(file, line);){
        if(count == 0){
            count++;
            continue;
        }

        std::stringstream inputString(line);
        std::string data;

        getline(inputString, data, ',');
        code = data;
        getline(inputString, data, ',');
        name = data;
        getline(inputString, data, ',');
        city = data;
        getline(inputString, data, ',');
        country = data;
        getline(inputString, data, ',');
        latitude = std::stod(data);
        getline(inputString, data, '\r');
        longitude = std::stod(data);

        airportsGraph.addAirport(code, name, city, country, latitude, longitude);
    }
}

void FlightManager2000::addAirlines(const std::string& pathName) {
    std::string code;
    std::string name;
    std::string callSign;
    std::string country;

    int count = 0;

    std::ifstream file;
    file.open(pathName);

    Airline airline = Airline();

    for(std::string line; std::getline(file, line);){
        if(count == 0){
            count++;
            continue;
        }

        std::stringstream inputString(line);
        std::string data;

        std::getline(inputString, data, ',');
        code = data;
        std::getline(inputString, data, ',');
        name = data;
        std::getline(inputString, data, ',');
        callSign = data;
        std::getline(inputString, data, '\r');
        country = data;

        airline = Airline(code, name, callSign, country);

        airlines.insert(airline);
    }
}

void FlightManager2000::addEdges(const std::string &pathName) {
    std::string src;
    std::string dest;
    std::string airlineCode;
    std::string airlineName;


    int count = 0;

    std::ifstream file;
    file.open(pathName);

    Airline airline1 = Airline();
    Airline airline2 = Airline();

    for(std::string line; std::getline(file, line);){
        if(count == 0){
            count++;
            continue;
        }

        std::stringstream inputString(line);
        std::string data;

        std::getline(inputString, data, ',');
        src = data;
        std::getline(inputString, data, ',');
        dest = data;
        std::getline(inputString, data, '\r');
        airlineCode = data;

        airline2 = Airline(airlineCode,"","","");
        airlineName = airlines.find(airline2)->getName();

        airportsGraph.addEdge(src, dest, airlineCode, airlineName);
    }
}

void FlightManager2000::bestFlightAtoB() {
    int choice = 0;
    std::string airlineChoice;
    std::string airlineString;
    std::vector<std::string> airlinesVector;

    std::cout << "| Select one of the following options:                     \n";
    std::cout << "|                                                          \n";
    std::cout << "| 1 - Simple search                                        \n";
    std::cout << "| 2 - Search by city                                       \n";
    std::cout << "| 3 - Search by location                                   \n";
    std::cout << "|                                                          \n";
    std::cout << "| Enter here: ";
    std::cin >> choice;

    while(std::cin.eof()){
        std::cout << "| Not a valid input, please try again                      \n";
        std::cout << "|                                                          \n";
        std::cout << "| Enter here: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    while(true){
        if(choice == 1){
            std::string src, dest;
            std::cout << "|                                                          \n";
            std::cout << "| Write here the source airport                            \n";
            std::cout << "| Enter here: ";
            std::cin >> src;
            std::cout << "| Write here the destination airport                       \n";
            std::cout << "| Enter here: ";
            std::cin >> dest;

            while(true){
                std::cout << "| Do you wish to specify any airlines to flight on?        \n";
                std::cout << "| Enter here ('yes'/'no'): ";
                std::cin >> airlineChoice;

                if(airlineChoice == "yes"){
                    std::cout << "|                                                          \n";
                    std::cout << "| Write 'stop' after you inserted all the wished airline   \n";

                    while(true){
                        std::cout << "| Enter here a airline code: ";
                        std::cin >> airlineString;

                        if(airlineString == "stop") break;

                        airlinesVector.push_back(airlineString);
                    }
                    Airline airlineHelper;
                    bool exit = false;

                    for(const std::string& airlineCode : airlinesVector){
                        airlineHelper = Airline(airlineCode, "", "", "");
                        if(std::find(airlines.begin(), airlines.end(), airlineHelper) == airlines.end()){
                            exit = true;
                            break;
                        }
                    }

                    if(exit){
                        std::cout << "|                                                          \n";
                        std::cout << "| Error: One or more airlines given don´t exist in the database!\n";
                        break;
                    }

                    airportsGraph.simpleShortestPath(src, dest, airlinesVector);
                    break;
                }

                else if(airlineChoice == "no"){
                    airportsGraph.simpleShortestPath(src, dest, airlinesVector);
                    break;
                }

                else{
                    std::cout << "| Not a valid input, please try again                      \n";
                    std::cout << "|                                                          \n";
                    airlineChoice = "";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            break;
        }

        else if(choice == 2){
            break;
        }

        else if(choice == 3){
            break;
        }
    }
}

bool FlightManager2000::checkFileOpening(){
    return airportsGraph.airportsSize() > 0 && airlinesSize() > 0 && airportsGraph.airportsSize() > 0;
}

void FlightManager2000::airportAirLines() {
    airportsGraph.printAirportAirlines();
}

void FlightManager2000::airportFlights(){
    airportsGraph.printAirportFlights();
}

void FlightManager2000::connectionAirport() {

}


