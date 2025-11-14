// src/dijkstra.cpp
#include "dijkstra.hpp"

#include <queue>
#include <limits>
#include <algorithm>

namespace {
    std::vector<int> reconstructPath(int src, int dest, const std::vector<int>& parent) {
        std::vector<int> path;
        if (dest < 0 || dest >= (int)parent.size()) return path;
        if (src < 0 || src >= (int)parent.size()) return path;

        int cur = dest;
        if (parent[cur] == -1 && cur != src) return {};

        while (cur != -1) {
            path.push_back(cur);
            if (cur == src) break;
            cur = parent[cur];
        }
        std::reverse(path.begin(), path.end());
        if (!path.empty() && path.front() == src) return path;
        return {};
    }
}

std::vector<int> dijkstraShortestPath(
    const Graph& g,
    int src,
    int dest,
    double& totalWeight
) {
    int n = g.numVertices();
    totalWeight = 0.0;

    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    std::vector<int> parent(n, -1);
    std::vector<bool> visited(n, false);

    using P = std::pair<double, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;

    dist[src] = 0.0;
    pq.push(P(0.0, src));

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        if (u == dest) break;

        for (const Edge& e : g.neighbors(u)) {
            int v = e.to;
            double w = e.weight;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push(P(dist[v], v));
            }
        }
    }

    if (!std::isfinite(dist[dest])) return {};

    totalWeight = dist[dest];
    return reconstructPath(src, dest, parent);
}

std::vector<int> bfsShortestPath(
    const Graph& g,
    int src,
    int dest
) {
    int n = g.numVertices();
    std::vector<bool> visited(n, false);
    std::vector<int> parent(n, -1);

    std::queue<int> q;
    visited[src] = true;
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == dest) break;

        for (const Edge& e : g.neighbors(u)) {
            int v = e.to;
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    return reconstructPath(src, dest, parent);
}

bool isConnected(const Graph& g) {
    int n = g.numVertices();
    if (n == 0) return true;

    std::vector<bool> visited(n, false);
    std::queue<int> q;

    visited[0] = true;
    q.push(0);
    int count = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (const Edge& e : g.neighbors(u)) {
            int v = e.to;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
                count++;
            }
        }
    }

    return count == n;
}