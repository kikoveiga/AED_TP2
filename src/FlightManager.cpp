//
// Created by belchior on 28-12-2022.
//

#include "../headers/FlightManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

FlightManager::FlightManager(bool include, const list<string>& airlinesChosen) {
    readAirportsFile();
    readAirlinesFile(include, airlinesChosen);
    readFlightsFile(include, airlinesChosen);
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
        graph.addNode(airport);
    }

}

void FlightManager::readAirlinesFile(bool include, const list<string>& airlinesChosen) {
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

        if (airlinesChosen.empty()) {
            auto* airline = new Airline(code, name, callsign, country);
            airlines.insert({code, airline});
            continue;
        }

        if (!include) {
            bool add = true;

            for (auto& i : airlinesChosen) {
                if (i == code) {
                    add = false;
                }
            }

            if (add) {
                auto* airline = new Airline(code, name, callsign, country);
                airlines.insert({code, airline});
            }
            continue;
        }

        for (auto& i : airlinesChosen) {
            if (i == code) {
                auto* airline = new Airline(code, name, callsign, country);
                airlines.insert({code, airline});
                continue;
            }
        }
    }
}

void FlightManager::readFlightsFile(bool include, const list<string>& airlinesChosen) {
    ifstream file("../dataset/flights.csv");
    string line;
    getline(file,line); // ignore first line

    while(getline(file,line)) {
        string source, target, airline ;
        stringstream input(line);
        getline(input, source, ',');
        getline(input, target, ',');
        getline(input, airline, '\r');

        if (airlinesChosen.empty()) {
            graph.addEdge(source, target, airline);
            continue;
        }

        if (!include) {

            bool add = true;

            for (auto& i : airlinesChosen) {
                if (i == airline) {
                    add = false;
                }
            }

            if (add) graph.addEdge(source, target, airline);

            continue;
        }

        for (auto& i : airlinesChosen) {
            if (i == airline) {
                graph.addEdge(source, target, airline);
                continue;
            }
        }
    }
}

Graph& FlightManager::getGraph() {
    return graph;
}

const unordered_map<std::string, Airline*>& FlightManager::getAirlines() const {
    return airlines;
}

