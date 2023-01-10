//
// Created by belchior on 29-12-2022.
//

#include <set>
#include <stack>
#include <list>
#include <map>
#include <vector>
#include <unordered_map>
#include "Airport.h"
#include "Calc.h"
#ifndef AED_TP2_GRAPH_H
#define AED_TP2_GRAPH_H

//in this graph each airport will be a node and each flight will be an edge and the weight of them will be the distanceKms

class Graph {

private:
    struct Edge {
        std::string destination;  //dest
        std::list<std::string> airlines;
        int distanceKms;          //weight
    };
    struct Node{
        Airport* airport;         //src
        std::list<Edge> adj;
        bool visited;
        int distance;
        int indexTarjan;
        int lowTarjan;
    };

    std::unordered_map<std::string, Node> nodes;

public:

    /**
     * @brief Graph constructor
     */
    explicit Graph();

    /**
     * @brief Function to add a node to the graph
     * @param airport airport to add to the node
     */
    void addNode(Airport* airport);

    /**
     * @brief Function to add an edge to the graph
     * @param src source airport
     * @param dest destination airport
     * @param airline airline that flies between the airports
     */
    void addEdge(const std::string& src, const std::string& dest, const std::string& airline);

    /**
     * @brief Function to get the nodes of the graph
     * @return nodes
     */
    const std::unordered_map<std::string, Node>& getNodes() const;

    /**
     * @brief Function to set all nodes unvisited
     */
    void setAllNodesUnvisited();

    /**
     * @brief Function to set all nodes' distance to 0
     */
    void setAllNodesDistance0();

    /**
     * @brief Function to set all nodes' indexTarjan to -1
     */
    void setAllNodesIndexTarjan();

    /**
     * @brief Function to set all nodes' lowTarjan to -1
     */
    void setAllNodesLowTarjan();


    /**
     * @brief Function that implements the DFS algorithm to find the articulation points of the graph and stores them in a set
     * @brief Time complexity of O(V*(V + E))
     * @param src source airport
     * @param counter to keep track of the indexes of the nodes to visit
     * @param stack to keep track of the nodes visited
     * @param articulationPoints set to store the articulation points
     */
    void dfsArticulationPoints(const std::string& src, int& counter, std::stack<std::string>& stack, std::set<std::string>& articulationPoints);

    /**
     * @brief Function that calls the DFS algorithm to every node that hasn't been visited yet with the purpose of finding the articulation points
     * @return list of articulation points
     */
    std::set<std::string> articulationPoints();

    /**
     * @brief Function that implements the DFS algorithm to find the strongly connected components of the graph and stores them in a list
     * @brief Time complexity of O(V + E)
     * @param src source airport
     * @param counter to keep track of the indexes of the nodes to visit
     * @param stack to keep track of the nodes visited
     * @param scc list to store the strongly connected components
     */
    void dfsTarjan(const std::string& src, int& counter, std::stack<std::string>& stack, std::list<std::list<std::string>>& scc);

    /**
     * @brief Function based on the Tarjan algorithm to find the strongly connected components of the graph
     * @return list of strongly connected components
     */
    std::list<std::list<std::string>> stronglyConnectedComponents();

    /**
     * @brief Function that implements a standard BFS algorithm and marks all nodes with a distance relative to the source node
     * @brief Time complexity of O(V + E)
     * @param src
     */
    void bfs(const std::string& src);

    /**
     * @brief Function that implements a DFS algorithm and finds all possible best paths between two airports
     * @brief Time complexity of O(V + E)
     * @param src string with the source airport
     * @param dest string with the destination airport
     * @param bestPaths list to store the best paths
     * @param path list to store the current path
     * @param distanceSum int to keep track of total the distance of the current path
     */
    void dfsBestPaths(const std::string& src, const std::string& dest, std::set<std::pair<int, std::vector<std::string>>>& bestPaths, std::vector<std::string>& path, int distanceSum);

    /**
     * @brief Function that calls a standard BFS algorithm and a DFS algorithm to find the shortest path between two airports
     * @brief Time complexity of BFS + DFS
     * @param src source airport
     * @param dest destination airport
     * @param bestPaths list to store the best paths in terms of number of flights and distance
     */
    void findBestPaths(const std::string& src, const std::string& dest, std::set<std::pair<int, std::vector<std::string>>>& bestPaths);

    /**
     * @brief Function that calls a standard BFS algorithm to all nodes to find the diameter of the graph
     * @brief Time complexity of O(V*(2V + E))
     * @return int with the diameter of the graph
     */
    int diameter();

    /**
     * @brief Function to get all the airports from a given city
     * @brief Time complexity of O(V)
     * @param city string with the city
     * @return list of airports
     */
    std::list<std::string> getAirportsInCity(const std::string& city) const;

    /**
     * @brief Function to get all the airports from a given country
     * @brief Time complexity of O(V)
     * @param country string with the country
     * @return list of airports
     */
    std::list<std::string> getAirportsInCountry(const std::string& country) const;

    /**
     * @brief Function to get all the airports within a radius from a given location
     * @brief Time complexity of O(V)
     * @param latitude double with the latitude of the location
     * @param longitude double with the longitude of the location
     * @return list of airports
     */
    std::set<std::pair<int, std::string>> getAirportsNearLocation(double latitude, double longitude, double radius) const;

    /**
     * @brief Function that returns the number of destinations from a given airport
     * @param airportCode string with the airport code
     * @return unsigned with the number of destinations
     */
    unsigned getNumberDestinationsFromAirport(const std::string &airportCode);

    /**
     * @brief Function that returns the list of airlines in a given edge
     * @param src string with the source airport code
     * @param dest string with the destination airport code
     * @return list of strings containing the airlines' codes
     */
    std::list<std::string> getAirlinesFromFlight(const std::string& src, const std::string& dest) const;

    /**
     * @brief return the distance from src to dest
     * @param src string with the source airport code
     * @param dest string with the destination airport code
     * @return int with the distance of the flight
     */
    int flightDistance(const std::string& src, const std::string& dest) const;
};

#endif //AED_TP2_GRAPH_H
