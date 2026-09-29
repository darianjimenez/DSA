/**
 * Directed Weighted Graph
 * Each vertex stores neighboring vertices and edge costs
 */

#pragma once
#include <iostream>
#include <unordered_map> // MutableMap
#include <unordered_set> // MutableSet

using namespace std;

// @param VertexType the type that represents a vertex in the graph
template <typename VertexType>
class Graph {
private:
    unordered_map<VertexType, unordered_map<VertexType, double>> graph;

public:
    /* @return the vertices in the graph */
    unordered_set<VertexType> getVertices() {
        unordered_set<VertexType> vertices;
        for (auto vertex : graph) {
            vertices.insert(vertex.first);
        }
        return vertices;
    }

    /* Add an edge between [from] and [to] with edge weight [cost] */
    void addEdge(VertexType from, VertexType to, double cost) {
        // Add [from] if not in graph
        if (graph.find(from) == graph.end()) {
            graph[from] = {};
        }
        // Add [to] if not in graph
        if (graph.find(to) == graph.end()) {
            graph[to] = {};
        }
        // Add edge and cost
        graph[from][to] = cost;
    }

    /* Get all the edges that begin at [from]
     * @return a map where each key represents a vertex connected to [from] and the value represents the edge weight.*/
    unordered_map<VertexType, double> getEdges(VertexType from) {
        if (graph.find(from) != graph.end()) {
            return graph[from];
        }
        return {};
    }

    /* Remove all edges and vertices from the graph */
    void clear() {
        graph.clear();
    }
};
