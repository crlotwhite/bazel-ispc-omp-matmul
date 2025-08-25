#include "matmul.h"
#include "matutils/utils.h"

double* matmul(const double* A, const double* B, std::size_t rows, std::size_t cols) {
    if (!A || !B || rows == 0 || cols == 0) return nullptr;

    double* C = allocate_matrix_contiguous(rows, cols);
    if (!C) return nullptr;

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            C[i * cols + j] = 0;
            for (std::size_t k = 0; k < cols; ++k) {
                C[i * cols + j] += A[i * cols + k] * B[k * cols + j];
            }
        }
    }
    return C;
}
