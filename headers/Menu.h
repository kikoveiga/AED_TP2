//
// Created by kikoveiga on 07-01-2023.
//

#ifndef AED_TP2_MENU_H
#define AED_TP2_MENU_H

#include "FlightManager.h"

class Menu {

private:
    FlightManager flightManager;
    std::string command;

public:
    explicit Menu(FlightManager& flightManager);
    void run();
    void mainMenu();

};

#endif //AED_TP2_MENU_H
