#pragma once
#include <cstddef>

namespace cpu{
    double* matmul(const double* A, const double* B, std::size_t rows, std::size_t cols);
}
