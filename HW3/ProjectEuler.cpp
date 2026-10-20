/**
 * @file ProjectEuler.cpp
 * @brief Project Euler Problem 81 Solution
 */

#include "Dijkstras.hpp"
#include "Graph.hpp"
#include <fstream>
#include <iostream>
#include <optional>
#include <vector>

using namespace std;

/**
 * @brief Read matrix text file, create directional weighted graph
 *        and use Dijkstras implementation to find the min path from
 *        the top left cell to the bottom right.
 * @return 0 on exit
 */
int main() {
    ifstream file("matrix.txt");
    vector<vector<int>> matrix(80, vector<int>(80)); // make 80x80 matrix
    char comma;                                      // skip commas

    // Read matrix
    for (int row = 0; row < 80; row++) {
        for (int column = 0; column < 80; column++) {
            file >> matrix[row][column]; // store current num in matrix
            if (column < 79) {
                file >> comma;
            }
        }
    }

    Graph<int> graph;

    // Create graph
    for (int row = 0; row < 80; row++) {
        for (int column = 0; column < 80; column++) {
            int current = row * 80 + column; // give cells unique vertex num

            // Move right
            if (column < 79) {
                int right = current + 1;
                int cost = matrix[row][column + 1]; // cost = val of cell we move into
                graph.addEdge(current, right, cost);
            }

            // Move down
            if (row < 79) {
                int down = current + 80;
                int cost = matrix[row + 1][column]; // cost = val of cell we move into
                graph.addEdge(current, down, cost);
            }
        }
    }

    int start = 0;                           // top left = vertex 0
    int end = 6399;                          // last cell = 6399
    auto path = dijkstra(graph, start, end); // find path

    if (!path.has_value()) {
        cout << "No path found" << endl;
        return 0; // stop if no path found
    }

    int total = 0;
    for (int vertex : path.value()) {
        // conv vertex number back to row and col
        int row = vertex / 80;
        int column = vertex % 80;
        total += matrix[row][column];
    }

    cout << "Minimum path: " << total << endl;
    return 0;
}