#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "heap-sort.hpp"
#include "insertion-sort.hpp"
#include "merge-sort.hpp"
#include "selection-sort.hpp"

using namespace std;

// Create list of random ints
vector<int> randomList(int size) {
    vector<int> arr;
    for (int i = 0; i < size; i++) {
        arr.push_back(rand() % 100000);
    }
    return arr;
}

template <typename SortFunction>
void testSort(string name, vector<int> arr, SortFunction sortFunction) {
    auto start = chrono::high_resolution_clock::now(); // start timer
    sortFunction(arr);

    auto end = chrono::high_resolution_clock::now();             // stop timer
    double time = chrono::duration<double>(end - start).count(); // calc runtime

    cout << name << ": " << time << " seconds" << endl;
}

int main() {
    srand(time(0)); // random num generator

    vector<int> sizes = {10, 100, 1000, 10000, 100000}; // sizes to test

    for (int size : sizes) {
        vector<int> arr = randomList(size); // generate list for each alg

        cout << "List size: " << size << endl;

        testSort("Selection Sort", arr, selectionSort);
        testSort("Insertion Sort", arr, insertionSort);
        testSort("Heap Sort", arr, heapSort);
        testSort("Merge Sort", arr, mergeSort);

        cout << endl;
    }

    return 0;
}