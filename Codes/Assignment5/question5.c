#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void matrixMultiplySerial(int n, int **A, int **B, int **C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrixMultiplyStatic(int n, int **A, int **B, int **C) {
    #pragma omp parallel for schedule(static, 100)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrixMultiplyDynamic(int n, int **A, int **B, int **C) {
    #pragma omp parallel for schedule(dynamic, 100)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int n = 1500;
    int **A, **B, **C;

    A = malloc(n * sizeof(int *));
    B = malloc(n * sizeof(int *));
    C = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        A[i] = malloc(n * sizeof(int));
        B[i] = malloc(n * sizeof(int));
        C[i] = malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }

    // Serial
    clock_t start = clock();
    matrixMultiplySerial(n, A, B, C);
    clock_t end = clock();
    printf("Serial execution time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Static
    start = clock();
    matrixMultiplyStatic(n, A, B, C);
    end = clock();
    printf("Static execution time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Dynamic
    start = clock();
    matrixMultiplyDynamic(n, A, B, C);
    end = clock();
    printf("Dynamic execution time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Cleanup
    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
