#include "ispc/matmul_ispc.h"
#include "matutils/utils.h"
#include <cstddef>

namespace ispc {

double* matmul(const double* matA, const double* matB, std::size_t rows, std::size_t cols) {
    if (!matA || !matB || rows == 0 || cols == 0) return nullptr;

    double* C = allocate_matrix_contiguous(rows, cols);
    if (!C) return nullptr;

    // Call the ISPC implementation
    ispc::matmul_ispc(matA, matB, C, static_cast<int>(rows), static_cast<int>(cols));
    
    return C;
}

} // namespace ispc
