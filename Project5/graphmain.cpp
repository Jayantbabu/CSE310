#include <iostream>
#include <fstream>
#include <vector>

struct Edge {
    int id;
    int u;
    int v;
    float weight;
};

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
    printGraph(adjacencyLists);


    return 0;
}
