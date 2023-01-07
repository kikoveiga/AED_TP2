#include <iostream>
#include "../headers/Menu.h"

using namespace std;

int main() {

    FlightManager flightManager;

    Graph grafo = flightManager.getGraph();


    /*for (auto i : a.getNodes()) {

        for (auto j : i.second->adj) {
            cout << i.second->airport->getCode() << " " << j->destination << " " << j->airlines.size() << endl;
        }
    }*/

    grafo.findBestPaths("OPO", "MIA");

    list<string> aeroportos = grafo.airportsInCity("Dubai");

    for (auto i : aeroportos) {
        cout << i << endl;
    }
    cout << endl;
    list<string> aeroportos2 = grafo.airportsNearLocation(41.0, -8.0, 400);

    for (auto i : aeroportos2) {
        cout << i << endl;
    }

    return 0;
}
