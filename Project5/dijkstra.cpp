#include <set>
#include <vector>
#include <limits>
#include <iostream>

const double INF = std::numeric_limits<double>::infinity();


void dijkstra(const Graph& graph, int source) {
    std::vector<double> distances(graph.adjList.size(), INF);
    std::vector<int> previous(graph.adjList.size(), -1);
    std::set<std::pair<double, int>> heap;

    distances[source] = 0;
    heap.insert({0, source});

    while (!heap.empty()) {
        int u = heap.begin()->second;
        heap.erase(heap.begin());

        for (const Node& node : graph.adjList[u]) {
            int v = node.dest;
            double weight = node.weight;

            // Check if there is a shorter path to v through u
            if (distances[v] > distances[u] + weight) {
                // Removing the old distance if it's in the set
                if (distances[v] != INF) {
                    heap.erase(heap.find({distances[v], v}));
                }
                distances[v] = distances[u] + weight;
                previous[v] = u;
                heap.insert({distances[v], v});
            }
        }
    }

    // Output distances and paths
    for (int i = 0; i < distances.size(); ++i) {
        std::cout << "Distance from " << source << " to " << i << " is " << distances[i] << std::endl;
    }
}
