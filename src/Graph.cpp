//
// Created by belchior on 29-12-2022.
//

#include "../headers/Graph.h"
#include "../headers/Calc.h"

using namespace std;

Graph::Graph(int n) {}

void Graph::addNode(Airport* airport) {
    nodes.insert({airport->getCode(), {airport, {}, false}});
}


void Graph::addEdge(const string& src, const string& dest, const string& airline) {
    auto src_node = nodes.find(src);
    auto dest_node = nodes.find(dest);

    if(src_node == nodes.end() || dest_node == nodes.end() || src_node == dest_node) {
        return;
    }

    src_node->second.adj.push_back({ dest, airline });
}

const unordered_map<string, Graph::Node>& Graph::getNodes() const {
    return nodes;
}







