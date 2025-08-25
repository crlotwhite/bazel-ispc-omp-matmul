
#include "utils.h"
#include <new>
#include <cstring>
#include <cstdlib>

double* allocate_matrix_contiguous(std::size_t rows, std::size_t cols) {
	if (rows == 0 || cols == 0) return nullptr;
	// check overflow: rows * cols shouldn't overflow size_t
	if (cols != 0 && rows > (SIZE_MAX / cols)) return nullptr;
	std::size_t n = rows * cols;
	// allocate using malloc to get contiguous memory; return nullptr on failure
	void* p = std::malloc(n * sizeof(double));
	if (!p) return nullptr;
	// zero-initialize for safety
	std::memset(p, 0, n * sizeof(double));
	return static_cast<double*>(p);
}

void free_matrix(double* data) noexcept {
	if (!data) return;
	std::free(data);
}

void fill_matrix(double* data, std::size_t rows, std::size_t cols, double value) {
	if (!data) return;
	std::size_t n = rows * cols;
	for (std::size_t i = 0; i < n; ++i) data[i] = value;
}
