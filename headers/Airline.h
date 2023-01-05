//
// Created by belchior on 29-12-2022.
//
#include <string>

#ifndef AED_TP2_AIRLINE_H
#define AED_TP2_AIRLINE_H


class Airline {
private:
    std::string name;
    std::string callsign;
    std::string country;


public:
    Airline(const std::string& name, const std::string& callsign, const std::string& country);
    const std::string &getName() const;
    const std::string &getCallsign() const;
    const std::string &getCountry() const;

};


#endif //AED_TP2_AIRLINE_H
