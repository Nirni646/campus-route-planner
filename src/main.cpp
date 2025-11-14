// src/main.cpp
#include <iostream>
#include <string>
#include <vector>

#include "graph.hpp"
#include "dijkstra.hpp"
#include "io.hpp"

void printPath(const std::vector<int>& path, const CampusMap& cmap) {
    if (path.empty()) {
        std::cout << "No path found.\n";
        return;
    }
    for (size_t i = 0; i < path.size(); ++i) {
        int id = path[i];
        if (id >= 0 && id < (int)cmap.idToName.size()) {
            std::cout << cmap.idToName[id];
        } else {
            std::cout << "?" ;
        }
        if (i + 1 < path.size()) {
            std::cout << " -> ";
        }
    }
    std::cout << "\n";
}

void listLocations(const CampusMap& cmap) {
    std::cout << "Locations:\n";
    for (size_t i = 0; i < cmap.idToName.size(); ++i) {
        std::cout << i << ": " << cmap.idToName[i] << "\n";
    }
}

std::string readLocationName(const std::string& prompt) {
    std::string name;
    std::cout << prompt;
    std::cin >> name; // assumes no spaces in name
    return name;
}

int main() {
    std::string filename = "data/campus_map.txt";
    CampusMap cmap = loadCampusMap(filename);

    if (cmap.g.numVertices() == 0) {
        std::cerr << "Campus map is empty or not loaded. Exiting.\n";
        return 1;
    }

    int choice = -1;
    while (true) {
        std::cout << "\n=== IITJ Campus Route Planner ===\n";
        std::cout << "1. List all locations\n";
        std::cout << "2. Shortest path (by distance)\n";
        std::cout << "3. Shortest path (by number of hops)\n";
        std::cout << "4. Check if campus map is connected\n";
        std::cout << "5. Shortest path with a blocked road\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter choice: ";
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Exiting.\n";
            break;
        }

        if (choice == 6) {
            std::cout << "Goodbye!\n";
            break;
        }

        switch (choice) {
        case 1: {
            listLocations(cmap);
            break;
        }
        case 2: {
            std::string startName = readLocationName("Enter start location (exact name): ");
            std::string destName  = readLocationName("Enter destination location (exact name): ");

            int src = getLocationId(cmap, startName);
            int dest = getLocationId(cmap, destName);

            if (src == -1 || dest == -1) {
                std::cout << "Unknown start or destination.\n";
                break;
            }

            double totalDist = 0.0;
            std::vector<int> path = dijkstraShortestPath(cmap.g, src, dest, totalDist);

            std::cout << "Shortest path (by distance):\n";
            printPath(path, cmap);
            if (!path.empty()) {
                std::cout << "Total distance: " << totalDist << "\n";
            }
            break;
        }
        case 3: {
            std::string startName = readLocationName("Enter start location (exact name): ");
            std::string destName  = readLocationName("Enter destination location (exact name): ");

            int src = getLocationId(cmap, startName);
            int dest = getLocationId(cmap, destName);

            if (src == -1 || dest == -1) {
                std::cout << "Unknown start or destination.\n";
                break;
            }

            std::vector<int> path = bfsShortestPath(cmap.g, src, dest);

            std::cout << "Shortest path (by number of hops):\n";
            printPath(path, cmap);
            if (!path.empty()) {
                std::cout << "Number of hops: " << (path.size() - 1) << "\n";
            }
            break;
        }
        case 4: {
            bool conn = isConnected(cmap.g);
            if (conn) {
                std::cout << "The campus map graph is connected.\n";
            } else {
                std::cout << "The campus map graph is NOT fully connected.\n";
            }
            break;
        }
        case 5: {
            std::string startName = readLocationName("Enter start location (exact name): ");
            std::string destName  = readLocationName("Enter destination location (exact name): ");

            int src = getLocationId(cmap, startName);
            int dest = getLocationId(cmap, destName);

            if (src == -1 || dest == -1) {
                std::cout << "Unknown start or destination.\n";
                break;
            }

            std::string blockFrom = readLocationName("Enter blocked road FROM location: ");
            std::string blockTo   = readLocationName("Enter blocked road TO location: ");

            int avoidU = getLocationId(cmap, blockFrom);
            int avoidV = getLocationId(cmap, blockTo);

            if (avoidU == -1 || avoidV == -1) {
                std::cout << "Unknown blocked road endpoints.\n";
                break;
            }

            double totalDist = 0.0;
            std::vector<int> path = dijkstraAvoidingEdge(cmap.g, src, dest, avoidU, avoidV, totalDist);

            std::cout << "Shortest path avoiding blocked road " 
                      << blockFrom << " <-> " << blockTo << ":\n";
            printPath(path, cmap);
            if (!path.empty()) {
                std::cout << "Total distance: " << totalDist << "\n";
            }
            break;
        }
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}