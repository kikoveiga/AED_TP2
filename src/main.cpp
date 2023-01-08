#include <iostream>
#include "../headers/Menu.h"

using namespace std;

int main() {

    FlightManager flightManager;
    Graph grafo = flightManager.getGraph();
    
    int resposta = 0;

    cout << grafo.getNodes().size() << endl;
    for (auto i : grafo.getNodes()) {
        for (auto j : i.second.adj) {
            resposta += j.airlines.size();
        }
    }
    cout << resposta;


    //Menu menu;
    //menu.build();
    return 0;
}
