#include <iostream>
#include "../headers/Menu.h"

using namespace std;

int main() {

    FlightManager fm;
    Graph grafo = fm.getGraph();
    
    int resposta = 0;

    cout << fm.getAirlines().size() << " airlines" << endl;
    cout << grafo.getNodes().size() << " aeroportos" << endl;
    for (auto i : grafo.getNodes()) {
        for (auto j : i.second.adj) {
            resposta += j.airlines.size();
        }
    }
    cout << resposta << " voos" << endl;

    set<pair<int, string>> aeroportos = grafo.airportsNearLocation(38.7742, -9.1342, 300);

    for (auto i : aeroportos) {
        cout << i.second << " " << i.first << endl;
    }
    cout << endl;

    set<pair<int, vector<string>>> caminhos;

    grafo.findBestPaths("OPO", "MIA", caminhos);

    for (auto i : caminhos) {
        cout << i.first << " ";
        for (auto j : i.second) {
            cout << j << " ";
        }
        cout << endl;
    }

    //Menu menu;
    //menu.build();
    return 0;
}
