/**
 * Min priority queue implemented using MinHeap file
 * Lower priority values are removed first
 */

#pragma once
#include "MinHeap.hpp"
#include <iostream>
#include <optional>

using namespace std;
template <typename T>

class MinPriorityQueue {
private:
    MinHeap<T> heap;

public:
    /* @return true if the queue is empty, false otherwise */
    bool isEmpty() {
        return heap.size() == 0;
    }

    /* Add [elem] with at level [priority] */
    void addWithPriority(T elem, double priority) {
        heap.push(elem, priority);
    }

    /* Get the next (highest priority) element and remove this element from the queue.
       @return the next element in terms of priority.  If empty, return null. */
    optional<T> next() {
        optional<T> item = heap.peek();

        if (item.has_value()) {
            heap.pop();
        }
        return item;
    }

    /*
     * Adjust the priority of the given element
     * @param elem whose priority should change
     * @param newPriority the priority to use for the element
     *   the lower the priority the earlier the element int
     *   the order.
     */
    void adjustPriority(T elem, double newPriority) {
        heap.adjustPriority(elem, newPriority);
    }
};