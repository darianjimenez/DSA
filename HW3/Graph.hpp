/**
 * @file Graph.hpp
 * @brief Directed Weighted Graph stored as adjacency list
 *        Each vertex stores neighboring vertices and edge costs
 */

#pragma once
#include <iostream>
#include <unordered_map> // MutableMap
#include <unordered_set> // MutableSet

using namespace std;

/**
 * @brief A directed, weighted graph
 * @param VertexType Type that represents a vertex in the graph
 */
template <typename VertexType>
class Graph {
private:
    // Adjacency list
    unordered_map<VertexType, unordered_map<VertexType, double>> graph;

public:
    /**
     * @brief Gets all vertices in the graph
     * @return A set containing all the vertices in the graph 
     */
    unordered_set<VertexType> getVertices() {
        unordered_set<VertexType> vertices;
        for (auto vertex : graph) {
            vertices.insert(vertex.first);
        }
        return vertices;
    }

    /**
     * @brief Add an edge between [from] and [to] with edge weight [cost] 
     * 
     * If not present, a vertex is added to the graph
     * If an edge already exists, its cost is replaced
     * 
     * @param from The vertex the edge starts at
     * @param to   The vertex the edge points to
     * @param cost The weight of the edge
     */
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

    /**
     * @brief Get all the edges that begin at [from]
     * @param from The vertex whose outgoing edges to look up
     * @return a map where each key represents a vertex connected
     *         to [from] and the value represents the edge weight.
     */
    unordered_map<VertexType, double> getEdges(VertexType from) {
        if (graph.find(from) != graph.end()) {
            return graph[from];
        }
        return {};
    }

    /**
     * @brief Removes all edges and vertices from the graph
     */
    void clear() {
        graph.clear();
    }
};
