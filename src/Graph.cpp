//
// Created by belchior on 29-12-2022.
//

#include "../headers/Graph.h"
#include <queue>
#include <algorithm>
#include <list>
#include <string>

using namespace std;

Graph::Graph() = default;

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

void Graph::setAllNodesIndexTarjan() {
    for (auto& i : nodes) {
        i.second.indexTarjan = -1;
    }
}

void Graph::setAllNodesLowTarjan() {
    for (auto& i : nodes) {
        i.second.lowTarjan = -1;
    }
}

void Graph::dfsArticulationPoints(const string& src, int& counter, stack<string>& stack, set<string>& articulationPoints) {
    auto &srcNode = nodes[src];
    srcNode.visited = true;
    srcNode.lowTarjan = srcNode.indexTarjan = counter++;
    stack.push(src);

    for (auto &i : srcNode.adj) {
        auto &destNode = nodes[i.destination];

        if (destNode.indexTarjan == -1) {
            dfsArticulationPoints(i.destination, counter, stack, articulationPoints);

            srcNode.lowTarjan = min(srcNode.lowTarjan, destNode.lowTarjan);

            if (srcNode.indexTarjan != 0 && destNode.lowTarjan >= srcNode.indexTarjan) {
                articulationPoints.insert(src);
            }
        }
        else if (destNode.visited){
            srcNode.lowTarjan = min(srcNode.lowTarjan, destNode.indexTarjan);
        }
    }
    stack.pop();
}

set<string> Graph::articulationPoints() {
    set<string> articulationPoints;
    setAllNodesUnvisited();
    setAllNodesIndexTarjan();
    setAllNodesLowTarjan();

    int counter = 0;
    stack<string> stack;

    for (auto &i : nodes) {
        if (i.second.indexTarjan == -1) {
            dfsArticulationPoints(i.first, counter, stack, articulationPoints);
        }
    }
    return articulationPoints;
}

void Graph::dfsTarjan(const string& src, int& counter, stack<string>& stack, list<list<string>>& scc) {
    auto& srcNode = nodes[src];
    srcNode.indexTarjan = srcNode.lowTarjan = counter++;
    stack.push(src);
    srcNode.visited = true;
    for (auto& i : srcNode.adj) {
        if (nodes[i.destination].indexTarjan == -1) { // Not yet visited
            dfsTarjan(i.destination, ++counter, stack, scc);
            srcNode.lowTarjan = min(srcNode.lowTarjan, nodes[i.destination].lowTarjan);
        }
        else if (nodes[i.destination].visited) { // It is in stack and in current scc
            srcNode.lowTarjan = min(srcNode.lowTarjan, nodes[i.destination].indexTarjan);
        }
        // It was not in stack, so it is from a different scc, ignore
    }
    if (srcNode.lowTarjan == srcNode.indexTarjan) { // Root node, pop the stack and generate the scc
        list<string> component;
        string w;
        do {
            w = stack.top();
            stack.pop();
            nodes[w].visited = false;
            component.push_back(w);
        } while (w != src);
        scc.push_back(component);
    }

}
list<list<string>> Graph::stronglyConnectedComponents() {

    setAllNodesUnvisited();
    setAllNodesIndexTarjan();
    setAllNodesLowTarjan();

    int index = 0;
    stack<string> stack;
    list<list<string>> scc;

    for (auto& i : nodes) {
        if (i.second.indexTarjan == -1) { // If has undefined index
            dfsTarjan(i.first, index, stack, scc);
        }
    }
    return scc;
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

void Graph::dfsBestPaths(const string& src, const string& dest, set<pair<int, vector<string>>>& bestPaths, vector<string>& path, int distanceSum) {

    path[nodes[src].distance] = src;

    if (src == dest) bestPaths.insert({distanceSum, path});

    nodes[src].visited = true;

    for (auto& e : nodes[src].adj) {
        string next = e.destination;

        if (!nodes[next].visited && nodes[next].distance == nodes[src].distance + 1 && nodes[next].distance < path.size()) {

            dfsBestPaths(next, dest, bestPaths, path, distanceSum + e.distanceKms);
        }
    }
    nodes[src].visited = false;
}

void Graph::findBestPaths(const std::string& src, const std::string& dest, set<pair<int, vector<string>>>& bestPaths) {

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

list<string> Graph::getAirportsInCity(const string& city) const {

    list<string> aeroportos;

    for (auto& i : nodes) {
        if (i.second.airport->getCity() == city) {
            aeroportos.push_back(i.first);
        }
    }
    return aeroportos;
}

list<string> Graph::getAirportsInCountry(const string& country) const {

    list<string> aeroportos;

    for (auto& i : nodes) {
        if (i.second.airport->getCountry() == country) {
            aeroportos.push_back(i.first);
        }
    }
    return aeroportos;
}

set<pair<int, string>>Graph::getAirportsNearLocation(const double latitude, const double longitude, const double radius) const {

    set<pair<int, string>> airports;

    for (auto& i : nodes) {

        int distance = Calc::haversine(latitude, longitude, i.second.airport->getLatitude(), i.second.airport->getLongitude());
        if (distance <= radius) {
            airports.insert({distance, i.first});
        }
    }
    return airports;
}

unsigned Graph::getNumberFlightsFromAirport(const string &airportCode) {
    return nodes.at(airportCode).adj.size();
}


int Graph::diameter() {

    int diameter = 0;
    for (auto& i : nodes) {
        bfs(i.first);
        for (auto& j : nodes) {
            if (j.second.distance > diameter) {
                diameter = j.second.distance;
            }
        }
    }
    return diameter;
}

list<string> Graph::getAirlinesFromFlight(const string& src, const string& dest) const{

    list<string> airlines;
    auto& srcNode = nodes.at(src);

    for (auto& i : srcNode.adj) {
        if (i.destination == dest) {
            for (auto& j : i.airlines) {
                airlines.push_back(j);
            }
            return airlines;
        }
    }
    return airlines;
}

int Graph::flightDistance(const string& src, const string& dest) const {
    int distance = 0;
    auto& srcNode = nodes.at(src);

    for (auto&i :srcNode.adj) {
        if (i.destination == dest) {
            distance = i.distanceKms;
            return distance;
        }
    }
    return distance;
}
