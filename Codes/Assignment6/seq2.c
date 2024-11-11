//Implementation of Matrix-vector Multiplication.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void matrixVectorMultiply(int **matrix, int *vector, int *result, int N) {
    for (int i = 0; i < N; ++i) {
        result[i] = 0;
        for (int j = 0; j < N; ++j) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

int main() {
    int N;
    printf("Enter the size of the matrix and vector: ");
    scanf("%d", &N);

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

    clock_t start = clock();

    matrixVectorMultiply(matrix, vector, result, N);

    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Time taken for sequential matrix-vector multiplication: %f seconds\n", time_taken);

    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vector);
    free(result);

    return 0;
}
