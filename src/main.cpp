#include <iostream>
#include "../headers/Menu.h"

using namespace std;

int main() {
    /*
    FlightManager flightManager;


    Graph grafo = flightManager.getGraph();

    grafo.findBestPaths("OPO", "MIA");

    list<string> aeroportos = grafo.airportsInCity("Dubai");

    for (auto i : aeroportos) {
        cout << i << endl;
    }
    cout << endl;
    list<string> aeroportos2 = grafo.airportsNearLocation(41.0, -8.0, 300);

    for (auto i : aeroportos2) {
        cout << i << endl;
    }

    cout << grafo.connectedCompontents();
    */
    Menu menu;
    menu.build();
    return 0;
}
