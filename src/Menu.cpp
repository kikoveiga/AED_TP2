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
    bool negative = false;

    for (char c : s) {

        if (!isdigit(c) && c != '.' && c != '-') return false;
        if (c == '-' && (negative || counterNumber)) return false;


        if (c == '-') negative = true;
        else if (c == '.') counterDot++;
        else {
            if(counterDot == 1) afterDot = true;
            counterNumber++;
        }
    }
    if (!counterDot) afterDot = true;
    return (counterDot <= 1 && counterNumber > 0 && afterDot);
}

Menu::Menu() {
    this->command = "5";
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
            list<string> airlinesChosen;

            while (true) {
                cout << "DO YOU WANT TO INCLUDE OR EXCLUDE AIRLINES? (0/1)\n";cin >> command;
                if (command == "0" || command == "1") break;
            }

            if (command == "0") include = true;
            else include = false;

            if (include) {
                cout << "ENTER THE AIRLINES YOU WANT TO INCLUDE (PRESS 0 TO FINISH):\n";
                string airline;
                cin >> airline;
                while (airline != "0") {
                    airlinesChosen.push_back(airline);
                    cin >> airline;
                }
            } else {
                cout << "ENTER THE AIRLINES YOU WANT TO EXCLUDE (PRESS 0 TO FINISH):\n";
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
                break;
            case 2:
                airportMenu();
                break;
            case 3:
                airlineMenu();
                break;
            case 4:
                networkMenu();
                break;
            case 5:
                build();
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
         << "| 5. ROUTE FROM LOCATION TO LOCATION            |\n"
         << "| 6. SEARCH FLIGHT                              |\n"
         << "| 7. GO BACK                                    |\n"
         << "-------------------------------------------------\n";


    while (true) {
        cout << "   - OPTION: "; cin >> command;
        if (isNumerical(command) && 1 <= stoi(command) && stoi(command) <= 7) break;
        else cout << "   - INVALID OPTION" << endl;
    }
    if (command  == "1"){ // Airport->Airport
        string src, dest;
        while (true) {
            cout << "ENTER SOURCE AIRPORT: ";
            cin >> src;
            if (fm.getGraph().getNodes().find(src) != fm.getGraph().getNodes().end()) break;
            cout << "   - INVALID CITY" << endl;
        }
        while (true) {
            cout << "ENTER DESTINATION AIRPORT: ";
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
        while (true) {
            cout << "PRESS 0 TO CONTINUE: "; cin >> command;
            if (command == "0") break;
        }
    }

    else if ( command == "2"){ // City->City
        string src, dest;
        list<string> srcAirports;
        list<string> destAirports;

        while (true) {
            cout << "ENTER SOURCE CITY: ";
            getline(cin >> ws, src);
            srcAirports = fm.getGraph().getAirportsInCity(src);
            if (!srcAirports.empty()) break;
            cout << "   - INVALID CITY" << endl;
        }
        while (true) {
            cout << "ENTER DESTINATION CITY: ";
            getline(cin >> ws, dest);
            destAirports = fm.getGraph().getAirportsInCity(dest);
            if (!destAirports.empty()) break;
            cout << "   - INVALID CITY" << endl;
        }

        set<pair<int, vector<string>>> bestPaths = {};

        for (auto& i : srcAirports) {
            for (auto& j : destAirports) {
                fm.getGraph().findBestPaths(i, j, bestPaths);
            }
        }
        int nFlights = bestPaths.begin()->second.size();

        cout << "BEST ROUTES FROM " << src << " TO " << dest << ":\n";

        for (auto &bestPath : bestPaths) {
            if (nFlights == bestPath.second.size()) {
                cout << "- ROUTE :\n";
                cout << "    ";
                for (auto &airport : bestPath.second) {
                    cout << airport << ' ' << fm.getGraph().getNodes().at(airport).airport->getName() << " --> ";
                }
                cout << "\b\b\b\b";
                cout << " DISTANCE: " << bestPath.first << " KM\n";
            }
        }


        while (true) {
            cout << "PRESS 0 TO CONTINUE: "; cin >> command;
            if (command == "0") break;
        }
    }
    else if ( command == "3"){ // Aiport->City
        string src, dest;
        list<string> destAirports;
        while (true) {
            cout << "ENTER SOURCE AIRPORT: ";
            cin >> src;
            if (fm.getGraph().getNodes().find(src) != fm.getGraph().getNodes().end()) break;
            cout << "   - INVALID CITY" << endl;
        }
        while (true) {
            cout << "ENTER DESTINATION CITY: ";
            getline(cin >> ws, dest);
            destAirports = fm.getGraph().getAirportsInCity(dest);
            if (!destAirports.empty()) break;
            cout << "   - INVALID CITY" << endl;
        }

        set<pair<int, vector<string>>> bestPaths = {};

        for (auto& i : destAirports) {
            fm.getGraph().findBestPaths(src, i, bestPaths);
        }

        int nFlights = bestPaths.begin()->second.size();

        cout << "BEST ROUTES FROM " << src << " TO " << dest << ":\n";

        for (auto &bestPath : bestPaths) {
            if (nFlights == bestPath.second.size()) {
                cout << "- ROUTE :\n";
                cout << "    ";
                for (auto &airport : bestPath.second) {
                    cout << airport << ' ' << fm.getGraph().getNodes().at(airport).airport->getName() << " --> ";
                }
                cout << "\b\b\b\b";
                cout << " DISTANCE: " << bestPath.first << " KM\n";
            }
        }

        while (true) {
            cout << "PRESS 0 TO CONTINUE: "; cin >> command;
            if (command == "0") break;
        }
    }
    else if ( command == "4"){ // City->Airport
        string src, dest;
        list<string> srcAirports;
        while (true) {
            cout << "ENTER SOURCE CITY: ";
            getline(cin >> ws, src);
            srcAirports = fm.getGraph().getAirportsInCity(src);
            if (!srcAirports.empty()) break;
            cout << "   - INVALID CITY" << endl;
        }
        while (true) {
            cout << "ENTER DESTINATION AIRPORT: ";
            cin >> dest;
            if (fm.getGraph().getNodes().find(dest) != fm.getGraph().getNodes().end()) break;
            cout << "   - INVALID CITY" << endl;
        }

        set<pair<int, vector<string>>> bestPaths = {};

        for (auto& i : srcAirports) {
            fm.getGraph().findBestPaths(i, dest, bestPaths);
        }

        int nFlights = bestPaths.begin()->second.size();

        cout << "BEST ROUTES FROM " << src << " TO " << dest << ":\n";

        for (auto &bestPath : bestPaths) {
            if (nFlights == bestPath.second.size()) {
                cout << "- ROUTE :\n";
                cout << "    ";
                for (auto &airport : bestPath.second) {
                    cout << airport << ' ' << fm.getGraph().getNodes().at(airport).airport->getName() << " --> ";
                }
                cout << "\b\b\b\b";
                cout << " DISTANCE: " << bestPath.first << " KM\n";
            }
        }

        while (true) {
            cout << "PRESS 0 TO CONTINUE: "; cin >> command;
            if (command == "0") break;
        }
    }
    else if ( command == "5"){ // Location->Location

        while (true) {
            cout << "   - ENTER SOURCE LATITUDE: "; cin >> command;

            if (isDouble(command) && stod(command) >= -90 && stod(command) <= 90) break;
            cout << "   - INVALID LATITUDE" << endl;
        }

        double lat1 = stod(command);

        while (true) {
            cout << "   - ENTER SOURCE LONGITUDE: "; cin >> command;
            if (isDouble(command) && stod(command) >= -180 && stod(command) <= 180) break;
            cout << "   - INVALID LONGITUDE" << endl;
        }

        double lon1 = stod(command);

        while (true) {
            cout << "   - ENTER SOURCE RADIUS: "; cin >> command;
            if (isDouble(command) && stod(command) >= 0) break;
            cout << "   - INVALID RADIUS" << endl;
        }

        double rad1 = stod(command);

        while (true) {
            cout << "   - ENTER DESTINATION LATITUDE: "; cin >> command;

            if (isDouble(command) && stod(command) >= -90 && stod(command) <= 90) break;
            cout << "   - INVALID LATITUDE" << endl;
        }

        double lat2 = stod(command);

        while (true) {
            cout << "   - ENTER DESTINATION LONGITUDE: "; cin >> command;
            if (isDouble(command) && stod(command) >= -180 && stod(command) <= 180) break;
            cout << "   - INVALID LONGITUDE" << endl;
        }

        double lon2 = stod(command);

        while (true) {
            cout << "   - ENTER DESTINATION RADIUS: "; cin >> command;
            if (isDouble(command) && stod(command) >= 0) break;
            cout << "   - INVALID RADIUS" << endl;
        }

        double rad2 = stod(command);


        set<pair<int, vector<string>>> bestPaths = {};
        auto srcAirports = fm.getGraph().getAirportsNearLocation(lat1, lon1, rad1);
        auto destAirports = fm.getGraph().getAirportsNearLocation(lat2, lon2, rad2);

        for (auto& i : srcAirports) {
            for (auto& j : destAirports) {
                fm.getGraph().findBestPaths(i.second, j.second, bestPaths);
            }
        }
        int nFlights = bestPaths.begin()->second.size();

        cout << "BEST ROUTES FROM (" << lat1 << ", " << lon1 <<  ") TO (" << lat2 << ", " << lon2 << "):\n";

        for (auto &bestPath : bestPaths) {
            if (nFlights == bestPath.second.size()) {
                cout << "- ROUTE :\n";
                cout << "    ";
                for (auto &airport : bestPath.second) {
                    cout << airport << ' ' << fm.getGraph().getNodes().at(airport).airport->getName() << " --> ";
                }
                cout << "\b\b\b\b";
                cout << " DISTANCE: " << bestPath.first << " KM\n";
            }
        }

        while (true) {
            cout << "PRESS 0 TO CONTINUE: "; cin >> command;
            if (command == "0") break;
        }

    } else if (command == "6") { // Search flight

        while (true) {
            cout << "ENTER SOURCE AIRPORT: "; cin >> command;
            if (fm.getGraph().getNodes().find(command) != fm.getGraph().getNodes().end()) break;
            cout << "INVALID AIRPORT!\n";
        }

        string src = command;

        while (true) {
            cout << "ENTER DESTINATION AIRPORT: "; cin >> command;
            if (fm.getGraph().getNodes().find(command) != fm.getGraph().getNodes().end()) break;
            cout << "INVALID AIRPORT!" << endl;
        }

        string dest = command;

        list<string> airlines = fm.getGraph().getAirlinesFromFlight(src, dest);
        int distance = fm.getGraph().flightDistance(src, dest);

        if (airlines.empty()) cout << "THERE ARE NO FLIGHTS BETWEEN THESE AIRPORTS!\n";

        else {
            cout << "FLIGHT DISTANCE FROM "  << src << ' ' << fm.getGraph().getNodes().at(src).airport->getName() << " --> "
                                             << dest<< ' ' << fm.getGraph().getNodes().at(dest).airport->getName() << " IS " << distance << " KMS" << endl;


            cout << "THE AVAILABLE AIRLINES ARE: ";

            for (auto &i: airlines) {
                cout << i << " ";
            }
            cout << endl;
        }

        while (true) {
            cout << "PRESS 0 TO CONTINUE: "; cin >> command;
            if (command == "0") break;
        }
    } else if (command == "7") {
        command = "0";
        return;

    }
    command = "1";
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
         << "| 5. AIRPORTS FROM COUNTRY                      |\n"
         << "| 6. AIRPORTS FROM COORDINATES                  |\n"
         << "| 7. GO BACK                                    |\n"
         << "-------------------------------------------------\n";
    while (true) {
        cout << "   - OPTION: "; cin >> command;
        if (isNumerical(command) && 1 <= stoi(command) && stoi(command) <= 7) break;
        else cout << "   - INVALID OPTION" << endl;
    }
    if (command == "1"){ // Search Airports
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
            cout << "PRESS 0 TO CONTINUE: "; cin >> command;
            if (command == "0") break;
        }
    }
    else if (command == "2") { // Number of Airports
        cout << "NUMBER OF AIRPORTS: " << fm.getGraph().getNodes().size() << endl;

        while (true) {
            cout << "PRESS 0 TO CONTINUE: "; cin >> command;
            if (command == "0") break;
        }

    }
    else if (command == "3") { // Top N Airports with most flights

        while (true) {
            cout << "ENTER N: "; cin >> command;
            if (isNumerical(command) && stoi(command) > 0) break;
            cout << "   - INVALID N" << endl;
        }
        int n = stoi(command);

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
            cout << "PRESS 0 TO CONTINUE: "; cin >> command;
            if (command == "0") break;
        }
    }
    else if (command == "4") { // Airports from City
        string city;
        while (true) {
            cout << "ENTER CITY: ";
            getline(cin >> ws, city);
            if (!fm.getGraph().getAirportsInCity(city).empty()) break;
            cout << "   - INVALID CITY" << endl;
        }
        list<string> airports_city = fm.getGraph().getAirportsInCity(city);

        cout << "AIRPORTS FROM CITY " << city << ":\n";
        for (auto &i : airports_city) {
            cout << "   - " << i << ' ' << fm.getGraph().getNodes().at(i).airport->getName() << endl;
        }

        while(true) {
            cout << "PRESS 0 TO CONTINUE: "; cin >> command;
            if (command == "0") break;
        }
    }
    else if (command == "5") { // Airports from Country
        string country;
        while (true) {
            cout << "ENTER COUNTRY: ";
            getline(cin >> ws, country);
            if (!fm.getGraph().getAirportsInCountry(country).empty()) break;
            cout << "   - INVALID COUNTRY" << endl;
        }
        list<string> airports_country = fm.getGraph().getAirportsInCountry(country);

        cout << "AIRPORTS FROM COUNTRY " << country << ":\n";
        for (auto &i : airports_country) {
            cout << "   - " << i << ' ' << fm.getGraph().getNodes().at(i).airport->getName() << endl;
        }

        while(true) {
            cout << "PRESS 0 TO CONTINUE: "; cin >> command;
            if (command == "0") break;
        }
    }
    else if (command == "6") { // Airports from Coordinates
        while (true) {
            cout << "   - ENTER LATITUDE: "; cin >> command;

            if (isDouble(command) && stod(command) >= -90 && stod(command) <= 90) break;
            else cout << "   - INVALID LATITUDE" << endl;
        }

        double lat = stod(command);

        while (true) {
            cout << "   - ENTER LONGITUDE: "; cin >> command;
            if ( isDouble(command) && stod(command) >= -180 && stod(command) <= 180) break;
            else cout << "   - INVALID LONGITUDE" << endl;
        }

        double lon = stod(command);

        while (true) {
            cout << "   - ENTER RADIUS: "; cin >> command;
            if ( isDouble(command) && stod(command) >= 0) break;
            else cout << "   - INVALID RADIUS" << endl;
        }

        double rad = stod(command);

        auto airports = fm.getGraph().getAirportsNearLocation(lat, lon, rad);
        cout << "AIRPORTS FROM COORDINATES (" << lat << ", " << lon << ") WITH RADIUS " << rad << "KM:" << endl;
        for (auto& airport : airports) {
            cout << "   - " << airport.second << " - " << airport.first << "KM" << endl;
        }

        while(true) {
            cout << "PRESS 0 TO CONTINUE: "; cin >> command;
            if (command == "0") break;
        }
    } else if (command == "7") {
        command = "0";
        return;
    }
    command = "2";
}

