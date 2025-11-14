// src/dijkstra.hpp
#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <vector>
#include "graph.hpp"

// Dijkstra shortest path by weight
std::vector<int> dijkstraShortestPath(
    const Graph& g,
    int src,
    int dest,
    double& totalWeight
);

// Dijkstra shortest path avoiding a specific edge (u <-> v)
std::vector<int> dijkstraAvoidingEdge(
    const Graph& g,
    int src,
    int dest,
    int avoidU,
    int avoidV,
    double& totalWeight
);

// BFS shortest path by number of edges (ignores weights)
std::vector<int> bfsShortestPath(
    const Graph& g,
    int src,
    int dest
);

// Check if the graph is fully connected (single component)
bool isConnected(const Graph& g);

#endif // DIJKSTRA_HPP