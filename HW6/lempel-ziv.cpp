#include "associative-array.hpp"
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

/**
 * Compress text using Lempel-Ziv 78
 * Stores each new phrase as a 2 byte dictionary number followed by one character
 * @param text Original text
 * @return Compressed binary str
 */
string encode(const string &text) {
    AssociativeArray<string, int> dict;
    string current = "";
    string output = "";

    for (char letter : text) {
        string next = current + letter;

        if (dict.contains(next)) {
            current = next;
        } else {
            int number = 0; // Index 0 = empty phrase

            if (current != "") {
                number = dict.get(current).value();
            }

            // Store dict number and next character
            output += char(number / 256);
            output += char(number % 256);
            output += letter;

            dict.set(next, dict.size() + 1);
            current = "";

            // Reset when the 2 byte dict is full
            if (dict.size() == 65535) {
                dict = AssociativeArray<string, int>();
            }
        }
    }

    // Save final phrase if already in the dictionary
    if (current != "") {
        int number = dict.get(current).value();
        output += char(number / 256);
        output += char(number % 256);
    }
    return output;
}

/**
 * Decodes Lempel Ziv compressed data
 * @param compressed Compressed binary string
 * @return Original text
 */
string decode(const string &compressed) {
    vector<string> dict = {""};
    string output = "";
    size_t i = 0;

    while (i < compressed.size()) {
        if (i + 1 >= compressed.size()) {
            throw runtime_error("Incomplete data");
        }

        // Read 2 bytes to get the dictionary number
        int first = (unsigned char)compressed[i++];
        int second = (unsigned char)compressed[i++];
        int number = first * 256 + second;

        if (number >= (int)dict.size()) {
            throw runtime_error("Invalid dictionary number");
        }
        string phrase = dict[number];

        // Add next character (unless final phrase)
        if (i < compressed.size()) {
            phrase += compressed[i++];
            dict.push_back(phrase);
        }
        output += phrase;

        // Reset the dict at the same size as the encoder
        if (dict.size() == 65536) {
            dict = {""};
        }
    }
    return output;
}