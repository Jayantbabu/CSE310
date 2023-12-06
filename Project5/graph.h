// graph.h

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

// Structure to represent an edge
struct Edge {
    int id;
    int u;
    int v;
    float weight;
};

// Function to read graph from file
void readGraphFromFile(const std::string& filename, const std::string& direction, std::vector<std::vector<Edge>>& adjacencyLists);

// Function to print the graph
void printGraph(std::vector<std::vector<Edge>>& adjList);

#endif // GRAPH_H
