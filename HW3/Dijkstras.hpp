/**
 * Dijkstras Algorithm Implementation
 */

#pragma once
#include "Graph.hpp"
#include "MinPriorityQueue.hpp"
#include <algorithm>
#include <limits>
#include <optional>
#include <unordered_map>
#include <vector>

using namespace std;
template <typename V>

optional<vector<V>> dijkstra(Graph<V> &graph, V start, V target) {
    unordered_map<V, double> dist; // Shortest distance to each vertex
    unordered_map<V, V> prev;      // Prev vertex used to reach each vertex

    MinPriorityQueue<V> queue; // Which vertex to check next?

    auto vertices = graph.getVertices(); // get all vertices

    // Set all distances to infinity
    for (auto vertex : vertices) {
        dist[vertex] = numeric_limits<double>::infinity();
        queue.addWithPriority(vertex, dist[vertex]);
    }

    // Check both start and target exist
    if (dist.find(start) == dist.end() ||
        dist.find(target) == dist.end()) {
        return nullopt;
    }

    dist[start] = 0;                // Dist from start to itself is 0
    queue.adjustPriority(start, 0); // Start is the first vertex checked

    // Keep goign until no vertices left
    while (!queue.isEmpty()) {
        auto nextVertex = queue.next(); // get vertex with lowest priority
        if (!nextVertex.has_value()) {
            break;
        }
        V current = nextVertex.value();

        if (current == target) // stop if target reached
            break;

        auto edges = graph.getEdges(current);

        // Check each neighboring vertex
        for (auto edge : edges) {
            V neighbor = edge.first;
            double cost = edge.second;

            double newDist = dist[current] + cost; // New possible dist to neighbor

            // If this path shorter, save
            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
                prev[neighbor] = current;                // Save how we got here
                queue.adjustPriority(neighbor, newDist); // Update priority in queue
            }
        }
    }

    // Couldnt find path
    if (start != target && prev.find(target) == prev.end()) {
        return nullopt;
    }

    // Make final path
    vector<V> path;
    V current = target;

    // Work backward from target to start
    while (current != start) {
        path.push_back(current);
        current = prev[current];
    }

    path.push_back(start);             // Add starting vertex
    reverse(path.begin(), path.end()); // Reverse path
    return path;
}