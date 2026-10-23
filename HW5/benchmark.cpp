/**
 * @file benchmark.cpp
 * @brief Compare convetional and Strassen matrix multiplication
 */

#include "matrix.hpp"
#include <chrono>
#include <iostream>

using namespace std;

int main() {
    // Test different sizes
    for (int n : {32, 64, 128, 256}) {
        Matrix a(n, n);
        Matrix b(n, n);

        // Fill matrix with values
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a(i, j) = i + j + 1;
                b(i, j) = (i + j) % 7;
            }
        }

        cout << "\nMatrix size: " << n << endl;

        // Regular multiplication
        auto start = chrono::steady_clock::now();
        Matrix normal = a.multiply(b).value();
        auto end = chrono::steady_clock::now();
        double time = chrono::duration<double, milli>(end - start).count();
        cout << "Regular: " << time << " ms" << endl;

        // Strassen
        for (int cutoff : {1, 16, 32, 64}) {
            start = chrono::steady_clock::now();
            Matrix result = a.strassenMultiply(b, cutoff).value();
            end = chrono::steady_clock::now();
            time = chrono::duration<double, milli>(end - start).count();
            cout << "Cutoff " << cutoff << ": " << time << " ms" << endl;

            // Check that results match
            if (result(0, 0) != normal(0, 0)) {
                cout << "Results don't match" << endl;
            }
        }
    }

    return 0;
}
