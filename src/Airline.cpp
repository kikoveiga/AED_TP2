//
// Created by belchior on 29-12-2022.
//

#include "../headers/Airline.h"

using namespace std;

Airline::Airline(const string& code, const string& name, const string& callsign, const string& country) {
    this->code = code;
    this->name = name;
    this->callsign = callsign;
    this->country = country;
}
const string& Airline::getCode() const {
    return code;
}

const string& Airline::getName() const {
    return name;
}

const string& Airline::getCallsign() const {
    return callsign;
}

const string& Airline::getCountry() const {
    return country;
}

unsigned Airline::getNFlights() const {
    return nFlights;
}

void Airline::addFlight() {
    nFlights++;
}
