#include <cstdlib>
#include <iostream>
#include "matmul/matmul.h"
#include "matutils/utils.h"


int main() {
    std::cout << "MatMul Example" << std::endl;
    std::cout << "CPU Mode" << std::endl;

    std::size_t rows = 4096;
    std::size_t cols = 4096;

    // matA
    double* matA = allocate_matrix_contiguous(rows, cols);
    if (!matA) {
        std::cerr << "Allocation failed\n";
        return 1;
    }

    fill_matrix(matA, rows, cols, 3.14);

    // matB
    double* matB = allocate_matrix_contiguous(rows, cols);
    if (!matB) {
        std::cerr << "Allocation failed\n";
        free_matrix(matA);
        return 1;
    }

    fill_matrix(matB, rows, cols, 2.71);

    // C = A * B
    double* matC = matmul(matA, matB, rows, cols);
    if (!matC) {
        std::cerr << "Matrix multiplication failed\n";
        free_matrix(matA);
        free_matrix(matB);
        return 1;
    }

    // print a few sample values
    std::cout << "mat[0,0] = " << mat_at(matC, cols, 0, 0) << "\n";
    std::cout << "mat[" << rows-1 << "," << cols-1 << "] = " << mat_at(matC, cols, rows-1, cols-1) << "\n";

    free_matrix(matA);
    free_matrix(matB);
    free_matrix(matC);

    return 0;
}
