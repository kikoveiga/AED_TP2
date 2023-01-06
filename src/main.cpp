#include <iostream>
#include "../headers/FlightManager.h"
#include "../headers/Airport.h"
int main() {
    auto fm = new FlightManager();
    auto a = fm->getAirports();
    auto m = fm->getAirlines();
    for (auto & i : m) std::cout << i.first << " ----- " << i.second.getName() << '\n';
    std::cout << m.size();
    for (auto & j: a.getNodes()) std::cout << j.first << " ----- " << j.second.airport->getName() << " ------ " << j.second.airport->getCity() << '\n';
    std::cout << a.getNodes().size();

    for (auto & k: a.getNodes()) {
        for (auto & l: k.second.adj) {
            std::cout << l.destination<< " ------ " << l.airline << '\n';
        }
    }
    return 0;

}
