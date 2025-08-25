#pragma once
#include <cstddef>

// Perform C = A * B where A, B, C are (rows x cols) matrices stored in row-major order.
double* matmul(const double* A, const double* B, std::size_t rows, std::size_t cols);