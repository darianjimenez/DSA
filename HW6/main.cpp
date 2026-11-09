#include <fstream>
#include <iostream>
#include <string>
using namespace std;

string encode(const string &text);
string decode(const string &compressed);

int main(int, char *argv[]) {
    // Read input file
    ifstream inputFile(argv[2], ios::binary);
    if (!inputFile)
        return 1;

    string input = "";
    char c;
    while (inputFile.get(c)) {
        input += c;
    }

    // Encode or decode
    string output;
    string mode = argv[1];

    if (mode == "encode") {
        output = encode(input);
    } else if (mode == "decode") {
        output = decode(input);
    } else {
        return 1;
    }

    // Save output file
    ofstream outputFile(argv[3], ios::binary);
    if (!outputFile)
        return 1;

    outputFile.write(output.data(), output.size());
    if (!outputFile)
        return 1;

    cout << "Input: " << input.size() << " bytes\n";
    cout << "Output: " << output.size() << " bytes\n";

    return 0;
}
