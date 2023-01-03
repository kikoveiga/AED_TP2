//
// Created by belchior on 29-12-2022.
//

#include "../headers/Airline.h"

Airline::Airline(const std::string &name, const std::string &callsign, const std::string &country) {
    this->name = name;
    this->callsign = callsign;
    this->country = country;
}

const std::string &Airline::getName() const {
    return name;
}

const std::string &Airline::getCallsign() const {
    return callsign;
}

const std::string &Airline::getCountry() const {
    return country;
}
