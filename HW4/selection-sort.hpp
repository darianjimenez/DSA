/**
 * Selection Sort Implementation
 *  1. Find smallest element and swap with first
 *  2. Find second smallet, put it in second position
 *  3. Continue
 */

#include <iostream>
#include <vector>

using namespace std;

void selectionSort(vector<int> &arr) {
    // Go through each position in array
    for (int i = 0; i < arr.size(); i++) {
        int minIndex = i;

        // Find smallest remaining value
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Move smallest value to current position
        swap(arr[i], arr[minIndex]);
    }
}