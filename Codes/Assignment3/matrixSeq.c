#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initialize_matrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
}

void matrix_addition_sequential(int **matrixA, int **matrixB, int **matrixC, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};

    for (int s = 0; s < 5; s++) {
        int size = sizes[s];
        printf("\nMatrix size: %d x %d\n", size, size);

        int **matrixA = (int **)malloc(size * sizeof(int *));
        int **matrixB = (int **)malloc(size * sizeof(int *));
        int **matrixC = (int **)malloc(size * sizeof(int *));
        
        for (int i = 0; i < size; i++) {
            matrixA[i] = (int *)malloc(size * sizeof(int));
            matrixB[i] = (int *)malloc(size * sizeof(int));
            matrixC[i] = (int *)malloc(size * sizeof(int));
        }

        initialize_matrix(matrixA, size);
        initialize_matrix(matrixB, size);

        clock_t start_time = clock();
        matrix_addition_sequential(matrixA, matrixB, matrixC, size);
        clock_t end_time = clock();

        double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("Time taken by sequential computation: %.6f seconds\n", time_taken);

        for (int i = 0; i < size; i++) {
            free(matrixA[i]);
            free(matrixB[i]);
            free(matrixC[i]);
        }
        free(matrixA);
        free(matrixB);
        free(matrixC);
    }

    return 0;
}
