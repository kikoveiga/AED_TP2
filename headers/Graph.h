//
// Created by belchior on 29-12-2022.
//

#include <list>
#include <vector>
#include <unordered_map>
#include "Airport.h"
#ifndef AED_TP2_GRAPH_H
#define AED_TP2_GRAPH_H

//in this graph each airport will be a node and each flight will be an edge and the weight of them will be the distance

class Graph {

private:
    struct Edge {
        std::string destination;    //dest
        std::list<std::string> airlines;
        double distance;                           //weight
    };
    struct Node{
        Airport* airport;         //src
        std::list<Edge*> adj;
        bool visited;
        int dist;
    };

    std::unordered_map<std::string, Node*> nodes;

public:

    explicit Graph(int n = 1);


    void addNode(Airport* airport);
    void addEdge(const std::string& src, const std::string& dest, const std::string& airline, double distance);
    void setAllNodesUnvisited();
    void setAllNodesDist0();
    void dfsBestPaths(const std::string& src, const std::string& dest, std::vector<std::string>& path);
    void bfs(const std::string& src);
    void findBestPaths(const std::string& src, const std::string& dest);

    const std::unordered_map<std::string, Node*>& getNodes() const;


};




#endif //AED_TP2_GRAPH_H
