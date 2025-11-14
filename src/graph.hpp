// src/graph.hpp
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

struct Edge {
    int to;
    double weight;
    Edge(int t, double w) : to(t), weight(w) {}
};

class Graph {
    int V;
    std::vector<std::vector<Edge>> adj;

public:
    Graph();
    explicit Graph(int n);

    void resize(int n);
    int numVertices() const;

    void addEdge(int u, int v, double w, bool bidirectional = true);

    const std::vector<Edge>& neighbors(int u) const;
};

#endif // GRAPH_HPP
