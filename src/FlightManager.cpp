//
// Created by belchior on 28-12-2022.
//

#include "../headers/FlightManager.h"
#include "../headers/Airport.h"
#include "../headers/Calc.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

FlightManager::FlightManager() {
    readAirportsFile();
    readAirlinesFile();
    readFlightsFile();
}

void FlightManager::readAirportsFile() {

    ifstream file("../dataset/airports.csv");
    string line;
    getline(file,line); // ignore first line

    while(getline(file,line)){
        string code, name, city, country, latitude, longitude;
        stringstream input(line);
        getline(input, code, ',');
        getline(input, name, ',');
        getline(input, city, ',');
        getline(input, country, ',');
        getline(input, latitude, ',');
        getline(input, longitude, '\r');

        auto* airport = new Airport(code, name, city, country, stod(latitude), stod(longitude));
        airports.addNode(airport);
    }

}

void FlightManager::readAirlinesFile() {
    ifstream file("../dataset/airlines.csv");
    string line;
    getline(file,line); // ignore first line

    while(getline(file,line)) {
        string code, name, callsign, country;
        stringstream input(line);
        getline(input, code, ',');
        getline(input, name, ',');
        getline(input, callsign, ',');
        getline(input, country, '\r');

        auto* airline = new Airline(  name, callsign, country);
        airlines.insert({code, *airline});
    }
}

void FlightManager::readFlightsFile() {
    ifstream file("../dataset/flights.csv");
    string line;
    getline(file,line); // ignore first line

    while(getline(file,line)) {
        string source, target, airline ;
        stringstream input(line);
        getline(input, source, ',');
        getline(input, target, ',');
        getline(input, airline, '\r');
        Airport* source_airport = airports.getNodes().at(source).airport;
        Airport* target_airport = airports.getNodes().at(target).airport;
        double distance = haversine(source_airport->getLatitude(), source_airport->getLongitude(), target_airport->getLatitude(), target_airport->getLongitude());
        airports.addEdge(source, target, airline, distance);
    }
}

const Graph FlightManager::getAirports() const {
    return airports;
}

const unordered_map<std::string, Airline> &FlightManager::getAirlines() const {
    return airlines;
}
