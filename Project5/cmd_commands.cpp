#include "cmd_command.h"
#include "dijkstra.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <limits>
#include <algorithm>

const float INF = std::numeric_limits<float>::infinity();

void processCommands(const std::vector<std::vector<Edge>>& graph) {
    std::string line, command;
    int source, destination, flag;
    std::vector<float> distances; // To store the shortest path distances
    std::vector<int> predecessors; // To store the predecessors for path reconstruction

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        iss >> command;
        if (command == "find") {
            iss >> source >> destination >> flag;
            if (source < 0 || source >= graph.size() || destination < -1 || destination >= graph.size() || (flag != 0 && flag != 1)) {
                std::cout << "Error: invalid find query" << std::endl;
                continue;
            }

            // Execute Dijkstra's algorithm
            dijkstra(graph, source);

            if (flag == 1) {
                // Additional details can be printed here as per your algorithm's design
                // This could include details like insertions and deletions in the min-heap
            }
        } else if (command == "write path") {
            iss >> source >> destination;
            if (source != source || destination < 0 || destination >= graph.size()) {
                std::cout << "Error: invalid source destination pair" << std::endl;
                continue;
            }

            // Output the path and its details
            if (distances[destination] == INF) {
                std::cout << "No path exists from " << source << " to " << destination << std::endl;
            } else {
                std::cout << "Path from " << source << " to " << destination << ": ";
                std::vector<int> path;
                for (int at = destination; at != -1; at = predecessors[at]) {
                    path.push_back(at);
                }
                std::reverse(path.begin(), path.end());
                for (int v : path) {
                    std::cout << v << " ";
                }
                std::cout << "\nThe path weight is: " << distances[destination] << std::endl;
            }
        } else if (command == "stop") {
            break;
        } else {
            std::cout << "Unknown command" << std::endl;
        }
    }
}
