/**
 * Merge Sort Algorithm Implementation
 *  1. Divide the array into 2 halves recursively
 *  2. Recursively apply merge sort to first half
 *  3. Reursively apply merge sort to second half
 *  4. Merge 2 halves into 1 array
 *  5. Return merged array as sorted result
 */

#include <iostream>
#include <vector>

using namespace std;

// Merge 2 sorted halves
void merge(vector<int> &arr, int left, int split, int right) {
    vector<int> temp;

    int i = left;      // track left
    int j = split + 1; // track right

    // Compare values from each half
    while (i <= split && j <= right) {
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i]);
            i++;
        } else {
            temp.push_back(arr[j]);
            j++;
        }
    }

    // Add remaining values from each half
    while (i <= split) {
        temp.push_back(arr[i]);
        i++;
    }
    while (j <= right) {
        temp.push_back(arr[j]);
        j++;
    }

    // Copy sorted values back
    for (int k = 0; k < temp.size(); k++) {
        arr[left + k] = temp[k];
    }
}

// Recursively split and sort
void mergeSortHelper(vector<int> &arr, int left, int right) {
    // Stop when the section has 1 or fewer elements
    if (left >= right) {
        return;
    }

    int split = (left + right) / 2; // find where to split

    // Sort both halves
    mergeSortHelper(arr, left, split);
    mergeSortHelper(arr, split + 1, right);

    // Merge sorted halves
    merge(arr, left, split, right);
}

void mergeSort(vector<int> &arr) {
    mergeSortHelper(arr, 0, arr.size() - 1);
}