void Menu::airlineMenu() {
    cleanTerminal();
    cout << "-------------------------------------------------\n"
         << "|                 AIRLINES MENU                 |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. SEARCH AIRLINE                             |\n"
         << "| 2. NUMBER OF AIRLINES                         |\n"
         << "| 3. TOP N AIRLINES WITH MOST FLIGHTS           |\n"
         << "| 4. AIRLINES FROM COUNTRY                      |\n"
         << "| 5. GO BACK                                    |\n"
         << "-------------------------------------------------\n";

    while (true) {
        cout << "   - OPTION: ";
        cin >> command;
        if (1 <= stoi(command) && stoi(command) <= 5) break;
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
            cout << "PRESS 0 TO CONTINUE: "; cin >> command;
            if (command == "0") break;
        }

    } else if (command == "3") { // Top N Airlines with most flights
        while (true) {
            cout << "   - ENTER N: ";
            cin >> command;
            if (stoi(command) > 0) break;
            else cout << "   - INVALID NUMBER" << endl;
        }

        int n = stoi(command);
        auto airlines = fm.getAirlines();
        set<pair<int, string>> topAirlines = {};

        cout << "- TOP " << n << " AIRLINES WITH MOST FLIGHTS" << endl;
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
            cout << "PRESS 0 TO CONTINUE: ";
            cin >> command; if (command == "0") break;
        }

    } else if (command == "2") { // Number of Airlines
        cout << "   - NUMBER OF AIRLINES: " << fm.getAirlines().size() << endl;
        while (true) {
            cout << "PRESS 0 TO CONTINUE: "; cin >> command;
            if (command == "0") break;
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
            cout << "PRESS 0 TO CONTINUE: "; cin >> command;
            if (command == "0") break;
        }

    } else if (command == "5") {
        command = "0";
        return;
    }
    command = "3";
}

