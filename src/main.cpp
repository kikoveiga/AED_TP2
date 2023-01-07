#include <iostream>
#include "../headers/FlightManager.h"
#include "../headers/Airport.h"

using namespace std;

int main() {
    auto fm = new FlightManager();
    auto a = fm->getGraph();
    auto m = fm->getAirlines();

    /*for (auto i : a.getNodes()) {

        for (auto j : i.second->adj) {
            cout << i.second->airport->getCode() << " " << j->destination << " " << j->airlines.size() << endl;
        }
    }*/

    a.findBestPaths("OPO", "MIA");



    return 0;

}
