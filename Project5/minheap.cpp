#include "graph.h"
#include "minheap.h"
#include <vector>
#include <queue>
#include <limits>
#include <iostream>
#include <iomanip>

const float INF = std::numeric_limits<float>::infinity();

// Assuming the graph is represented as an adjacency list of edges
struct Vertex {
    int id;
    float distance;
    Vertex(int id, float distance) : id(id), distance(distance) {}
};

struct CompareVertex {
    bool operator()(const Vertex& lhs, const Vertex& rhs) {
        return lhs.distance > rhs.distance;
    }
};

void dijkstra(const std::vector<std::vector<Edge>>& graph, int source, std::vector<float>& distances, std::vector<int>& predecessors, int flag) {
    int n = graph.size();
    std::vector<bool> visited(n, false);
    std::priority_queue<Vertex, std::vector<Vertex>, CompareVertex> pq;

    std::fill(distances.begin(), distances.end(), std::numeric_limits<float>::infinity());
    std::fill(predecessors.begin(), predecessors.end(), -1);

    distances[source] = 0.0f;
    pq.push(Vertex(source, 0.0f));

    if (flag == 1) {
        std::cout << "Insert vertex " << source << ", key=" << std::setw(12) << std::setprecision(4) << std::fixed << 0.0000 << "\n";
    }

    while (!pq.empty()) {
        int u = pq.top().id;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        if (flag == 1) {
            std::cout << "Delete vertex " << u << ", key=" << std::setw(12) << std::setprecision(4) << std::fixed << distances[u] << "\n";
        }

        for (const auto& edge : graph[u]) {
            int v = edge.v;
            float weight = edge.weight;

            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                predecessors[v] = u;
                pq.push(Vertex(v, distances[v]));

                if (flag == 1) {
                    std::cout << "Insert vertex " << v << ", key=" << std::setw(12) << std::setprecision(4) << std::fixed << distances[v] << "\n";
                }
            }
        }
    }
}