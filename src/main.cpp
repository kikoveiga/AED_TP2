#include <iostream>
#include "../headers/FlightManager.h"
#include "../headers/Airport.h"
int main() {
    auto *fm = new FlightManager();
    for (auto const &pair: fm->getAirports()) {
        std::cout << "{" << pair.first << ": " << pair.second.getName() << "}\n";
    }   //testar aeroportos


    return 0;
}
