#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include "graph.h"
#include "dijkstra.h"
#include "cmd_command.h"

void readGraphFromFile(const std::string& filename, const std::string& direction, std::vector<std::vector<Edge>>& adjacencyLists) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filename << std::endl;
        return;
    }

    int n, m;
    file >> n >> m;
    adjacencyLists.resize(n);

    for (int i = 0; i < m; i++) {
        Edge edge;
        file >> edge.id >> edge.u >> edge.v >> edge.weight;

        if (direction == "directed") {
            adjacencyLists[edge.u].push_back(edge);
        } else if (direction == "undirected") {
            adjacencyLists[edge.u].push_back(edge);
            adjacencyLists[edge.v].push_back(edge);
        }
    }

    file.close();
}

float calculateDensity(const std::vector<std::vector<Edge>>& adjacencyLists, bool directed) {
    int V = adjacencyLists.size();
    int E = 0;
    for (const auto& edges : adjacencyLists) {
        E += edges.size();
    }
    if (!directed) {
        E /= 2;  // Because each edge is counted twice for undirected graphs
    }

    float density = directed ? static_cast<float>(E) / (V * (V - 1)) :
                               static_cast<float>(2 * E) / (V * (V - 1));
    return density;
}

void dfs(const std::vector<std::vector<Edge>>& graph, int vertex, std::vector<bool>& visited) {
    visited[vertex] = true;
    for (const auto& edge : graph[vertex]) {
        if (!visited[edge.v]) {
            dfs(graph, edge.v, visited);
        }
    }
}

int countTreesInForest(const std::vector<std::vector<Edge>>& graph) {
    int V = graph.size();
    std::vector<bool> visited(V, false);
    int treeCount = 0;

    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            dfs(graph, i, visited);
            ++treeCount;
        }
    }

    return treeCount;
}


void printGraph(std::vector<std::vector<Edge>>& adjList) {
        for (int i = 0; i < adjList.size(); ++i) {
            std::cout << "Vertex " << i << " has edges to: ";
            for (const auto& edge : adjList[i]) {
                std::cout << "(" << edge.v << ", weight: " << edge.weight << "), ";
            }
            std::cout << std::endl;
        }
    }

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <graph> <direction>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string direction = argv[2];

    std::vector<std::vector<Edge>> adjacencyLists;

    readGraphFromFile(filename, direction, adjacencyLists);
    
    // int sourceVertex = 0;
    // dijkstra(adjacencyLists, sourceVertex);

    
    

    float density = calculateDensity(adjacencyLists,true);
    int trees = countTreesInForest(adjacencyLists);

    std::cout << "Graph Density: " << density << std::endl;
    std::cout << "Number of Trees (Connected Components) from DFS: " << trees << std::endl;

    //processCommands(adjacencyLists);


    return 0;
}
