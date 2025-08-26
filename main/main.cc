#include <cstdlib>
#include <iostream>
#include "cpu/matmul.h"
#include "omp/matmul.h"
#include "ispc/matmul.h"
#include "matutils/utils.h"
#include "timeutils/utils.h"
#ifdef _OPENMP
#include <omp.h>
#endif

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
    double* matC = nullptr;
    TIME_EXECUTE("Matrix multiplication", matC = cpu::matmul(matA, matB, rows, cols));
    if (!matC) {
        std::cerr << "Matrix multiplication failed\n";
        free_matrix(matA);
        free_matrix(matB);
        return 1;
    }

    // print a few sample values
    std::cout << "mat[0,0] = " << mat_at(matC, cols, 0, 0) << "\n";
    std::cout << "mat[" << rows-1 << "," << cols-1 << "] = " << mat_at(matC, cols, rows-1, cols-1) << "\n";

    std::cout << "OpenMP Mode" << std::endl;

#ifdef _OPENMP
    // Print OpenMP runtime information for debugging
    std::cout << "_OPENMP macro: " << _OPENMP << std::endl;
    const char* omp_env = std::getenv("OMP_NUM_THREADS");
    if (omp_env) {
        std::cout << "OMP_NUM_THREADS env: " << omp_env << std::endl;
        omp_set_num_threads(std::atoi(omp_env));
    }
    std::cout << "omp_get_max_threads(): " << omp_get_max_threads() << std::endl;
    // Query threads inside a parallel region to observe actual threads used
    #pragma omp parallel
    {
        #pragma omp single
        {
            std::cout << "threads in parallel region (omp_get_num_threads): " << omp_get_num_threads() << std::endl;
        }
    }
#else
    std::cout << "OpenMP not enabled in this build (no _OPENMP)" << std::endl;

    free_matrix(matA);
    free_matrix(matB);
    free_matrix(matC);
    return 1;
#endif

    double* matD = nullptr;
    TIME_EXECUTE("Matrix multiplication (OpenMP)", matD = omp::matmul(matA, matB, rows, cols));
    if (!matD) {
        std::cerr << "Matrix multiplication failed\n";
        free_matrix(matA);
        free_matrix(matB);
        free_matrix(matC);
        return 1;
    }

    // print a few sample values
    std::cout << "mat[0,0] = " << mat_at(matD, cols, 0, 0) << "\n";
    std::cout << "mat[" << rows-1 << "," << cols-1 << "] = " << mat_at(matD, cols, rows-1, cols-1) << "\n";

    std::cout << "ISPC Mode" << std::endl;
    double* matE = nullptr;
    TIME_EXECUTE("Matrix multiplication (ISPC)", matE = ispc::matmul(matA, matB, rows, cols));
    if (!matE) {
        std::cerr << "Matrix multiplication failed\n";
        free_matrix(matA);
        free_matrix(matB);
        free_matrix(matC);
        free_matrix(matD);
        return 1;
    }

    // print a few sample values
    std::cout << "mat[0,0] = " << mat_at(matE, cols, 0, 0) << "\n";
    std::cout << "mat[" << rows-1 << "," << cols-1 << "] = " << mat_at(matE, cols, rows-1, cols-1) << "\n";

    free_matrix(matA);
    free_matrix(matB);
    free_matrix(matC);
    free_matrix(matD);
    free_matrix(matE);
    return 0;
}
