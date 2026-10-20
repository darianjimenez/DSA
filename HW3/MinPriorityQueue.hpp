/**
 * @file MinPriorityQueue.hpp
 * @brief Min priority queue implemented using MinHeap file
 *        Lower priority values are removed first
 */

#pragma once
#include "MinHeap.hpp"
#include <iostream>
#include <optional>

using namespace std;
template <typename T>

/**
 * @brief A priority queue where lower priority values are removed first
 * @param T Element type
 */
class MinPriorityQueue {
private:
    MinHeap<T> heap; // storage

public:
    /**
     * @brief Checks if queue empty
     * @return true if the queue is empty, false otherwise
     */
    bool isEmpty() {
        return heap.size() == 0;
    }

    /**
     * @brief Add [elem] with at level [priority]
     * @param elem     Element to add
     * @param priority Its priority, lower values are removed first
     */
    void addWithPriority(T elem, double priority) {
        heap.push(elem, priority);
    }

    /**
     * @brief Get the next (highest priority) element and remove this element from the queue
     * @return the next element in terms of priority.  If empty, return null.
     */
    optional<T> next() {
        optional<T> item = heap.peek();

        if (item.has_value()) {
            heap.pop();
        }
        return item;
    }

    /**
     * @brief Adjust the priority of the given element
     * @param elem whose priority should change
     * @param newPriority the priority to use for the element
     *                    the lower the priority the earlier the element int
     *                    the order.
     */
    void adjustPriority(T elem, double newPriority) {
        heap.adjustPriority(elem, newPriority);
    }
};