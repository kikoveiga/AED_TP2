//
// Created by belchior on 28-12-2022.
//
#include <unordered_map>
#include<string>
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

#ifndef AED_TP2_FLIGHTMANAGER_H
#define AED_TP2_FLIGHTMANAGER_H


class FlightManager {
private:
    Graph graph;
    std::unordered_map<std::string, Airline*> airlines;
public:
    explicit FlightManager(bool include = true, const std::list<std::string>& airlinesChosen = {});
    void readAirportsFile();
    void readAirlinesFile(bool include, const std::list<std::string>& airlinesChosen);
    void readFlightsFile(bool include, const std::list<std::string>& airlinesChosen);

    Graph& getGraph();
    const std::unordered_map<std::string, Airline*>& getAirlines() const;
};


#endif //AED_TP2_FLIGHTMANAGER_H
