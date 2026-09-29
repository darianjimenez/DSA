#include "Dijkstras.hpp"
#include "Graph.hpp"
#include "MinHeap.hpp"
#include "MinPriorityQueue.hpp"
#include <cassert>
#include <iostream>

using namespace std;

void testDijkstra() {
    Graph<int> graph;

    graph.addEdge(1, 2, 5.0);
    graph.addEdge(1, 3, 2.0);
    graph.addEdge(3, 2, 1.0);
    graph.addEdge(2, 4, 3.0);

    // find shortest path from 1-4
    auto path = dijkstra(graph, 1, 4);
    assert(path.has_value());
    assert(path.value()[0] == 1);
    assert(path.value()[1] == 3);
    assert(path.value()[2] == 2);
    assert(path.value()[3] == 4);

    // check no path from 4 to 1
    assert(!dijkstra(graph, 4, 1).has_value());
}

void testGraph() {
    Graph<int> graph;

    assert(graph.getVertices().empty()); // graph starts empty

    // add 2 edges
    graph.addEdge(1, 2, 5.0);
    graph.addEdge(1, 3, 2.0);

    // Check all vertices added
    auto vertices = graph.getVertices();
    assert(vertices.size() == 3);

    // check edges from vertex 1
    auto edges = graph.getEdges(1);
    assert(edges[2] == 5.0);
    assert(edges[3] == 2.0);

    // clear graph, ensure empty
    graph.clear();
    assert(graph.getVertices().empty());
}

void testMinHeap() {
    MinHeap<int> heap;

    // start empty
    assert(heap.size() == 0);
    assert(!heap.peek().has_value());

    // add elements with priorities
    heap.push(1, 5.0);
    heap.push(2, 2.0);
    heap.push(3, 8.0);

    // 2 has smallest priority
    assert(heap.size() == 3);

    // change 3 to smallest
    assert(heap.peek().value() == 2);
    heap.pop();

    heap.adjustPriority(3, 1.0);

    assert(heap.peek().value() == 3);
    heap.pop();

    // 1 is last
    assert(heap.peek().value() == 1);
    heap.pop();

    // heap empty
    assert(heap.size() == 0);
}

void testMinPriorityQueue() {
    MinPriorityQueue<int> queue;

    assert(queue.isEmpty()); // start empty

    queue.addWithPriority(10, 5.0);
    queue.addWithPriority(20, 2.0);
    queue.addWithPriority(30, 8.0);

    assert(!queue.isEmpty());
    assert(queue.next().value() == 20); // 20 first

    queue.adjustPriority(30, 1.0); // make 30 highest priority

    assert(queue.next().value() == 30);
    assert(queue.next().value() == 10);
    assert(queue.isEmpty()); // queue empty
}

int main() {
    testGraph();
    testMinHeap();
    testMinPriorityQueue();
    testDijkstra();

    cout << "All tests passed!" << endl;

    return 0;
}