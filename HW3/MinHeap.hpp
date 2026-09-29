/**
 * Min Heap stored in a vector
 * The element with lowest priority stays at the top
 */

#pragma once
#include <optional>
#include <vector>

using namespace std;
template <typename T>

class MinHeap {
private:
    // Store Element and Priority
    struct Node {
        T element;
        double priority;
    };

    vector<Node> heap; // heap stored in vector

    // Func to move node up until min-heap property is correct
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

    // Func to move node down until min-heap property is correct
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
    // Add element
    void push(T element, double priority) {
        Node node = {element, priority};
        heap.push_back(node);
        heapifyUp(heap.size() - 1);
    }

    // Remove min element
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

    // Return minimum element
    optional<T> peek() {
        if (heap.empty()) {
            return nullopt;
        }
        return heap[0].element;
    }

    // Find size
    int size() {
        return heap.size();
    }

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