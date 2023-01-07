//
// Created by belchior on 29-12-2022.
//

#include "../headers/Graph.h"
#include "../headers/Calc.h"
#include <queue>
#include <iostream>

using namespace std;

Graph::Graph(int n) {}

void Graph::addNode(Airport* airport) {
    nodes.insert({airport->getCode(), new Node {airport, {}, false}});
}


void Graph::addEdge(const string& src, const string& dest, const string& airline, double distance) {

    //Why is the vector of airlines not working, in the end every node only has one airline to a different destination
    //nodes[src].adj.push_back({dest, airline, distance});
    auto srcNode = nodes[src];

    for (auto i : srcNode->adj) {
        if (i->destination == dest) {
            i->airlines.push_back(airline);
            return;
        }
    }

    srcNode->adj.push_back(new Edge {dest, {airline}, distance});


}

void Graph::setAllNodesUnvisited() {
    for (auto i : nodes) {
        i.second->visited = false;
    }
}

void Graph::setAllNodesDist0() {
    for (auto i : nodes) {
        i.second->dist = 0;
    }
}

void Graph::dfsBestPaths(const string& src, const string& dest, vector<string>& path) {

    path[nodes[src]->dist] = src;

    if (src == dest) {

        cout << "Best path: ";
        for (auto i : path) {
            cout << i << " ";
        }
        cout << endl;
        return;
    }
    nodes[src]->visited = true;

    for (auto e : nodes[src]->adj) {
        string next = e->destination;
        if (!nodes[next]->visited && nodes[next]->dist == nodes[src]->dist + 1 && nodes[next]->dist < path.size()) {

            dfsBestPaths(next, dest, path);
        }
    }
    nodes[src]->visited = false;
    return;
}

void Graph::bfs(const string& src) {

    setAllNodesDist0();
    setAllNodesUnvisited();

    queue<string> q; // queue of unvisited nodes
    q.push(src);
    nodes[src]->visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        string u = q.front(); q.pop();
        // show node order
        //cout << u << " ";
        for (auto e : nodes[u]->adj) {
            string w = e->destination;
            if (!nodes[w]->visited) {
                q.push(w);
                nodes[w]->visited = true;
                nodes[w]->dist = nodes[u]->dist + 1;
            }
        }
    }
}

void Graph::findBestPaths(const std::string &src, const std::string &dest) {

    bfs(src);
    if(nodes[dest]->dist == 0) {
        cout << "No path found" << endl;
        return;
    }

    setAllNodesUnvisited();

    if(nodes[dest]->dist == 0) {
        cout << "No path found" << endl;
        return;
    }

    vector<string> path(nodes[dest]->dist + 1);
    dfsBestPaths(src, dest, path);

    cout << "Best path found: " << nodes[dest]->dist << " flight(s)" << endl;
}

const unordered_map<string, Graph::Node*>& Graph::getNodes() const {
    return nodes;
}







