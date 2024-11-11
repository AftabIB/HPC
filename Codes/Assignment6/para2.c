#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrixVectorMultiplyParallel(int **matrix, int *vector, int *result, int N) {
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        result[i] = 0;
        for (int j = 0; j < N; ++j) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

int main() {
    int N, num_threads;
    printf("Enter the size of the matrix and vector: ");
    scanf("%d", &N);

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    omp_set_num_threads(num_threads);

    int **matrix = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int *)malloc(N * sizeof(int));
    }

    int *vector = (int *)malloc(N * sizeof(int));
    int *result = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = 1;  
        }
        vector[i] = 1;
    }

    double start_time = omp_get_wtime();

    matrixVectorMultiplyParallel(matrix, vector, result, N);

    double end_time = omp_get_wtime();
    double time_taken = end_time - start_time;

    printf("Time taken for parallel matrix-vector multiplication: %f seconds\n", time_taken);

    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vector);
    free(result);

    return 0;
}
