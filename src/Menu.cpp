//
// Created by kikoveiga on 07-01-2023.
//

#include <iostream>
#include "../headers/Menu.h"
using namespace std;

Menu::Menu() {
    this->command = "0";
}

void Menu::cleanTerminal() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void Menu::build(){
    cleanTerminal();
    cout << "-------------------------------------------------\n"
         << "|                     BUILD                     |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. INCLUDE/EXCLUDE AIRLINES                   |\n"
         << "| 2. CONTINUE                                   |\n"
         << "| 3. EXIT                                       |\n"
         << "-------------------------------------------------\n";
    while (true) {
        cout << "   - OPTION: "; cin >> command;
        if ( 1 <= stoi(command) && stoi(command) <= 3) break;
        else cout << "   - INVALID OPTION" << endl;
    }
    switch(stoi(command)) {
        case 1:{

            bool include;
            std::list<std::string> airlinesChosen;
            cout << "DO YOU WANT TO INCLUDE OR EXCLUDE AIRLINES? (1/0)\n";
            cin >> include;
            if (include) {
                cout << "ENTER THE AIRLINES YOU WANT TO INCLUDE (ENTER 0 TO FINISH):\n";
                string airline;
                cin >> airline;
                while (airline != "0") {
                    airlinesChosen.push_back(airline);
                    cin >> airline;
                }
            } else {
                cout << "ENTER THE AIRLINES YOU WANT TO EXCLUDE (ENTER 0 TO FINISH):\n";
                string airline;
                cin >> airline;
                while (airline != "0") {
                    airlinesChosen.push_back(airline);
                    cin >> airline;
                }
            }
            break;
        }
        case 2:{
            this->flightManager = FlightManager();
            run();
            break;
        }
        case 3:
            exit(0);
        default:
            cout << "Invalid command\n";
            build();
    }

    run();
}
void Menu::run() {

    bool running = true;
    while (running) {
        switch(stoi(command)) {
            case 1:
                mainMenu();
                break;
            case 2:
                running = false;
                break;

            case 10:
                running = false;
                break;
        }
    }
}

void Menu::mainMenu() {
    cleanTerminal();
    cout << "-------------------------------------------------\n"
         << "|                 FLIGHT HELPER                 |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. CHOOSE ROUTE                               |\n"
         << "| 2. AIRPORT STATS                              |\n"
         << "| 3. AIRLINE STATS                              |\n"
         << "| 4. NETWORK STATS                              |\n"
         << "| 5.                                            |\n"
         << "| 6. EXIT                                       |\n"
         << "-------------------------------------------------\n";
    while (true) {
        cout << "   - OPTION: "; cin >> command;
        if ( 1 <= stoi(command) && stoi(command) <= 7) break;
        else cout << "   - INVALID OPTION" << endl;
    }
}


void Menu::menu1() {
    cout << "-------------------------------------------------\n"
         << "|                 FLIGHT HELPER                 |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. CHOOSE ROUTE                               |\n"
         << "| 2. AIRPORT STATS                              |\n"
         << "| 3. AIRLINE STATS                              |\n"
         << "| 4. NETWORK STATS                              |\n"
         << "| 5.                                            |\n"
         << "| 6. EXIT                                       |\n"
         << "-------------------------------------------------\n";
    while (true) {
        cout << "   - OPTION: "; cin >> command;
        if ( 1 <= stoi(command) && stoi(command) <= 7) break;
        else cout << "   - INVALID OPTION" << endl;
    }
}


