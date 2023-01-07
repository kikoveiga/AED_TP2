//
// Created by kikoveiga on 07-01-2023.
//

#include "../headers/Menu.h"

Menu::Menu(FlightManager* flightManager) {
    this->flightManager = flightManager;
    this->command = "0";
}

void Menu::run() {

    bool running = true;

    while (running) {
        switch(stoi(command)) {

            case 0:
                mainMenu();
                break;

            case 10:
                system("cls");
                running = false;
                break;
        }
    }

}

