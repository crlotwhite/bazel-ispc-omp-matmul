#include "omp/matmul.h"
#include "matutils/utils.h"
#ifdef _OPENMP
#include <omp.h>
#endif

namespace omp{

    double* matmul(const double* matA, const double* matB, std::size_t rows, std::size_t cols) {
        if (!matA || !matB || rows == 0 || cols == 0) return nullptr;

        double* C = allocate_matrix_contiguous(rows, cols);
        if (!C) return nullptr;

        // Parallelize outer two loops (rows, cols). Each (i,j) computes an independent dot-product.
#pragma omp parallel for collapse(2) schedule(static)
            for (std::ptrdiff_t i = 0; i < static_cast<std::ptrdiff_t>(rows); ++i) {
                for (std::ptrdiff_t j = 0; j < static_cast<std::ptrdiff_t>(cols); ++j) {
                    double sum = 0.0;
                    for (std::ptrdiff_t k = 0; k < static_cast<std::ptrdiff_t>(cols); ++k) {
                        sum += matA[static_cast<std::size_t>(i) * cols + static_cast<std::size_t>(k)]
                             * matB[static_cast<std::size_t>(k) * cols + static_cast<std::size_t>(j)];
                    }
                    C[static_cast<std::size_t>(i) * cols + static_cast<std::size_t>(j)] = sum;
                }
            }

        return C;
    }

}