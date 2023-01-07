//
// Created by belchior on 05-01-2023.
//

#include <cmath>
#include "../headers/Calc.h"
using namespace std;

double deg2rad(double deg) {
    return deg * (M_PI/180);
}


int Calc::haversine(double lat1, double lon1, double lat2, double lon2) {
    double R = 6371; // Radius of the earth in km
    double dLat = deg2rad(lat2-lat1);  // deg2rad below
    double dLon = deg2rad(lon2-lon1);
    double a =
            sin(dLat/2) * sin(dLat/2) +
            cos(deg2rad(lat1)) * cos(deg2rad(lat2)) *
            sin(dLon/2) * sin(dLon/2)
    ;
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = R * c; // Distance in km
    return round(d);
}