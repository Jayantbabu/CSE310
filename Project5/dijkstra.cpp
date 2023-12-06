#include "graph.h"
#include <vector>
#include <queue>
#include <limits>
#include <iostream>

const float INF = std::numeric_limits<float>::infinity();

std::vector<float> distances;
std::vector<int> predecessors; 

void dijkstra(const std::vector<std::vector<Edge>>& graph, int source) {

    std::fill(distances.begin(), distances.end(), INF);
    std::fill(predecessors.begin(), predecessors.end(), -1);
    int n = graph.size();
    std::vector<float> dist(n, INF);
    std::vector<int> prev(n, -1);
    auto comp = [&dist](const int lhs, const int rhs) { return dist[lhs] > dist[rhs]; };
    std::priority_queue<int, std::vector<int>, decltype(comp)> pq(comp);

    dist[source] = 0.0f;
    pq.push(source);

    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();

        for (const auto& edge : graph[u]) {
            int v = edge.v;
            float weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push(v);
            }
        }
    }

    // Print shortest distances
    for (int i = 0; i < n; ++i) {
        std::cout << "Shortest distance from vertex " << source << " to vertex " << i << " is " << dist[i] << std::endl;
    }
}
