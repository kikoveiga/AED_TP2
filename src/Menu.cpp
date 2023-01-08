//
// Created by kikoveiga on 07-01-2023.
//

#include <iostream>
#include <string>
#include "../headers/Menu.h"
using namespace std;

bool isNumerical(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool isDouble(const string& s) {
    int counterDot = 0;
    int counterNumber = 0;
    bool afterDot = false;

    for (char c : s) {
        if (!isdigit(c) && c != '.') return false;

        if (c == '.') counterDot++;
        else {
            if(counterDot == 1) afterDot = true;
            counterNumber++;
        }
    }
    return (counterDot == 1 && counterNumber > 0 && afterDot);
}

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
         << "| 2. CONTINUE TO MAIN MENU                      |\n"
         << "-------------------------------------------------\n";
    while (true) {
        cout << "   - OPTION: "; cin >> command;
        if (isNumerical(command) && 1 <= stoi(command) && stoi(command) <= 2) break;
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
         << "| 1. ROUTE MENU                                 |\n"
         << "| 2. AIRPORTS MENU                              |\n"
         << "| 3. AIRLINES MENU                              |\n"
         << "| 4. GLOBAL STATISTICS                          |\n"
         << "| 5. BACK TO BUILD MENU                         |\n"
         << "| 6. EXIT                                       |\n"
         << "-------------------------------------------------\n";

    while (true) {
        cout << "   - OPTION: "; cin >> command;
        if (isNumerical(command) && 1 <= stoi(command) && stoi(command) <= 6) break;
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
         << "| 6. GO BACK                                    |\n"
         << "-------------------------------------------------\n";


    while (true){
        cout << "   - OPTION: "; cin >> command;
        if (isNumerical(command) && 1 <= stoi(command) && stoi(command) <= 6) break;
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
         << "|                 AIRPORTS MENU                 |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. SEARCH AIRPORTS                            |\n"
         << "| 2. NUMBER OF AIRPORTS                         |\n"
         << "| 3. TOP N AIRPORTS WITH MOST FLIGHTS           |\n"
         << "| 4. AIRPORTS FROM CITY                         |\n"
         << "| 5. AIRPORTS FROM COUNTRIES                    |\n"
         << "| 6. AIRPORTS FROM COORDINATES                  |\n"
         << "| 7. GO BACK                                    |\n"
         << "-------------------------------------------------\n";
    while (true){
        cout << "   - OPTION: "; cin >> command;
        if (isNumerical(command) && 1 <= stoi(command) && stoi(command) <= 6) break;
        else cout << "   - INVALID OPTION" << endl;
    }
    if (command == "1"){
        string code;
        while (true) {
            cout << "   - ENTER AIRPORT CODE: "; cin >> code;
            if (fm.getGraph().getNodes().find(code) != fm.getGraph().getNodes().end()) break;
            else cout << "   - AIRPORT NOT FOUND" << endl;
        }
        auto& airport = fm.getGraph().getNodes().at(code).airport;

        cout << "   - AIRPORT " << code << " FOUND" << endl;
        cout << "   - AIRPORT NAME: " << airport->getName()<< endl;
        cout << "   - AIRPORT CITY: " << airport->getCity() << endl;
        cout << "   - AIRPORT COUNTRY: " << airport->getCountry() << endl;
        cout << "   - AIRPORT COORDINATES: " << airport->getLatitude() << " " << airport->getLongitude() << endl;

        while(true) {
            cout << "PRESS 0 TO CONTINUE"; cin >> command;
            if (command == "0") airportMenu();
        }
    }
    else if (command == "2") {
        cout << "NUMBER OF AIRPORTS: " << fm.getGraph().getNodes().size() << endl;
        cout << "PRESS 0 TO CONTINUE";
        cin >> command;
        if (command == "0") airportMenu();
    }
    else if (command == "3") {
        int n;
        while (true) {
            cout << "WRITE N: ";
            cin >> n;
            if (n > 0) break;
            cout << "   - INVALID N" << endl;
        }
        set<pair<int, string>> airports_n_flights;
        for(auto &i : fm.getGraph().getNodes()){
            airports_n_flights.insert({fm.getGraph().getNumberFlightsFromAirport(i.first), i.first});
        }

        cout << "TOP " << n << " AIRPORTS WITH MOST FLIGHTS:\n";
        auto it = airports_n_flights.rbegin();
        for (int i = 0; i < n; i++) {
            cout << "- " << it->second << ' ' << fm.getGraph().getNodes().at(it->second).airport->getName() << " (" << it->first << " FLIGHTS)" << endl;
            it++;
        }

        while(true) {
            cout << "PRESS 0 TO CONTINUE"; cin >> command;
            if (command == "0") airportMenu();
        }
    }
    else if (command == "4") {
        string city;
        while (true) {
            cout << "WRITE CITY: ";
            cin >> city;
            if (!fm.getGraph().getAirportsInCity(city).empty()) break;
            cout << "   - INVALID CITY" << endl;
        }
        list<string> airports_city = fm.getGraph().getAirportsInCity(city);

        cout << "AIRPORTS FROM CITY " << city << ":\n";
        for (auto &i : airports_city) {
            cout << "- " << i << ' ' << fm.getGraph().getNodes().at(i).airport->getName() << endl;
        }
        cout << "PRESS 0 TO CONTINUE";
        while(true) {
            cout << "PRESS 0 TO CONTINUE"; cin >> command;
            if (command == "0") airportMenu();
        }
    }
    else if (command == "5") {
        string country;
        while (true) {
            cout << "WRITE COUNTRY: ";
            cin >> country;
            if (!fm.getGraph().getAirportsInCountry(country).empty()) break;
            cout << "   - INVALID COUNTRY" << endl;
        }
        list<string> airports_country = fm.getGraph().getAirportsInCountry(country);

        cout << "AIRPORTS FROM COUNTRY " << country << ":\n";
        for (auto &i : airports_country) {
            cout << "- " << i << ' ' << fm.getGraph().getNodes().at(i).airport->getName() << endl;
        }

        while(true) {
            cout << "PRESS 0 TO CONTINUE"; cin >> command;
            if (command == "0") airportMenu();
        }
    }
    else if (command == "6") {
        while (true) {
            cout << "   - ENTER LATITUDE: "; cin >> command;

            if (isNumerical(command) && stod(command) >= -90 && stod(command) <= 90) break;
            else cout << "   - INVALID LATITUDE" << endl;
        }

        double lat = stod(command);

        while (true) {
            cout << "   - ENTER LONGITUDE: "; cin >> command;
            if ( isNumerical(command) && stod(command) >= -180 && stod(command) <= 180) break;
            else cout << "   - INVALID LONGITUDE" << endl;
        }

        double lon = stod(command);

        while (true) {
            cout << "   - ENTER RADIUS: "; cin >> command;
            if ( isNumerical(command) && stod(command) >= 0) break;
            else cout << "   - INVALID RADIUS" << endl;
        }

        double rad = stod(command);

        auto airports = fm.getGraph().getAirportsNearLocation(lat, lon, rad);
        cout << "   - AIRPORTS FROM COORDINATES (" << lat << ", " << lon << ") WITH RADIUS " << rad << "KM" << endl;
        for (auto& airport : airports) {
            cout << "   - " << airport.second << " - " << airport.first << "KM" << endl;
        }
        cout << "PRESS 0 TO CONTINUE";
        cin >> command;
        if (command == "0") airportMenu();
        while(true) {
            cout << "PRESS 0 TO CONTINUE"; cin >> command;
            if (command == "0") airportMenu();
        }
    }
    else if (command == "7") mainMenu();
    else {
        cout << "   - INVALID COMMAND" << endl;
        airportMenu();
    }
}

void Menu::airlineMenu() {
    cleanTerminal();
    cout << "-------------------------------------------------\n"
         << "|                 AIRLINES MENU                 |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. SEARCH AIRLINE                             |\n"
         << "| 2. TOP N AIRLINES WITH MOST FLIGHTS           |\n"
         << "| 3. NUMBER OF AIRLINES                         |\n"
         << "| 4. AIRLINES FROM COUNTRY                      |\n"
         << "| 5. GO BACK                                    |\n"
         << "-------------------------------------------------\n";

    while (true) {
        cout << "   - OPTION: ";
        cin >> command;
        if (1 <= stoi(command) && stoi(command) <= 6) break;
        else cout << "   - INVALID OPTION" << endl;
    }

    if (command == "1") { // Search Airline

        while (true) {
            cout << "   - ENTER AIRLINE CODE: ";
            cin >> command;
            if (fm.getAirlines().find(command) != fm.getAirlines().end()) break;
            else cout << "   - AIRLINE NOT FOUND" << endl;
        }
        auto &airline = fm.getAirlines().at(command);

        cout << "   - AIRLINE " << command << " FOUND" << endl;
        cout << "   - AIRLINE NAME: " << airline->getName() << endl;
        cout << "   - AIRLINE CALLSIGN: " << airline->getCallsign() << endl;
        cout << "   - AIRLINE COUNTRY: " << airline->getCountry() << endl;

        while (true) {
            cout << "PRESS 0 TO CONTINUE";
            cin >> command;
            if (command == "0") airlineMenu();
        }

    } else if (command == "2") { // Top N Airlines with most flights
        while (true) {
            cout << "   - ENTER N: ";
            cin >> command;
            if (stoi(command) > 0) break;
            else cout << "   - INVALID NUMBER" << endl;
        }

        int n = stoi(command);
        auto airlines = fm.getAirlines();
        set<pair<int, string>> topAirlines = {};

        cout << "   - TOP " << n << " AIRLINES WITH MOST FLIGHTS" << endl;
        for (auto &airline: airlines) {
            topAirlines.insert({airline.second->getNFlights(), airline.first});
        }

        int i = 0;

        auto it = topAirlines.rbegin();

        while (i < n && it != topAirlines.rend()) {
            cout << "   - " << it->second << " - " << it->first << " FLIGHTS" << endl;
            i++;
            it++;
        }

        while (true) {
            cout << "PRESS 0 TO CONTINUE";
            cin >> command;
            if (command == "0") airlineMenu();
        }

    } else if (command == "3") { // Number of Airlines
        cout << "   - NUMBER OF AIRLINES: " << fm.getAirlines().size() << endl;
        while (true) {
            cout << "PRESS 0 TO CONTINUE";
            cin >> command;
            if (command == "0") airlineMenu();
        }

    } else if (command == "4") { // Airlines from Country

        while (true) {
            cout << "   - ENTER COUNTRY: ";
            cin >> command;
            if (fm.getAirlinesFromCountry(command).size() > 0) break;
            else cout << "   - NO AIRLINES FROM THIS COUNTRY FOUND" << endl;
        }
        list<string> airlines = fm.getAirlinesFromCountry(command);
        cout << "   - AIRLINES FROM " << command << endl;
        for (auto &airline: airlines) {
            cout << "   - " << airline << endl;
        }

        while (true) {
            cout << "PRESS 0 TO CONTINUE";
            cin >> command;
            if (command == "0") airlineMenu();
        }

    } else if (command == "5") { // Go Back
        mainMenu();
    } else if (command == "6") { // Exit
        exit(0);
    }
}

void Menu::networkMenu() {
    cleanTerminal();
    cout << "-------------------------------------------------\n"
         << "|                 NETWORK MENU                  |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. NUMBER OF AIRPORTS                         |\n"
         << "| 2. NUMBER OF AIRLINES                         |\n"
         << "| 3. NUMBER OF ROUTES                           |\n"
         << "| 4. GO BACK                                    |\n"
         << "-------------------------------------------------\n";
}


