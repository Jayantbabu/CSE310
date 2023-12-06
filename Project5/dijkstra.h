#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include "graph.h" // Include this if your Edge struct is defined in graph.h

// Declare the dijkstra function
void dijkstra(const std::vector<std::vector<Edge>>& graph, int source);

#endif // DIJKSTRA_H