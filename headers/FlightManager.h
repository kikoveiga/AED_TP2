//
// Created by belchior on 28-12-2022.
//
#include <unordered_map>
#include<string>
#include "Airport.h"
#ifndef AED_TP2_FLIGHTMANAGER_H
#define AED_TP2_FLIGHTMANAGER_H


class FlightManager {
private:
    std::unordered_map<std::string, Airport> airports;
public:
    explicit FlightManager();
    void readAirportsFile();

    const std::unordered_map<std::string, Airport> &getAirports() const;

};


#endif //AED_TP2_FLIGHTMANAGER_H
