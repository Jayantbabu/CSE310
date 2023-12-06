#include <iostream>
#include <vector>
#include <list>
#include <utility> 
#include "graph.h"
#include <fstream>
#include <string>
#include <sstream>

struct Edge {
    int src, dest;
    double weight;
};


struct Node {
    int dest;
    double weight;
};

class Graph {
public:
    std::vector<std::list<Node>> adjList;


    Graph(int vertices) {
        adjList.resize(vertices);
    }


    void addEdge(int src, int dest, double weight) {
        adjList[src].push_back({dest, weight});
        // If the graph is undirected, add an edge from dest to src as well
        // adjList[dest].push_back({src, weight});
    }

    // Function to print the adjacency list representation of the graph
    void printGraph() {
        for (int i = 0; i < adjList.size(); i++) {
            std::cout << "Adjacency list of vertex " << i << std::endl;
            for (Node node : adjList[i]) {
                std::cout << "(" << i << ", " << node.dest << ", " << node.weight << ") ";
            }
            std::cout << std::endl;
        }
    }
};


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <graph_filename> <directed/undirected>" << std::endl;
        return 1;
    }

    std::string graphFilename = argv[1];
    std::string graphType = argv[2];

    // Check if the graph should be directed or undirected
    bool isDirected = (graphType == "directed");

    // Open the file
    std::ifstream file(graphFilename);
    if (!file) {
        std::cerr << "Error: Unable to open file " << graphFilename << std::endl;
        return 1;
    }

    int numVertices, numEdges;
    file >> numVertices >> numEdges;
    Graph myGraph(numVertices);

    // Read edges from the file
    int edgeID, u, v;
    double weight;
    while (file >> edgeID >> u >> v >> weight) {
        // Note: Subtract 1 if the file uses 1-based indexing
        myGraph.addEdge(u - 1, v - 1, weight);
        if (!isDirected) {
            // Add the reverse edge for undirected graphs
            myGraph.addEdge(v - 1, u - 1, weight);
        }
    }

    // Close the file
    file.close();

    // Now you can perform operations on the graph, like running Dijkstra's algorithm
    // ...

    return 0;
}

