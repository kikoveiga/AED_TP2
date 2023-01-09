//
// Created by belchior on 29-12-2022.
//
#include <string>

#ifndef AED_TP2_AIRLINE_H
#define AED_TP2_AIRLINE_H


class Airline {

private:

    std::string code;
    std::string name;
    std::string callsign;
    std::string country;
    unsigned nFlights = 0;


public:

    /**
     * @brief Airline constructor
     * @param code string with the code of the airline
     * @param name string with the name of the airline
     * @param callsign string with the callsign of the airline
     * @param country string with the country of the airline
     */
    Airline(const std::string& code, const std::string& name, const std::string& callsign, const std::string& country);

    /**
     * @brief Get function for the code of the airline
     * @return string with the code of the airline
     */
    const std::string& getCode() const;

    /**
     * @brief Get function for the name of the airline
     * @return string with the name of the airline
     */
    const std::string& getName() const;

    /**
     * @brief Get function for the callsign of the airline
     * @return string with the callsign of the airline
     */
    const std::string& getCallsign() const;

    /**
     * @brief Get function for the country of the airline
     * @return string with the country of the airline
     */
    const std::string& getCountry() const;

    /**
     * @brief Get function for the number of flights of the airline
     * @return unsigned with the number of flights of the airline
     */
    unsigned getNFlights() const;

    /**
     * @brief Function to increment the number of flights of the airline
     */
    void addFlight();
};

#endif //AED_TP2_AIRLINE_H
