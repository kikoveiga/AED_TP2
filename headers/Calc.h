//
// Created by belchior on 05-01-2023.
//

#ifndef AED_TP2_CALC_H
#define AED_TP2_CALC_H

class Calc {

public:

    /**
     * @brief Haversine function that returns a static int
     * @param lat1 double with the latitude of the first point
     * @param lon1 double with the longitude of the first point
     * @param lat2 double with the latitude of the second point
     * @param lon2 double with the longitude of the second point
     * @return static int with the distance between the two points
     */
    static int haversine(double lat1, double lon1, double lat2, double lon2);
};


#endif //AED_TP2_CALC_H
