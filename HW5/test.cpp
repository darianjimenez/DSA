#define RUN_TESTS
#include "matrix.hpp"
#include "needleman-wunsch.cpp"
#include <cassert>
#include <iostream>
using namespace std;

// Test matrix operations
void testMatrix() {
    // Create two 2x2 matrices
    Matrix a(2, 2);
    Matrix b(2, 2);

    a(0, 0) = 1;
    a(0, 1) = 2;
    a(1, 0) = 3;
    a(1, 1) = 4;
    b(0, 0) = 5;
    b(0, 1) = 6;
    b(1, 0) = 7;
    b(1, 1) = 8;

    // Test matrix size and values
    assert(a.num_rows() == 2);
    assert(a.num_cols() == 2);
    assert(a(0, 0) == 1);
    assert(a(1, 1) == 4);

    // Test splitting
    vector<Matrix> parts = a.split();
    assert(parts[0](0, 0) == 1);
    assert(parts[1](0, 0) == 2);
    assert(parts[2](0, 0) == 3);
    assert(parts[3](0, 0) == 4);

    // Test adding and subtracting
    assert(a.add(b)(0, 0) == 6);
    assert(a.subtract(b)(0, 0) == -4);

    // Test multiplication
    Matrix normal = a.multiply(b).value();
    Matrix strassen = a.strassenMultiply(b).value();

    assert(normal(0, 0) == 19);
    assert(normal(0, 1) == 22);
    assert(normal(1, 0) == 43);
    assert(normal(1, 1) == 50);

    // Both algorithms should give same answer
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            assert(normal(i, j) == strassen(i, j));
        }
    }

    // Test incompatible sizes
    Matrix c(3, 3);
    assert(!a.multiply(c).has_value());
    assert(!a.strassenMultiply(c).has_value());

    cout << "Matrix tests passed" << endl;
}

// Test Strassen on larger matrices
void testStrassen() {
    // Create two 4x4 matrices
    Matrix a(4, 4);
    Matrix b(4, 4);

    // Fill matrices
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            a(i, j) = i + j + 1;
            b(i, j) = (i + j) % 3;
        }
    }

    // Multiply using three approaches
    Matrix normal = a.multiply(b).value();
    Matrix strassen = a.strassenMultiply(b).value();
    Matrix hybrid = a.strassenMultiply(b, 2).value();

    // Compare multiplication results
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            assert(normal(i, j) == strassen(i, j));
            assert(normal(i, j) == hybrid(i, j));
        }
    }

    cout << "Strassen tests passed" << endl;
}

// Test Needleman-Wunsch
void testNeedlemanWunsch() {
    // Same sequences
    Alignment a = needlemanWunsch("ACGT", "ACGT");
    assert(a.score == 4);
    assert(a.first == a.second);

    // Mismatch
    Alignment b = needlemanWunsch("A", "T");
    assert(b.score == -1);

    // Gap
    Alignment c = needlemanWunsch("ACGT", "AGT");
    assert(c.score == 2);
    assert(c.first == "ACGT");
    assert(c.second == "A-GT");

    // Empty sequence
    Alignment d = needlemanWunsch("", "AG");
    assert(d.score == -2);

    // Provided DNA sequences
    Alignment e = needlemanWunsch(genomeSnippet, testAgainst);
    assert(e.score == 143);
    assert(e.first.size() == e.second.size());

    cout << "Needleman-Wunsch tests passed" << endl;
}

int main() {
    testMatrix();
    testStrassen();
    testNeedlemanWunsch();

    cout << "All tests passed!" << endl;
    return 0;
}