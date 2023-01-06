//
// Created by belchior on 29-12-2022.
//

#include "../headers/Graph.h"
#include "../headers/Calc.h"

//there still is segmentation fault, correct addNode
Graph::Graph(int n) {}

void Graph::addNode(Airport* airport) {
    nodes.insert({airport->getCode(), {airport, {}, false}});
}


void Graph::addEdge(const std::string &src, const std::string &dest, const std::string& airline) {
    auto src_node = nodes.find(src);
    auto dest_node = nodes.find(dest);

    if(src_node == nodes.end() || dest_node == nodes.end() || src_node == dest_node) {
        return;
    }

    src_node->second.adj.push_back({ dest, airline });
}

const std::unordered_map<std::string, Graph::Node> &Graph::getNodes() const {
    return nodes;
}







