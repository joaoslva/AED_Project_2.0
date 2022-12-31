#include <iostream>
#include <ctime>
#include <limits>
#include "headers/FlightManager2000.h"

int main() {

    FlightManager2000 flightManager2000 = FlightManager2000();
    flightManager2000.addAirports("../../trabalho/dataset/airports.csv");
    flightManager2000.addAirlines("../../trabalho/dataset/airlines.csv");
    flightManager2000.addEdges("../../trabalho/dataset/flights.csv");
    flightManager2000.bestFlightAtoB();
    //flightManager2000.test1();
}

/*
void check(bool& condition){
    std::string checkChoice;
    while(true){
        std::cout << "| Do you wish to use this functionality again or go back?  \n";
        std::cout << "| Write 'stay' to use it again, 'back' to go back          \n";
        std::cout << "|                                                          \n";
        std::cout << "| Enter here: ";
        std::cin >> checkChoice;
        std::cout << "|                                                          \n";

        if(checkChoice == "stay"){
            break;
        }

        else if(checkChoice == "back"){
            condition = false;
            std::cout << " ---------------------------------------------------------- \n";
            std::cout << "|                                                          \n";
            break;
        }

        else{
            std::cout << "| Not a valid input, please try again                      \n";
            std::cout << "|                                                          \n";
            std::cout << "| Enter here: ";
            checkChoice = "";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int main() {
    bool running = true;
    time_t now = time(nullptr);
    tm* localtm = localtime(&now);

    std::cout << " __________________________________________________________ \n";
    std::cout << "|                                                          \n";
    std::cout << "| Welcome to Duovago, your flight search engine!           \n";
    std::cout << "| Please select one of the following options and enjoy     \n";
    std::cout << "| your search!                                             \n";

    FlightManager2000 flightManager2000 = FlightManager2000();
    flightManager2000.addAirports("../../trabalho/dataset/airports.csv");
    flightManager2000.addAirlines("../../trabalho/dataset/airlines.csv");
    flightManager2000.addEdges("../../trabalho/dataset/flights.csv");

    if(!flightManager2000.checkFileOpening()){
        running = false;
        std::cout << "|                                                          \n";
        std::cout << "| Oops! Something went wrong while opening the files       \n";
        std::cout << "| Please check the file paths in the source code and       \n";
        std::cout << "| restart the program.                                     \n";
        std::cout << "|                                                          \n";
        std::cout << " ---------------------------------------------------------- \n";
    }
    std::cout << "|                                                          \n";

    while(running){
        int choice = 0;
        std::cout << "| 1 - Best Flight To                                       \n";
        std::cout << "| 2 - Connection Airports                                  \n";
        std::cout << "| 3 - Airport Flights                                      \n";
        std::cout << "| 4 - Airport Airlines                                     \n";
        std::cout << "| 5 - Airport Range                                        \n";
        std::cout << "| 6 - Help page                                            \n";
        std::cout << "| 7 - Quit the program                                     \n";
        std::cout << "|                                                          \n";
        std::cout << "| Enter here your choice: ";
        std::cin >> choice;
        std::cout << "|                                                          \n";

        if(choice == 1){
            bool bestFlightToRunning = true;
            std::cout << "|----------------------Best Flight To----------------------\n";
            std::cout << "|                                                          \n";
            while(bestFlightToRunning){
                flightManager2000.bestFlightAtoB();
                check(bestFlightToRunning);
            }
        }

        else if(choice == 2){
            std::cout << "|-------------------Connection Airports--------------------\n";
            std::cout << "|                                                          \n";
        }

        else if(choice == 3){
            bool airportFlightsRunning = true;
            std::cout << "|----------------------Airport Flights---------------------\n";
            std::cout << "|                                                          \n";
            while (airportFlightsRunning){
                flightManager2000.airportFlights();
                check(airportFlightsRunning);
            }
        }

        else if(choice == 4){
            bool airportAirlinesRunning = true;
            std::cout << "|---------------------Airport Airlines---------------------\n";
            std::cout << "|                                                          \n";
            while(airportAirlinesRunning){
                flightManager2000.airportAirLines();
                check(airportAirlinesRunning);
            }
        }

        else if(choice == 5){
            std::cout << "|----------------------Airport Range-----------------------\n";
            std::cout << "|                                                          \n";
        }

        else if(choice == 6){
            std::string helpChoice;
            bool helpRunning = true;
            std::cout << "|------------------------Help Page-------------------------\n";
            std::cout << "|                                                          \n";
            std::cout << "| How each functionality works                             \n";
            std::cout << "|                                                          \n";
            std::cout << "| Best Flight To:                                          \n";
            std::cout << "| Connection Airports: This function shows you airports    \n";
            std::cout << "|    in a specified region that are connection points;\n";
            std::cout << "| Airport Flights: This function shows you all the         \n";
            std::cout << "|    destinations for a specified airport;\n";
            std::cout << "| Airport Airlines: This function shows you all the        \n";
            std::cout << "|    airlines that operate in a specified airport;\n";
            std::cout << "| Airport Range:                                           \n";
            std::cout << "|                                                          \n";
            std::cout << "| You can type 'back' mid search to go back one page       \n";
            std::cout << "|                                                          \n";
            std::cout << "| Write 'back' to go to the main menu                      \n";
            std::cout << "| Enter here: ";

            while(helpRunning){
                std::cin >> helpChoice;
                if(helpChoice == "back"){
                    helpRunning = false;
                }
                else{
                    std::cout << "| Not a valid input, please try again                      \n";
                    std::cout << "|                                                          \n";
                    std::cout << "| Enter here: ";
                    helpChoice = "";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }

            std::cout << "|                                                          \n";
            std::cout << "|----------------------------------------------------------\n";
            std::cout << "|                                                          \n";
            std::cout << "| Select one of the following functionalities              \n";
            std::cout << "|                                                          \n";
        }

        else if(choice == 7){
            std::cout << "| Thanks for using Duovago!                                \n";
            std::cout << "|                                                          \n";
            std::cout << " ---------------------------------------------------------- \n";
            running = false;
        }

        else{
            std::cout << "| Not a valid input, please try again                      \n";
            std::cout << "|                                                          \n";
            choice = 0;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return 0;
}
*/