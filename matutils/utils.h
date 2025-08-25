#pragma once
#include <cstddef>

// Allocate a contiguous rows x cols matrix of doubles.
// Returns a pointer to the first element (row-major). Returns nullptr on allocation failure.
double* allocate_matrix_contiguous(std::size_t rows, std::size_t cols);

// Free a matrix previously returned by allocate_matrix_contiguous.
void free_matrix(double* data) noexcept;

// Access helper: compute reference to element (i,j) when you have pointer and cols.
inline double& mat_at(double* data, std::size_t cols, std::size_t i, std::size_t j) {
	return data[i * cols + j];
}

// Fill the matrix with a constant value.
void fill_matrix(double* data, std::size_t rows, std::size_t cols, double value);
