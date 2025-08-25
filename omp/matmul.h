#pragma once

#include <cstddef>

namespace omp{
    double* matmul(const double* matA, const double* matB, std::size_t rows, std::size_t cols);
}