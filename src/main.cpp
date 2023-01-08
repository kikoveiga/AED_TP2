#include <iostream>
#include "../headers/Menu.h"

using namespace std;

int main() {
    /*
    FlightManager fm;
    Graph grafo = fm.getGraph();
    auto nodes = grafo.getNodes();
    
    int resposta = 0;

    cout << fm.getAirlines().size() << " airlines" << endl;
    cout << grafo.getNodes().size() << " aeroportos" << endl;
    for (auto i : grafo.getNodes()) {
        for (auto j : i.second.adj) {
            resposta += j.airlines.size();
        }
    }
    cout << resposta << " voos" << endl << endl;

    list<list<string>> scc = grafo.stronglyConnectedComponents();

    cout << "Strongly Connected Components: " << scc.size() << endl;

    for (auto i : scc) {
        cout << i.size() << "Componente: ";
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }

    list<string> pontosArticulacao = grafo.articulationPoints();
    cout << pontosArticulacao.size();

    */

    Menu menu;
    menu.build();
    return 0;
}
