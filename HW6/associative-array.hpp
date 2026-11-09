#pragma once
#include <functional>
#include <list>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

/**
 * Represents mapping of keys to values
 * @param K the type of the keys
 * @param V the type of the values
 */
template <typename K, typename V>
class AssociativeArray {
private:
    vector<list<pair<K, V>>> table;
    int count = 0;

    // Prime bucket sizes (https://planetmath.org/goodhashtableprimes)
    vector<int> primes = {
        53, 97, 193, 389, 769, 1543, 3079, 6151,
        12289, 24593, 49157, 98317, 196613, 393241,
        786433, 1572869, 3145739, 6291469, 12582917,
        25165843, 50331653, 100663319, 201326611,
        402653189, 805306457, 1610612741};
    int primeIndex = 0;

    // Division --> use remainder to choose a bucket
    int hashIndex(const K &key) const {
        return hash<K>{}(key) % table.size();
    }

    // Move all key value pairs to a bigger table
    void rehash() {
        if (primeIndex + 1 >= (int)primes.size()) {
            throw runtime_error("Hash table is too large");
        }

        int newSize = primes[primeIndex + 1];
        vector<list<pair<K, V>>> biggerTable(newSize);

        for (auto &bucket : table) {
            for (auto &item : bucket) {
                int index = hash<K>{}(item.first) % newSize;
                biggerTable[index].push_back(item);
            }
        }

        table = biggerTable;
        primeIndex++;
    }

public:
    AssociativeArray() : table(53) {}

    /**
     * Insert the mapping from the key, [k], to the value, [v].
     * If the key already maps to a value, replace the mapping.
     */
    void set(const K &k, const V &v) {
        int index = hashIndex(k);

        for (auto &item : table[index]) {
            if (item.first == k) {
                item.second = v;
                return;
            }
        }

        table[index].push_back({k, v});
        count++;

        // Resize when load factor > 75%
        if (count > table.size() * 0.75) {
            rehash();
        }
    }

    /**
     * @return true if [k] is a key in the associative array
     */
    bool contains(const K &k) const {
        return get(k).has_value();
    }

    /**
     * @return the value associated with the key [k] or null if it doesn't exist
     */
    optional<V> get(const K &k) const {
        for (auto &item : table[hashIndex(k)]) {
            if (item.first == k) {
                return item.second;
            }
        }
        return nullopt;
    }

    /**
     * Remove the key, [k], from the associative array
     * @param k the key to remove
     * @return true if the item was successfully removed and false if the element was not found
     */
    bool remove(const K &k) {
        auto &bucket = table[hashIndex(k)];

        for (auto it = bucket.begin(); it != bucket.end(); it++) {
            if (it->first == k) {
                bucket.erase(it);
                count--;
                return true;
            }
        }
        return false;
    }

    /**
     * @return the number of elements stored in the hash table
     */
    int size() const {
        return count;
    }

    /**
     * @return the full list of key value pairs for the associative array
     */
    vector<pair<K, V>> keyValuePairs() const {
        vector<pair<K, V>> result;

        for (auto &bucket : table) {
            for (auto &item : bucket) {
                result.push_back(item);
            }
        }
        return result;
    }
};
