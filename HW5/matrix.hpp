/**
 * @file matrix.hpp
 * @brief Matrix class with traditional and Strassen Multiplication
 */

#pragma once
#include <cstddef>
#include <optional>
#include <vector>

using namespace std;

/**
 * @brief Matrix class to store and perform matrix operations
 */
class Matrix {
private:
    size_t rows, cols;
    vector<double> storage;

    /**
     * @brief Strassens algorithm implementation for two equally sized, square matrices
     *        Recursively multiply matrices by splitting into 4 smaller ones
     *
     * @param A First square Matrix
     * @param B Second square Matrix
     * @param curoff Size to use regular multiplication at
     * @return Product of matrices
     */
    static Matrix strassen(const Matrix &A, const Matrix &B, size_t cutoff) {
        size_t n = A.rows;

        // Regular multiplication for small/odd matrices
        if (n <= cutoff || n % 2 != 0) {
            return A.multiply(B).value();
        }

        // Split into quarters
        vector<Matrix> a = A.split();
        vector<Matrix> b = B.split();

        // 7 multiplications from Strassens algorithm
        Matrix p1 = strassen(a[0].add(a[3]), b[0].add(b[3]), cutoff);
        Matrix p2 = strassen(a[2].add(a[3]), b[0], cutoff);
        Matrix p3 = strassen(a[0], b[1].subtract(b[3]), cutoff);
        Matrix p4 = strassen(a[3], b[2].subtract(b[0]), cutoff);
        Matrix p5 = strassen(a[0].add(a[1]), b[3], cutoff);
        Matrix p6 = strassen(a[2].subtract(a[0]), b[0].add(b[1]), cutoff);
        Matrix p7 = strassen(a[1].subtract(a[3]), b[2].add(b[3]), cutoff);

        // 4 blocks of the answer
        Matrix c1 = p1.add(p4).subtract(p5).add(p7);
        Matrix c2 = p3.add(p5);
        Matrix c3 = p2.add(p4);
        Matrix c4 = p1.subtract(p2).add(p3).add(p6);

        // Combine the 4 blocks back into one matrix
        Matrix result(n, n);
        size_t half = n / 2;
        for (size_t i = 0; i < half; i++) {
            for (size_t j = 0; j < half; j++) {
                result(i, j) = c1(i, j);
                result(i, j + half) = c2(i, j);
                result(i + half, j) = c3(i, j);
                result(i + half, j + half) = c4(i, j);
            }
        }
        return result;
    }

public:
    /**
     * @brief Create a matrix filled with zeros
     * @param numRows Number of Rows
     * @param numCols Number of Cloumns
     */
    // Create matrix
    Matrix(size_t numRows, size_t numCols) {
        rows = numRows;
        cols = numCols;
        storage = vector<double>(rows * cols, 0);
    }

    // Set or get a value
    double &operator()(size_t i, size_t j) {
        return storage[i * cols + j];
    }
    const double &operator()(size_t i, size_t j) const {
        return storage[i * cols + j];
    }

    // Get dimensions
    // Return num rows
    size_t num_rows() const {
        return rows;
    }
    // Return Num of columns
    size_t num_cols() const {
        return cols;
    }

    /**
     * @brief Split a square matrix equally into 4 matrices
     *
     * @return Vector containing the quarters of the Matrix
     * @note Assume even-sized square matrix
     */
    vector<Matrix> split() const {
        size_t half = rows / 2;

        Matrix a(half, half);
        Matrix b(half, half);
        Matrix c(half, half);
        Matrix d(half, half);

        // Copy values into each quarter
        for (size_t i = 0; i < half; i++) {
            for (size_t j = 0; j < half; j++) {
                a(i, j) = (*this)(i, j);
                b(i, j) = (*this)(i, j + half);
                c(i, j) = (*this)(i + half, j);
                d(i, j) = (*this)(i + half, j + half);
            }
        }

        return {a, b, c, d};
    }

    /**
     * @brief Add two matrices element by element
     *
     * @param other Matrix to add
     * @return Matrix containing the sum
     */
    Matrix add(const Matrix &other) const {
        Matrix result(rows, cols);
        for (size_t i = 0; i < storage.size(); i++) {
            result.storage[i] = storage[i] + other.storage[i];
        }
        return result;
    }

    /**
     * @brief Subtract two matrices element by element
     *
     * @param other Matrix to subtract
     * @return Matrix containing the difference
     */
    Matrix subtract(const Matrix &other) const {
        Matrix result(rows, cols);
        for (size_t i = 0; i < storage.size(); i++) {
            result.storage[i] = storage[i] - other.storage[i];
        }
        return result;
    }

    /**
     * @brief Multiply two matrices using traditional multiplication
     *
     * @param other Matrix to multiply by
     * @return Product of matrices, null if dimensions don't match
     */
    optional<Matrix> multiply(const Matrix &other) const {
        // Check if both are equally sized and square
        if (rows != cols || other.rows != other.cols || rows != other.rows) {
            return nullopt;
        }
        Matrix result(rows, rows);
        // Multiply each row by each column
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < rows; j++) {
                for (size_t k = 0; k < rows; k++) {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return result;
    }

    /**
     * @brief Multiply 2 matrices with Strassens
     * @return Product of matrices, null if dimensions don't match
     */
    optional<Matrix> strassenMultiply(const Matrix &other, size_t cutoff = 1) const {
        // Check both matrices are same size and square
        if (rows != cols || other.rows != other.cols || rows != other.rows) {
            return nullopt;
        }

        return strassen(*this, other, cutoff);
    }
};