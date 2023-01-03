//
// Created by belchior on 29-12-2022.
//

#include "../headers/Graph.h"

void Graph::addNode(const std::string& airport_code, const Airport& airport) {
    nodes.insert({airport_code, { airport}});
}

void Graph::addEdge(const std::string &src, const std::string &dest, const std::string& airline) {
    auto src_node = nodes.find(src);
    auto dest_node = nodes.find(dest);

    if(src_node == nodes.end() || dest_node == nodes.end() || src_node == dest_node) {
        return;
    }

    src_node->second.adj.push_back({ dest, airline });
}