void Menu::networkMenu() {
    cleanTerminal();
    cout << "-------------------------------------------------\n"
         << "|                STATISTICS MENU                |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. NUMBER OF FLIGHTS                          |\n"
         << "| 2. STRONGLY CONNECTED COMPONENTS              |\n"
         << "| 3. ARTICULATION POINTS                        |\n"
         << "| 4. GRAPH DIAMETER                             |\n"
         << "| 5. GO BACK                                    |\n"
         << "-------------------------------------------------\n";

    while (true) {
        cout << "   - OPTION: ";
        cin >> command;
        if (isNumerical(command) && 1 <= stoi(command) && stoi(command) <= 5) break;
        else cout << "   - INVALID OPTION" << endl;
    }

    if (command == "1") { // Number of Flights
        int count = 0;
        for (auto& i: fm.getGraph().getNodes()){
            for(auto& j : i.second.adj) {
                count += j.airlines.size();
            }
        }
        cout << "   - NUMBER OF FLIGHTS: " << count << endl;
        while (true) {
            cout << "PRESS 0 TO CONTINUE: "; cin >> command;
            if (command == "0") break;
        }
    }
    else if (command == "2") { // Strongly Connected Components
        auto scc = fm.getGraph().stronglyConnectedComponents().size();
        cout << "   - NUMBER OF STRONGLY CONNECTED COMPONENTS - " << scc << endl;
        while (true) {
            cout << "PRESS 0 TO CONTINUE: "; cin >> command;
            if (command == "0") break;
        }
    }
    else if (command == "3") { // Articulation Points

        set<string> articulationPoints = fm.getGraph().articulationPoints();
        cout << "   - NUMBER OF ARTICULATION POINTS - " << articulationPoints.size() - 1 << endl;
        while (true) {
            cout << "PRESS 0 TO CONTINUE: "; cin >> command;
            if (command == "0") break;
        }
    }
    else if (command == "4") { // Graph Diameter
        cout << "   - GRAPH DIAMETER: " << fm.getGraph().diameter() << endl;
        while (true) {
            cout << "PRESS 0 TO CONTINUE: "; cin >> command;
            if (command == "0") break;
        }
    } else if (command == "5") {
        command = "0";
        return;
    }
    command = "4";
}
