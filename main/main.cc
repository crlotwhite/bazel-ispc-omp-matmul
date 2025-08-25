#include <cstdlib>
#include <iostream>
#include "matmul/matmul.h"
#include "matutils/utils.h"


int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "2 + 3 = " << add(2, 3) << std::endl;

    // Demo: allocate a reasonably large matrix. For quick test keep small;
    // change rows/cols for real large allocations.
    std::size_t rows = 128; // small default for quick run; change as needed
    std::size_t cols = 128;
    double* mat = allocate_matrix_contiguous(rows, cols);
    if (!mat) {
        std::cerr << "Allocation failed\n";
        return 1;
    }

    fill_matrix(mat, rows, cols, 3.14);

    // print a few sample values
    std::cout << "mat[0,0] = " << mat_at(mat, cols, 0, 0) << "\n";
    std::cout << "mat[" << rows-1 << "," << cols-1 << "] = " << mat_at(mat, cols, rows-1, cols-1) << "\n";

    free_matrix(mat);

    return 0;
}
