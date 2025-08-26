#ifndef ISPC_MATMUL_H
#define ISPC_MATMUL_H

#include <cstddef>

namespace ispc {
    double* matmul(const double* matA, const double* matB, std::size_t rows, std::size_t cols);
}

#endif // ISPC_MATMUL_H
