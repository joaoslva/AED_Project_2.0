cmake_minimum_required(VERSION 3.24)
project(trabalho)

set(CMAKE_CXX_STANDARD 23)

add_executable(trabalho main.cpp Airport.cpp headers/Airport.h Airline.cpp headers/Airline.h FlightManager2000.cpp headers/FlightManager2000.h graph.cpp)
