/**
 * @file insertion-sort.hpp
 * @brief Insertion Sort Implementation
 *  1. Assume first element is sorted, move to second
 *  2. Compare first and second, if the second is smaller, shift
 *  3. Compare 3rd element with first 2 and place in correct position
 *  4. Repeat
 */

#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Sorts vector of ints O(n^2)
 * @param arr The vector to sort
 */
void insertionSort(vector<int> &arr) {
    // Start at 2nd element
    for (int i = 1; i < arr.size(); i++) {
        int current = arr[i];
        int j = i - 1;

        // Shift larger values right
        while (j >= 0 && arr[j] > current) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = current; // Insert current value
    }
}