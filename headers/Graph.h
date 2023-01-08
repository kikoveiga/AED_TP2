//
// Created by belchior on 29-12-2022.
//

#include <list>
#include <map>
#include <vector>
#include <unordered_map>
#include "Airport.h"
#include "Calc.h"
#ifndef AED_TP2_GRAPH_H
#define AED_TP2_GRAPH_H

//in this graph each airport will be a node and each flight will be an edge and the weight of them will be the distance

class Graph {

private:
    struct Edge {
        std::string destination;    //dest
        std::list<std::string> airlines;
        int distanceKms;                           //weight
    };
    struct Node{
        Airport* airport;         //src
        std::list<Edge> adj;
        bool visited;
        int distance;
    };

    std::unordered_map<std::string, Node> nodes;

public:

    explicit Graph();


    void addNode(Airport* airport);
    void addEdge(const std::string& src, const std::string& dest, const std::string& airline);

    void setAllNodesUnvisited();
    void setAllNodesDistance0();

    void dfs(const std::string& src);
    void bfs(const std::string& src);

    void findBestPaths(const std::string& src, const std::string& dest, std::map<int, std::vector<std::string>>& bestPaths);
    void dfsBestPaths(const std::string& src, const std::string& dest, std::map<int, std::vector<std::string>>& bestPaths, std::vector<std::string>& path, int distanceSum);

    int connectedComponents();
    int diameter();

    const std::unordered_map<std::string, Node>& getNodes() const;
    std::list<std::string> airportsInCity(const std::string& city) const;
    std::map<int, std::string> airportsNearLocation(const double latitude, const double longitude, const double radius) const;
    int getNumberFlightsFromAirport(const std::string &airportCode);


};




#endif //AED_TP2_GRAPH_H
