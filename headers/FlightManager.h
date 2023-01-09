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

    /**
     * @brief FlightManager constructor
     * @param include bool to choose whether to include or exclude certain airlines
     * @param airlines list with the airlines to include or exclude
     */
    explicit FlightManager(bool include = true, const std::list<std::string>& airlinesChosen = {});

    /**
     * @brief Function to read the airports.csv file and add the airports to the graph
     */
    void readAirportsFile();

    /**
     * @brief Function to read the airlines.csv file and add the airlines to the airlines map
     * @param include bool to choose whether to include or exclude certain airlines
     * @param airlines list with the airlines to include or exclude
     */
    void readAirlinesFile(bool include, const std::list<std::string>& airlinesChosen);

    /**
     * @brief Function to read the flights.csv file and add the flights to the graph
     * @param include bool to choose whether to include or exclude certain airlines
     * @param airlines list with the airlines to include or exclude
     */
    void readFlightsFile(bool include, const std::list<std::string>& airlinesChosen);

    /**
     * @brief Function to get the graph
     * @return graph
     */
    Graph& getGraph();

    /**
     * @brief Function to get the airlines map
     * @return airlines map
     */
    const std::unordered_map<std::string, Airline*>& getAirlines() const;

    /**
     * @brief Function to get the airlines from a certain country
     * @param country country to get the airlines from
     * @return list with the airlines from the country
     */
    std::list<std::string> getAirlinesFromCountry(const std::string& country);
};


#endif //AED_TP2_FLIGHTMANAGER_H
