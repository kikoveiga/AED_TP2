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
    FlightManager flightManager;
    std::string command;

public:
    explicit Menu();
    void run();
    void build();
    void mainMenu();
    void cleanTerminal();

    void menu1();

};

#endif //AED_TP2_MENU_H
