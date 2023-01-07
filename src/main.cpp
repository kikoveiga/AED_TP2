#include <iostream>
#include "../headers/Menu.h"

using namespace std;

int main() {

    FlightManager flightManager;


    Graph grafo = flightManager.getGraph();

    list<string> a1 = grafo.airportsInCity("Dubai");
    for (auto i : a1) {
        cout << i << endl;
    }
    cout << endl;

    map<int, vector<string>> bestPaths;
    grafo.findBestPaths("OPO", "DXB", bestPaths);
    for (auto i : bestPaths) {
        cout << i.first << ' ';
        for (auto j : i.second) {
            cout << j << " ";
        }
        cout << endl;
    }

    map<int, string> aeroportos2 = grafo.airportsNearLocation(41.0, -8.0, 300);

    for (auto i : aeroportos2) {
        cout << i.first << " " << i.second << endl;
    }

    //cout << grafo.connectedComponents();

    //Menu menu;
    //menu.build();
    return 0;
}
