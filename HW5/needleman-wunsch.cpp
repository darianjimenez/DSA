/**
 * @file needleman-wunsch.cpp
 * @brief Needleman-Wunsch algorithm for global sequence alignment
 */

#include "genome.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Stores result of a sequence alignment
 */
struct Alignment {
    string first;
    string second;
    int score;
};

/**
 * @brief Align two sequences using the Needleman-Wunsch algorithm
 *
 * @param a First DNA sequence
 * @param b Second DNA sequence
 * @return Alignment containing both aligned sequences and their score
 */
Alignment needlemanWunsch(string a, string b) {
    int n = a.size();
    int m = b.size();

    // Create scoring and traceback tables
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    vector<vector<char>> trace(n + 1, vector<char>(m + 1));

    // First row and column
    for (int i = 1; i <= n; i++) {
        dp[i][0] = -i;
        trace[i][0] = 'u';
    }
    for (int j = 1; j <= m; j++) {
        dp[0][j] = -j;
        trace[0][j] = 'l';
    }

    // Fill scoring table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            // Match = +1 and mismatch = -1
            int points = -1;
            if (a[i - 1] == b[j - 1]) {
                points = 1;
            }

            int diagonal = dp[i - 1][j - 1] + points;
            int up = dp[i - 1][j] - 1;
            int left = dp[i][j - 1] - 1;

            dp[i][j] = max(diagonal, max(up, left));

            // Save direction of best score
            if (dp[i][j] == diagonal) {
                trace[i][j] = 'd';
            } else if (dp[i][j] == up) {
                trace[i][j] = 'u';
            } else {
                trace[i][j] = 'l';
            }
        }
    }

    // Backtrace to align
    string alignedA = "";
    string alignedB = "";

    // Start at bottom right corner of table
    int i = n;
    int j = m;

    while (i > 0 || j > 0) {
        if (trace[i][j] == 'd') {
            // Add both characters
            alignedA += a[i - 1];
            alignedB += b[j - 1];
            i--;
            j--;
        } else if (trace[i][j] == 'u') {
            // Add character from A and gap in B
            alignedA += a[i - 1];
            alignedB += '-';
            i--;
        } else {
            // Add gap in A and character from B
            alignedA += '-';
            alignedB += b[j - 1];
            j--;
        }
    }

    // Reverse (backtrace starts at the end)
    reverse(alignedA.begin(), alignedA.end());
    reverse(alignedB.begin(), alignedB.end());

    return {alignedA, alignedB, dp[n][m]};
}

#ifndef RUN_TESTS
/**
 * @brief Run Needleman-Wunsch on DNA sequences
 *        Print final alignment score and aligned sequences
 * @return 0 
 */
int main() {
    Alignment result = needlemanWunsch(genomeSnippet, testAgainst);

    cout << "Score: " << result.score << endl;
    cout << "Genome Snippet: " << result.first << endl;
    cout << "Test Against:   " << result.second << endl;

    return 0;
}
#endif