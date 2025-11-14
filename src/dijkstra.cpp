// src/dijkstra.cpp
#include "dijkstra.hpp"

#include <queue>
#include <limits>
#include <functional>
#include <algorithm>   // for std::reverse

namespace {
    std::vector<int> reconstructPath(int src, int dest, const std::vector<int>& parent) {
        std::vector<int> path;
        if (dest < 0 || dest >= (int)parent.size()) return path;
        if (src < 0 || src >= (int)parent.size()) return path;

        int cur = dest;
        if (parent[cur] == -1 && cur != src) {
            // No path
            return {};
        }
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

    using P = std::pair<double, int>; // (dist, node)
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;

    dist[src] = 0.0;
    pq.push(P(0.0, src));

    while (!pq.empty()) {
        P top = pq.top();
        pq.pop();
        double d = top.first;
        int u = top.second;

        if (visited[u]) continue;
        visited[u] = true;

        if (u == dest) break;

        const std::vector<Edge>& neigh = g.neighbors(u);
        for (size_t i = 0; i < neigh.size(); ++i) {
            const Edge& e = neigh[i];
            int v = e.to;
            double w = e.weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push(P(dist[v], v));
            }
        }
    }

    // Check if unreachable (still infinity)
    if (dist[dest] == std::numeric_limits<double>::infinity()) {
        return {};
    }

    totalWeight = dist[dest];
    return reconstructPath(src, dest, parent);
}

std::vector<int> dijkstraAvoidingEdge(
    const Graph& g,
    int src,
    int dest,
    int avoidU,
    int avoidV,
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

    auto isBlocked = [avoidU, avoidV](int u, int v) {
        return (u == avoidU && v == avoidV) || (u == avoidV && v == avoidU);
    };

    while (!pq.empty()) {
        P top = pq.top();
        pq.pop();
        double d = top.first;
        int u = top.second;

        if (visited[u]) continue;
        visited[u] = true;

        if (u == dest) break;

        const std::vector<Edge>& neigh = g.neighbors(u);
        for (size_t i = 0; i < neigh.size(); ++i) {
            const Edge& e = neigh[i];
            int v = e.to;
            if (isBlocked(u, v)) continue; // skip blocked road
            double w = e.weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push(P(dist[v], v));
            }
        }
    }

    if (dist[dest] == std::numeric_limits<double>::infinity()) {
        return {};
    }

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

        const std::vector<Edge>& neigh = g.neighbors(u);
        for (size_t i = 0; i < neigh.size(); ++i) {
            const Edge& e = neigh[i];
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

        const std::vector<Edge>& neigh = g.neighbors(u);
        for (size_t i = 0; i < neigh.size(); ++i) {
            const Edge& e = neigh[i];
            int v = e.to;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
                ++count;
            }
        }
    }

    return count == n;
}
