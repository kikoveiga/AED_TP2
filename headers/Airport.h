//
// Created by belchior on 28-12-2022.
//
#include <string>
#include <vector>
#include "Airline.h"



#ifndef AED_TP2_AIRPORT_H
#define AED_TP2_AIRPORT_H

class Airport {

private:
    std::string name;
    std::string city;
    std::string country;
    double latitude;
    double longitude;
    std::vector<Airline*> airlines;

public:
    Airport(const std::string& name, const std::string& city, const std::string& country, double latitude, double longitude);

    const std::string &getName() const;

    const std::string &getCity() const;

    const std::string &getCountry() const;

    double getLatitude() const;

    double getLongitude() const;


};


#endif //AED_TP2_AIRPORT_H
