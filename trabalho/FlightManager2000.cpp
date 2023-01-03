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


    Airline airline = Airline();

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

        airline = Airline(airlineCode, "", "", "");
        airlineName = airlines.find(airline)->getName();

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
    std::cout << "| 1 - Search flight airport to airport                     \n";
    std::cout << "| 2 - Search flight city to city                           \n";
    std::cout << "| 3 - Search flight city to airport                        \n";
    std::cout << "| 4 - Search flight airport to city                        \n";
    std::cout << "| 5 - Search by location                                   \n";
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
            std::string src, dest;
            std::cout << "|                                                          \n";
            std::cout << "| Write here the source city                           \n";
            std::cout << "| Enter here: ";
            std::cin >> src;
            std::cout << "| Write here the destination city                       \n";
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

                    airportsGraph.superBestFlightAtoB(src, dest, airlinesVector, 2);
                    break;
                }

                else if(airlineChoice == "no"){
                    airportsGraph.superBestFlightAtoB(src, dest, airlinesVector, 2);
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

        else if(choice == 3){
            std::string src, dest;
            std::cout << "|                                                          \n";
            std::cout << "| Write here the source city                               \n";
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

                    airportsGraph.superBestFlightAtoB(src, dest, airlinesVector, 3);
                    break;
                }

                else if(airlineChoice == "no"){
                    airportsGraph.superBestFlightAtoB(src, dest, airlinesVector, 3);
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

        else if(choice == 4){
            std::string src, dest;
            std::cout << "|                                                          \n";
            std::cout << "| Write here the source airport                            \n";
            std::cout << "| Enter here: ";
            std::cin >> src;
            std::cout << "| Write here the destination city                          \n";
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

                    airportsGraph.superBestFlightAtoB(src, dest, airlinesVector, 4);
                    break;
                }

                else if(airlineChoice == "no"){
                    airportsGraph.superBestFlightAtoB(src, dest, airlinesVector, 4);
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

        else if(choice == 5){
            double latitude,longitude;
            int range = 0;
            std::string dest;
            std::cout << "|                                                          \n";
            std::cout << "| Write here your latitude                                 \n";
            std::cout << "| Enter here: ";
            std::cin >> latitude;

            while (std::cin.eof()){
                std::cout << "| Not a valid input, please try again                      \n";
                std::cout << "|                                                          \n";
                latitude = 0.0;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            std::cout << "| Write here your longitude                                \n";
            std::cout << "| Enter here: ";
            std::cin >> longitude;

            while (std::cin.eof()){
                std::cout << "| Not a valid input, please try again                      \n";
                std::cout << "|                                                          \n";
                longitude = 0.0;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            std::cout << "| Write here your desired range                               \n";
            std::cout << "| Enter here: ";
            std::cin >> range;

            while (std::cin.eof()){
                std::cout << "| Not a valid input, please try again                      \n";
                std::cout << "|                                                          \n";
                range = 0.0;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

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

                    airportsGraph.locationShortestPath(latitude, longitude, range, dest, airlinesVector);
                    break;
                }

                else if(airlineChoice == "no"){
                    airportsGraph.locationShortestPath(latitude, longitude, range, dest, airlinesVector);
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
    airportsGraph.findArticulationPoints();
}

void FlightManager2000::airportRange() {
    std::string airportCode, airlineChoice, airlineString;
    int numFlights;
    std::vector<std::string> airlinesVector;

    std::cout << "|                                                          \n";
    std::cout << "| Write here the airport code                              \n";
    std::cout << "| Enter here: ";
    std::cin >> airportCode;
    std::cout << "| Write here the max flight number                         \n";
    std::cout << "| Enter here: ";
    std::cin >> numFlights;

    while (std::cin.eof()){
        std::cout << "| Not a valid input, please try again                      \n";
        std::cout << "|                                                          \n";
        numFlights = 0.0;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

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

            airportsGraph.printAirportRange(airportCode, numFlights, airlinesVector);
            break;
        }

        else if(airlineChoice == "no"){
            airportsGraph.printAirportRange(airportCode, numFlights, airlinesVector);
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
}


