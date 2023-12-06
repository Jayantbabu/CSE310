// graph.h

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>

struct Node {
    int dest;
    double weight;
};

class Graph {
public:
    std::vector<std::list<Node>> adjList;
    
    Graph(int vertices);
    void addEdge(int src, int dest, double weight);
    void printGraph();
};

#endif
