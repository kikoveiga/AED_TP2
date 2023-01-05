#include <iostream>
#include "../headers/FlightManager.h"
#include "../headers/Airport.h"
int main() {
    auto fm = new FlightManager();
    auto a = fm->getAirports();
    auto m = fm->getAirlines();
    for (auto i = m.begin(); i!= m.end() ; i++)
        std::cout << i->first << i->second.getName();
    return 0;
}
