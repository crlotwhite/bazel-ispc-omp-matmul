// ISPC implementation of matrix multiplication
export void matmul_ispc(const uniform double matA[], 
                        const uniform double matB[], 
                        uniform double C[],
                        uniform int rows, 
                        uniform int cols) {
    uniform int count = rows * cols;
    foreach (i = 0 ... count) {
        int row = i / cols;
        int col = i % cols;
        
        double sum = 0.0;
        for (int k = 0; k < cols; ++k) {
            sum += matA[row * cols + k] * matB[k * cols + col];
        }
        
        C[i] = sum;
    }
}

