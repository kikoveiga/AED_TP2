//
// Created by kikoveiga on 07-01-2023.
//

#ifndef AED_TP2_MENU_H
#define AED_TP2_MENU_H

#include "FlightManager.h"
#include "../headers/Menu.h"
#include "../headers/FlightManager.h"
#include "../headers/Graph.h"

class Menu {

private:
    FlightManager fm;
    std::string command;

public:

    /**
     * @brief Menu constructor that initializes the flight manager and the command
     */
    explicit Menu();

    /**
     * @brief Function to run the build menu which handles arlines the user wants to add or remove from the graph
     */
    void build();

    /**
     * @brief Function to run the main loop that changes between the different menus
     */
    void run();

    /**
     * @brief Function to run the main menu
     */
    void mainMenu();

    /**
     * @brief Function to run the route menu
     */
    void routeMenu();

    /**
     * @brief Function to clear the screen
     */
    void cleanTerminal();

    /**
     * @brief Function to run the Airports menu
     */
    void airportMenu();

    /**
     * @brief Function to run the Airlines menu
     */
    void airlineMenu();

    /**
     * @brief Function to run the network menu
     */
    void networkMenu();
};

#endif //AED_TP2_MENU_H
