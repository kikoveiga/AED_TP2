cmake_minimum_required(VERSION 3.24)
project(AED_TP2)

set(CMAKE_CXX_STANDARD 17)

add_executable(AED_TP2 src/main.cpp headers/FlightManager.h src/FlightManager.cpp src/Airport.cpp headers/Airline.h src/Airline.cpp headers/Graph.h src/Graph.cpp)
