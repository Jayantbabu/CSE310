#include "main.h"
#include "minheap.h"
#include <iostream>
#include <sstream>
#include <iomanip> // For std::setw and std::setprecision
#include <vector>
#include <string>
#include <limits>
#include <algorithm>

const float INF = std::numeric_limits<float>::infinity();

// Assume the 'dijkstra' function is updated to print the details when the flag is 1
// You will need to adjust the 'dijkstra' implementation accordingly

void processCommands(const std::vector<std::vector<Edge>>& graph) {
    std::string line, command, temp;
    int source, destination, flag;

    std::vector<float> distances(graph.size(), INF);
    std::vector<int> predecessors(graph.size(), -1);

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        iss >> command;
        //std::cout << "Command" << command;
        if (command == "find") {
            iss >> source >> destination >> flag;
            if (source < 0 || source >= graph.size() || destination < 0 || destination >= graph.size()) {
                std::cout << "Error: invalid find query\n";
                continue;
            }

            // Call your dijkstra function here which should handle the flag
            dijkstra(graph, source, distances, predecessors, flag);

        } else if (command == "write") {
            iss >> temp >> source >> destination;
            if (source < 0 || source >= graph.size() || destination < 0 || destination >= graph.size()) {
                std::cout << "Error: invalid source destination pair\n";
                continue;
            }

            // Output the path and its details
            if (distances[destination] == INF) {
                std::cout << "No " << source << "-" << destination << " path has been computed.\n";
            } else {
                std::vector<int> path;
                for (int at = destination; at != -1; at = predecessors[at]) {
                    path.push_back(at);
                }
                std::reverse(path.begin(), path.end());

                if (path.size() == 1) { // Only the source vertex is in the path
                    std::cout << "No " << source << "-" << destination << " path exists.\n";
                } else {
                    // Check if this is the shortest path or not
                    if (predecessors[destination] != -1) {
                        std::cout << "Shortest path: ";
                    } else {
                        std::cout << "Path not known to be shortest: ";
                    }

                    for (int v : path) {
                        std::cout << v << " ";
                    }
                    std::cout << "\nThe path weight is: "
                              << std::fixed << std::setprecision(4)
                              << distances[destination] << "\n";
                }
            }

        } else if (command == "stop") {
            break;
        } else {
            std::cout << "Unknown command\n";
        }
    }
}
