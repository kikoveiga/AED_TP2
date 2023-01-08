//
// Created by belchior on 29-12-2022.
//

#include "../headers/Graph.h"
#include <queue>
#include <iostream>
#include <algorithm>
#include <list>
#include <string>

using namespace std;

Graph::Graph() {}

void Graph::addNode(Airport* airport) {
    nodes.insert({airport->getCode(), {airport, {}, false}});
}


void Graph::addEdge(const string& src, const string& dest, const string& airline) {

    auto &srcNode = nodes[src];

    for (auto &i: srcNode.adj) {
        if (i.destination == dest) {
            i.airlines.push_back(airline);
            return;
        }
    }

    int distance = Calc::haversine(srcNode.airport->getLatitude(), srcNode.airport->getLongitude(),
                                   nodes[dest].airport->getLatitude(), nodes[dest].airport->getLongitude());

    srcNode.adj.push_back({dest, {airline}, distance});
}

void Graph::setAllNodesUnvisited() {
    for (auto& i : nodes) {
        i.second.visited = false;
    }
}

void Graph::setAllNodesDistance0() {
    for (auto& i : nodes) {
        i.second.distance = 0;
    }
}

void Graph::dfs(const string& src) {

    auto& srcNode = nodes[src];

    srcNode.visited = true;

    for (auto& i : srcNode.adj) {
        if (!(nodes[i.destination].visited)) {
            dfs(i.destination);
        }
    }

}

void Graph::bfs(const string& src) {

    setAllNodesDistance0();
    setAllNodesUnvisited();

    queue<string> q; // queue of unvisited nodes
    q.push(src);
    nodes[src].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        string u = q.front(); q.pop();
        // show node order
        //cout << u << " ";
        for (auto& e : nodes[u].adj) {
            string w = e.destination;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
            }
        }
    }
}

void dfsArticulationPoints (int v) {

}

void Graph::dfsBestPaths(const string& src, const string& dest, map<int, vector<string>>& bestPaths, vector<string>& path, int distanceSum) {

    path[nodes[src].distance] = src;
    distanceSum += Calc::haversine(nodes[src].airport->getLatitude(), nodes[src].airport->getLongitude(),
                                   nodes[dest].airport->getLatitude(), nodes[dest].airport->getLongitude());

    if (src == dest) bestPaths.insert({distanceSum, path});

    nodes[src].visited = true;

    for (auto& e : nodes[src].adj) {
        string next = e.destination;
        if (!nodes[next].visited && nodes[next].distance == nodes[src].distance + 1 && nodes[next].distance < path.size()) {

            dfsBestPaths(next, dest, bestPaths, path, distanceSum);
        }
    }
    nodes[src].visited = false;
}

void Graph::findBestPaths(const std::string& src, const std::string& dest, map<int, vector<string>>& bestPaths) {

    bfs(src);

    if(nodes[dest].distance == 0) {
        return;
    }

    setAllNodesUnvisited();

    vector<string> path(nodes[dest].distance + 1);
    dfsBestPaths(src, dest, bestPaths, path, 0);
}

const unordered_map<string, Graph::Node>& Graph::getNodes() const {
    return nodes;
}

list<string> Graph::airportsInCity(const string& city) const {

    list<string> aeroportos;

    for (auto& i : nodes) {
        if (i.second.airport->getCity() == city) {
            aeroportos.push_back(i.first);
        }
    }
    return aeroportos;
}

map<int, string>Graph::airportsNearLocation(const double latitude, const double longitude, const double radius) const {

    map<int, string> aeroportos;

    for (auto& i : nodes) {

        int distance = Calc::haversine(latitude, longitude, i.second.airport->getLatitude(), i.second.airport->getLongitude());
        if (distance <= radius) {
            aeroportos.insert({distance, i.first});
        }
    }
    return aeroportos;
}

int Graph::getNumberFlightsFromAirport(const string &airportCode) {
    return nodes.at(airportCode).adj.size();;
}

int Graph::connectedComponents() {
    int counter = 0;
    setAllNodesUnvisited();

    for (auto& i : nodes) {
        if (!nodes[i.first].visited) {
            cout << i.first << endl;
            counter++;
            dfs(i.first);
        }
    }
    return counter;
}

int Graph::diameter() {

    int diameter = 0;

    nodes["OPO"].visited = true;

}












