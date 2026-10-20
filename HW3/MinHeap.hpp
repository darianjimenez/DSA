/**
 * @file MinHeap.hpp
 * @brief Min-heap with priorities, stored in a vector
 * The element with lowest priority stays at the top
 */

#pragma once
#include <optional>
#include <vector>

using namespace std;
template <typename T>

/**
 * @brief Min-heap where element with lowest priority is on top
 *
 * Complete binary tree stored in a vector.
 * For node at index i, parent = (i-1)/2, children = 2i+1 and 2i+2
 * Each node has a priority equal to or smaller than its children
 *
 * @param T Element type.
 */
class MinHeap {
private:
    // Store Element and Priority
    struct Node {
        T element;
        double priority;
    };

    vector<Node> heap; // heap stored in vector

    /**
     * @brief Move node up until min-heap property is correct
     * @param i Index of the node to move
     */
    void heapifyUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2; // find parent index

            // If current node priority is smaller, swap w/ parent
            if (heap[i].priority < heap[parent].priority) {
                Node temp = heap[i];
                heap[i] = heap[parent];
                heap[parent] = temp;
                i = parent; // keep checking from parents position
            } else {
                break;
            }
        }
    }

    /**
     * @brief Move node down until min-heap property is correct
     * @param i Index of the node to move
     */
    void heapifyDown(int i) {
        while (true) {
            int left = 2 * i + 1;  // Find left child index
            int right = 2 * i + 2; // Find right child index
            int smallest = i;

            // Left smaller priority?
            if (left < heap.size() &&
                heap[left].priority < heap[smallest].priority) {
                smallest = left;
            }
            // or right smaller priority?
            if (right < heap.size() &&
                heap[right].priority < heap[smallest].priority) {
                smallest = right;
            }
            // Stop if current node smallest
            if (smallest == i) {
                break;
            }
            // Swap current node with smaller child
            Node temp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = temp;

            i = smallest; // keep checking
        }
    }

public:
    /**
     * @brief Adds element with priority O(logn)
     * @param element  Element to add
     * @param priority Priority of element based on value
     */
    void push(T element, double priority) {
        Node node = {element, priority};
        heap.push_back(node);
        heapifyUp(heap.size() - 1);
    }

    /**
     * @brief Removes the element with lowest priority
     * Do nothing if heap empty
     */
    void pop() {
        if (heap.empty()) {
            return;
        }
        if (heap.size() == 1) {
            heap.pop_back();
            return;
        }
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    /**
     * @brief Gets the element with the lowest priority without removing it
     * @return The top element (null if heap empty)
     */
    optional<T> peek() {
        if (heap.empty()) {
            return nullopt;
        }
        return heap[0].element;
    }

    /**
     * @brief Gets number of elements in the heap
     * @return Num of elements
     */
    int size() {
        return heap.size();
    }

    /**
     * @brief Changes the priority of an element already in the heap
     *
     * Finds the element with a linear search, updates its priority, then 
     * moves it up or down to restore the heap order
     *
     * @param element Element to update
     * @param newPriority Its new priority
     */
    void adjustPriority(T element, double newPriority) {
        // Search for element
        for (int i = 0; i < heap.size(); i++) {
            if (heap[i].element == element) {
                double oldPriority = heap[i].priority;
                heap[i].priority = newPriority; // change priority

                if (newPriority < oldPriority) {
                    heapifyUp(i); // If priority smaller, move up
                } else {
                    heapifyDown(i); // If priority larger, move down
                }
                return;
            }
        }
    }
};