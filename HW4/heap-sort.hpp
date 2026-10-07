/**
 * Heap Sort Implementation
 *  1. Treats unsorted array as binary tree
 *  2. Build max-heap to store data from unsorted list
 *  3. Extract largest value from heap and place into a sorted list
 *  4. Replace root of heap with the last element in the list. Then rebalance heap
 *  5. Once max heap is empty, return sorted list
 */

#include <iostream>
#include <vector>

using namespace std;

void heapify(vector<int> &arr, int n, int i) {
    int largest = i;

    // Find left and right child indeces
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Is left child larger?
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Is right child larger?
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If larger, swap and keep heapifying
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int> &arr) {
    int n = arr.size();

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Move largest values to end of array
    for (int i = n - 1; i > 0; i--) {
        swap(arr[i], arr[0]);
        heapify(arr, i, 0); // Rebalance remaining unsorted part
    }
}