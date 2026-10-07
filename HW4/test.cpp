#include "heap-sort.hpp"
#include "insertion-sort.hpp"
#include "merge-sort.hpp"
#include "selection-sort.hpp"
#include <cassert>
#include <vector>

using namespace std;
template <typename SortFunction>

void testAlg(SortFunction sortFunction) {
    // one element
    vector<int> arr_1 = {27};
    sortFunction(arr_1);
    assert(arr_1 == vector<int>({27}));

    // empty list
    vector<int> arr_empty = {};
    sortFunction(arr_empty);
    assert(arr_empty.empty());

    // random  list
    vector<int> arr_rand = {42, 7, 19, 3, 88, 25, 14};
    sortFunction(arr_rand);
    assert(arr_rand == vector<int>({3, 7, 14, 19, 25, 42, 88}));

    // already sorted
    vector<int> arr_sorted = {2, 11, 23, 37, 51, 72};
    sortFunction(arr_sorted);
    assert(arr_sorted == vector<int>({2, 11, 23, 37, 51, 72}));

    // reversed order
    vector<int> arr_reverse = {91, 74, 63, 40, 28, 12, 4};
    sortFunction(arr_reverse);
    assert(arr_reverse == vector<int>({4, 12, 28, 40, 63, 74, 91}));

    // duplicates
    vector<int> arr_dup = {8, 3, 8, 1, 5, 3, 9, 1};
    sortFunction(arr_dup);
    assert(arr_dup == vector<int>({1, 1, 3, 3, 5, 8, 8, 9}));

    // negative numbers
    vector<int> arr_neg = {12, -4, 7, -15, 0, 3};
    sortFunction(arr_neg);
    assert(arr_neg == vector<int>({-15, -4, 0, 3, 7, 12}));
}

int main() {
    testAlg(selectionSort);
    testAlg(insertionSort);
    testAlg(heapSort);
    testAlg(mergeSort);

    cout << "All tests passed!" << endl;

    return 0;
}