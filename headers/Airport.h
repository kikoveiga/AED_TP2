//
// Created by belchior on 28-12-2022.
//
#include <vector>
#include<string>

#ifndef AED_TP2_AIRPORT_H
#define AED_TP2_AIRPORT_H

class Airport {

private:
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    double latitude;
    double longitude;


public:

    /**
     * @brief Airport constructor
     * @param code string with the code of the airport
     * @param name string with the name of the airport
     * @param city string with the city of the airport
     * @param country string with the country of the airport
     * @param latitude double with the latitude of the airport
     * @param longitude double with the longitude of the airport
     */
    Airport(const std::string& code, const std::string& name, const std::string& city, const std::string& country, double latitude, double longitude);

    /**
     * @brief Get function for the code of the airport
     * @return string with the code of the airport
     */
    const std::string& getCode() const;

    /**
     * @brief Get function for the name of the airport
     * @return string with the name of the airport
     */
    const std::string& getName() const;

    /**
     * @brief Get function for the city of the airport
     * @return string with the city of the airport
     */
    const std::string& getCity() const;

    /**
     * @brief Get function for the country of the airport
     * @return string with the country of the airport
     */
    const std::string& getCountry() const;

    /**
     * @brief Get function for the latitude of the airport
     * @return double with the latitude of the airport
     */
    double getLatitude() const;

    /**
     * @brief Get function for the longitude of the airport
     * @return double with the longitude of the airport
     */
    double getLongitude() const;
};


#endif //AED_TP2_AIRPORT_H
