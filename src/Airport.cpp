//
// Created by belchior on 28-12-2022.
//

#include "../headers/Airport.h"
using namespace std;


Airport::Airport(const string& name, const string& city, const string& country, double latitude, double longitude) {
    this->name = name;
    this->city = city;
    this->country = country;
    this->latitude = latitude;
    this->longitude = longitude;
}

const string &Airport::getName() const {
    return name;
}

const string &Airport::getCity() const {
    return city;
}

const string &Airport::getCountry() const {
    return country;
}

double Airport::getLatitude() const {
    return latitude;
}

double Airport::getLongitude() const {
    return longitude;
}
