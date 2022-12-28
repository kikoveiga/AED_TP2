//
// Created by belchior on 28-12-2022.
//

#include "../headers/FlightManager.h"
#include "../headers/Airport.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

FlightManager::FlightManager() {
    readAirportsFile();
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
        getline(input, longitude, ',');

        auto *airport_ = new Airport( name, city, country, stod(latitude), stod(longitude));
        airports.insert({code, *airport_});

    }

}

const unordered_map<std::string, Airport> &FlightManager::getAirports() const {
    return airports;
}
