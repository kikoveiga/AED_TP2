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
            cout << "DO YOU WANT TO INCLUDE OR EXCLUDE AIRLINES? (0/1)\n";
            cin >> include;
            if (!include) {
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
            this->fm = FlightManager(include ,airlinesChosen);
            break;
        }
        case 2:{
            this->fm = FlightManager();
            break;
        }
        case 3:
            exit(0);
        default:
            cout << "Invalid command\n";
            build();
    }
    command = "0";
    run();
}
void Menu::run() {

    bool running = true;
    while (running) {
        switch(stoi(command)) {
            case 0:
                mainMenu();
                break;
            case 1:
                routeMenu();
                command = "0";
                break;
            case 2:
                airportMenu();
                command = "0";
                break;
            case 3:
                airlineMenu();
                command = "0";
                break;
            case 4:
                networkMenu();
                command = "0";
                break;
            case 5:
                build();
                running = false;
                break;
            case 6:
                exit(0);
        }
    }
}

void Menu::mainMenu() {
    cleanTerminal();
    cout << "-------------------------------------------------\n"
         << "|                 FLIGHT HELPER                 |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. BEST ROUTE                                 |\n"
         << "| 2. AIRPORT INFO                               |\n"
         << "| 3. AIRLINE INFO                               |\n"
         << "| 4. NETWORK STATS                              |\n"
         << "| 5. GO BACK TO BUILD                           |\n"
         << "| 6. EXIT                                       |\n"
         << "-------------------------------------------------\n";

    while (true) {
        cout << "   - OPTION: "; cin >> command;
        if ( 1 <= stoi(command) && stoi(command) <= 6) break;
        else cout << "   - INVALID OPTION" << endl;
    }
}


void Menu::routeMenu() {
    cout << "-------------------------------------------------\n"
         << "|      CHOOSE ONE OF THE FOLLOWING OPTIONS      |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. ROUTE FROM AIRPORT TO AIRPORT              |\n"
         << "| 2. ROUTE FROM CITY TO CITY                    |\n"
         << "| 3. ROUTE FROM AIRPORT TO CITY                 |\n"
         << "| 4. ROUTE FROM CITY TO AIRPORT                 |\n"
         << "| 5. ROUTE FROM COORDINATES                     |\n"
         << "| 6. EXIT                                       |\n"
         << "-------------------------------------------------\n";


    while (true){
        cout << "   - OPTION: "; cin >> command;
        if ( 1 <= stoi(command) && stoi(command) <= 6) break;
        else cout << "   - INVALID OPTION" << endl;
    }
    if (command  == "1"){
        string src, dest;
        cout << "WRITE SOURCE AIRPORT:";
        cin >> src;
        cout << "WRITE DESTINATION AIRPORT:";
        cin >> dest;
        set<pair<int, vector<string>>> bestPaths ;
        fm.getGraph().findBestPaths(src, dest, bestPaths);
        cout << "BEST ROUTES FROM " << src << " TO " << dest << ":\n";
        for (auto &bestPath : bestPaths) {
            cout << "- ROUTE :\n";
            cout << "    ";
            for (auto &airport : bestPath.second) {
                cout << airport << ' ' << fm.getGraph().getNodes().at(airport).airport->getName() << " --> ";
            }
            cout << "\b\b\b\b";
            cout << " DISTANCE: " << bestPath.first << " KM\n";
        }
        cout << "PRESS 0 TO CONTINUE";
        cin >> command;
        if (command == "0") routeMenu();
    }
    else if ( command == "2"){
        string src, dest;
        cout << "WRITE SOURCE CITY:";
        cin >> src;
        cout << "WRITE DESTINATION CITY:";
        cin >> dest;
        list<string> srcAirports = fm.getGraph().airportsInCity(src);
        list<string> destAirports = fm.getGraph().airportsInCity(dest);
        set<pair<int, vector<string>>> paths = {};
        set<pair<int, vector<string>>> bestPaths = {} ;
        for (auto &srcAirport : srcAirports) {
            for (auto &destAirport : destAirports) {
                fm.getGraph().findBestPaths(srcAirport, destAirport, paths);
                if (paths.begin()->second.size() > bestPaths.begin()->second.size()) bestPaths = paths;
            }
        }
        cout << "BEST ROUTES FROM " << src << " TO " << dest << ":\n";
        for (auto &bestPath : bestPaths) {
            cout << "- ROUTE :\n";
            cout << "    ";
            for (auto &airport : bestPath.second) {
                cout << airport << ' ' << fm.getGraph().getNodes().at(airport).airport->getName() << " --> ";
            }
            cout << "\b\b\b\b";
            cout << " DISTANCE: " << bestPath.first << " KM\n";

        }
        cout << "PRESS 0 TO CONTINUE";
        cin >> command;
        if (command == "0") routeMenu();

    }
    else if ( command == "3"){
        string src, dest;
        cout << "WRITE SOURCE AIRPORT:";
        cin >> src;
        cout << "WRITE DESTINATION CITY:";
        cin >> dest;
        set<pair<int, vector<string>>> bestPaths ;
        fm.getGraph().findBestPaths(src, dest, bestPaths);
        cout << "BEST ROUTES FROM " << src << " TO " << dest << ":\n";
        for (auto &bestPath : bestPaths) {
            cout << "- ROUTE :\n";
            cout << "    ";
            for (auto &airport : bestPath.second) {
                cout << airport << ' ' << fm.getGraph().getNodes().at(airport).airport->getName() << " --> ";
            }
            cout << "\b\b\b\b";
            cout << " DISTANCE: " << bestPath.first << " KM\n";
        }
        cout << "PRESS 0 TO CONTINUE";
        cin >> command;
        if (command == "0") routeMenu();

    }
}

void Menu::airportMenu() {

}

void Menu::airlineMenu() {

}

void Menu::networkMenu() {

}


