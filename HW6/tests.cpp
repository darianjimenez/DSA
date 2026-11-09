#include "associative-array.hpp"
#include <cassert>
#include <iostream>
#include <string>
using namespace std;

string encode(const string &text);
string decode(const string &compressed);

int main() {
    AssociativeArray<string, int> table;

    // Test adding and getting values
    table.set("cat", 1);
    table.set("dog", 2);
    assert(table.size() == 2);
    assert(table.contains("cat"));
    assert(table.get("dog") == 2);
    assert(!table.contains("bird"));
    assert(!table.get("bird").has_value());

    // Test updating and removing values
    table.set("cat", 5);
    assert(table.get("cat") == 5);
    assert(table.size() == 2);
    assert(table.remove("cat"));
    assert(!table.remove("cat"));
    assert(!table.contains("cat"));
    assert(table.size() == 1);

    // Test collisions and rehashing
    AssociativeArray<int, int> numbers;
    numbers.set(1, 10);
    numbers.set(54, 20); // Both go to bucket 1
    assert(numbers.get(1) == 10);
    assert(numbers.get(54) == 20);

    // Test getting all keyvalue pairs
    auto pairs = table.keyValuePairs();
    assert(pairs.size() == 1);
    assert(pairs[0].first == "dog");
    assert(pairs[0].second == 2);

    // Add enough items to make table grow
    for (int i = 100; i < 200; i++) {
        numbers.set(i, i * 2);
    }
    assert(numbers.get(1) == 10);
    assert(numbers.get(54) == 20);
    assert(numbers.get(150) == 300);

    // Test compression and decompression
    string text = "banana banana banana";
    string compressed = encode(text);
    string restored = decode(compressed);
    assert(restored == text);
    assert(decode(encode("ABABABA")) == "ABABABA");
    assert(decode(encode("")) == "");

    cout << "All tests passed!" << endl;
}