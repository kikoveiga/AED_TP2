//
// Created by belchior on 28-12-2022.
//
#include <unordered_map>
#include<string>
#include "Airport.h"
#include "Graph.h"

#ifndef AED_TP2_FLIGHTMANAGER_H
#define AED_TP2_FLIGHTMANAGER_H


class FlightManager {
private:

    Graph* airports;
public:
    explicit FlightManager();
    void readAirportsFile();
    void readAirlinesFile();

    Graph *getAirports() const;


};


#endif //AED_TP2_FLIGHTMANAGER_H
