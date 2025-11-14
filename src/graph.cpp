// src/graph.cpp
#include "graph.hpp"
#include <stdexcept>

Graph::Graph() : V(0), adj() {}

Graph::Graph(int n) : V(n), adj(n) {}

void Graph::resize(int n) {
    V = n;
    adj.clear();
    adj.resize(n);
}

int Graph::numVertices() const {
    return V;
}

void Graph::addEdge(int u, int v, double w, bool bidirectional) {
    if (u < 0 || v < 0 || u >= V || v >= V) {
        throw std::out_of_range("Vertex index out of range in addEdge");
    }
    adj[u].emplace_back(v, w);
    if (bidirectional) {
        adj[v].emplace_back(u, w);
    }
}

const std::vector<Edge>& Graph::neighbors(int u) const {
    if (u < 0 || u >= V) {
        throw std::out_of_range("Vertex index out of range in neighbors");
    }
    return adj[u];
}
