//
// Created by kikoveiga on 07-01-2023.
//

#include <iostream>
#include <string>
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
         << "|                  BUILD MENU                   |\n"
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
         << "|                   MAIN MENU                   |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. BEST ROUTE                                 |\n"
         << "| 2. AIRPORTS INFO                              |\n"
         << "| 3. AIRLINES INFO                              |\n"
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
    cleanTerminal();
    cout << "-------------------------------------------------\n"
         << "|                  ROUTE MENU                   |\n"
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
    if (command  == "1"){ // Airport->Airport
        string src, dest;
        while (true) {
            cout << "WRITE SOURCE Airport:";
            cin >> src;
            if (fm.getGraph().getNodes().find(src) != fm.getGraph().getNodes().end()) break;
            cout << "   - INVALID CITY" << endl;
        }
        while (true) {
            cout << "WRITE DESTINATION Airport:";
            cin >> dest;
            if (fm.getGraph().getNodes().find(dest) != fm.getGraph().getNodes().end()) break;
            cout << "   - INVALID CITY" << endl;
        }
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

    else if ( command == "2"){ // City->City
        string src, dest;
        list<string> srcAirports;
        list<string> destAirports;

        while (true) {
            cout << "WRITE SOURCE CITY:";
            getline(cin >> ws, src);
            srcAirports = fm.getGraph().getAirportsInCity(src);
            if (!srcAirports.empty()) break;
            cout << "   - INVALID CITY" << endl;
        }
        while (true) {
            cout << "WRITE DESTINATION CITY:";
            getline(cin >> ws, dest);
            destAirports = fm.getGraph().getAirportsInCity(dest);
            if (!destAirports.empty()) break;
            cout << "   - INVALID CITY" << endl;
        }

        set<pair<int, vector<string>>> paths = {};
        pair<int, vector<string>> bestPath = {0, {}} ;
        for (auto &srcAirport : srcAirports) {
            for (auto &destAirport : destAirports) {
                fm.getGraph().findBestPaths(srcAirport, destAirport, paths);
                if (bestPath.first == 0 || paths.begin()->second.size() < bestPath.second.size()) bestPath = *paths.begin();
            }
        }
        cout << "BEST ROUTES FROM " << src << " TO " << dest << ":\n";
        cout << "- ROUTE :\n";
        cout << "    ";
        for (auto &airport : bestPath.second) {
            cout << airport << ' ' << fm.getGraph().getNodes().at(airport).airport->getName() << " --> ";
        }
        cout << "\b\b\b\b\n";
        cout << "    DISTANCE " << bestPath.first << " KM\n";
        cout << "PRESS 0 TO CONTINUE";
        cin >> command;
        if (command == "0") routeMenu();

    }
    else if ( command == "3"){ // Aiport->City
        string src, dest;
        list<string> destAirports;
        while (true) {
            cout << "WRITE SOURCE Airport:";
            cin >> src;
            if (fm.getGraph().getNodes().find(src) != fm.getGraph().getNodes().end()) break;
            cout << "   - INVALID CITY" << endl;
        }
        while (true) {
            cout << "WRITE DESTINATION CITY:";
            getline(cin >> ws, dest);
            destAirports = fm.getGraph().getAirportsInCity(dest);
            if (!destAirports.empty()) break;
            cout << "   - INVALID CITY" << endl;
        }

        set<pair<int, vector<string>>> paths = {};
        pair<int, vector<string>> bestPath = {0, {}} ;
        for (auto &destAirport : destAirports) {
            fm.getGraph().findBestPaths(src, destAirport, paths);
            if (bestPath.first == 0 || paths.begin()->second.size() < bestPath.second.size()) bestPath = *paths.begin();
        }
        cout << "BEST ROUTES FROM " << fm.getGraph().getNodes().at(src).airport->getName() << " TO " << dest << ":\n";
        cout << "- ROUTE :\n";
        cout << "    ";
        for (auto &airport : bestPath.second) {
            cout << airport << ' ' << fm.getGraph().getNodes().at(airport).airport->getName() << " --> ";
        }
        cout << "\b\b\b\b\n";
        cout << "    DISTANCE " << bestPath.first << " KM\n";
        cout << "PRESS 0 TO CONTINUE";
        cin >> command;
        if (command == "0") routeMenu();

    }
    else if ( command == "4"){ // City->Airport
        string src, dest;
        list<string> srcAirports;
        while (true) {
            cout << "WRITE SOURCE CITY:";
            getline(cin >> ws, src);
            srcAirports = fm.getGraph().getAirportsInCity(src);
            if (!srcAirports.empty()) break;
            cout << "   - INVALID CITY" << endl;
        }
        while (true) {
            cout << "WRITE DESTINATION Airport:";
            cin >> dest;
            if (fm.getGraph().getNodes().find(dest) != fm.getGraph().getNodes().end()) break;
            cout << "   - INVALID CITY" << endl;
        }

        set<pair<int, vector<string>>> paths = {};
        pair<int, vector<string>> bestPath = {0, {}} ;
        for (auto &srcAirport : srcAirports) {
            fm.getGraph().findBestPaths(srcAirport, dest, paths);
            if (bestPath.first == 0 || paths.begin()->second.size() < bestPath.second.size()) bestPath = *paths.begin();
        }
        cout << "BEST ROUTES FROM " << src << " TO " << fm.getGraph().getNodes().at(dest).airport->getName() << ":\n";
        cout << "- ROUTE :\n";
        cout << "    ";
        for (auto &airport : bestPath.second) {
            cout << airport << ' ' << fm.getGraph().getNodes().at(airport).airport->getName() << " --> ";
        }
        cout << "\b\b\b\b\n";
        cout << "    DISTANCE " << bestPath.first << " KM\n";
        cout << "PRESS 0 TO CONTINUE";
        cin >> command;
        if (command == "0") routeMenu();

    }
    else if ( command == "5"){ // Coordinates->Coordinates
        double src_lat, src_lon, src_rad, dest_lat, dest_lon, dest_rad;
        set<pair<int, string>> srcAirports;
        set<pair<int, string>> destAirports;
        while (true) {
            cout << "WRITE SOURCE LATITUDE:";
            cin >> src_lat;
            if (isdigit(src_lat)){
                cout << "INVALID LATITUDE";
                break;
            }
            cout << "WRITE SOURCE LONGITUDE:";
            cin >> src_lon;
            if (isdigit(src_lon)){
                cout << "INVALID LONGITUDE";
                break;
            }
            cout << "WRITE SOURCE RADIUS:";
            cin >> src_rad;
            if (isdigit(isdigit(src_rad))){
                cout << "INVALID RADIUS";
                break;
            }
            cout << "WRITE DESTINATION LATITUDE:";
            cin >> dest_lat;
            if (isdigit(dest_lat)){
                cout << "INVALID LATITUDE";
                break;
            }
            cout << "WRITE DESTINATION LONGITUDE:";
            cin >> dest_lon;
            if (isdigit(dest_lon)){
                cout << "INVALID LONGITUDE";
                break;
            }
            cout << "WRITE DESTINATION RADIUS:";
            cin >> dest_rad;
            if (isdigit(dest_rad)){
                cout << "INVALID RADIUS";
                break;
            }
            break;
        }
        srcAirports = fm.getGraph().getAirportsNearLocation(src_lat, src_lon, src_rad);
        destAirports = fm.getGraph().getAirportsNearLocation(dest_lat, dest_lon, dest_rad);
        set<pair<int, vector<string>>> paths = {};
        pair<int, vector<string>> bestPath = {0, {}} ;
        for (auto &srcAirport : srcAirports) {
            for (auto &destAirport : destAirports) {
                fm.getGraph().findBestPaths(srcAirport.second, destAirport.second, paths);
                if (bestPath.first == 0 || paths.begin()->second.size() < bestPath.second.size()) bestPath = *paths.begin();
            }
        }
        string src = *bestPath.second.begin();
        string dest = *bestPath.second.rbegin();
        int dist_s, dist_d;
        for (auto &i : srcAirports) if (i.second == src) dist_s = i.first;
        for (auto &j : destAirports) if (j.second == dest) dist_d = j.first;

        cout << "BEST ROUTES FROM " << src << " (DISTANCE FROM COORDINATES " <<  dist_s << "KM)"
        << " TO " << dest << " DISTANCE FROM COORDINATES " <<  dist_d << "KM):\n";
        cout << "- ROUTE :\n";
        cout << "    ";
        for (auto &airport : bestPath.second) {
            cout << airport << ' ' << fm.getGraph().getNodes().at(airport).airport->getName() << " --> ";
        }

        cout << "\b\b\b\b\n";
        cout << "PRESS 0 TO CONTINUE";
        cin >> command;
        if (command == "0") routeMenu();



    }
}

void Menu::airportMenu() {
    cleanTerminal();
    cout << "-------------------------------------------------\n"
         << "|                   AIRPORT MENU                |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. NUMBER OF AIRPORTS                         |\n"
         << "| 2. AIRPORTS FROM CITY                         |\n"
         << "| 3. AIRPORTS FROM COUNTRIES                    |\n"
         << "| 4. AIRPORTS FROM COORDINATES                  |\n"
         << "| 5. GO BACK TO BUILD                           |\n"
         << "| 6. EXIT                                       |\n"
         << "-------------------------------------------------\n";

}

void Menu::airlineMenu() {

}

void Menu::networkMenu() {

}


