#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrixMultiplyParallel(int **A, int **B, int **C, int N) {
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int N, num_threads;
    printf("Enter the size of the matrix: ");
    scanf("%d", &N);

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    omp_set_num_threads(num_threads);

    int **A = (int **)malloc(N * sizeof(int *));
    int **B = (int **)malloc(N * sizeof(int *));
    int **C = (int **)malloc(N * sizeof(int *));
    
    for (int i = 0; i < N; i++) {
        A[i] = (int *)malloc(N * sizeof(int));
        B[i] = (int *)malloc(N * sizeof(int));
        C[i] = (int *)malloc(N * sizeof(int));
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = 1;  
            B[i][j] = 1;
        }
    }

    double start_time = omp_get_wtime();

    matrixMultiplyParallel(A, B, C, N);

    double end_time = omp_get_wtime();
    double time_taken = end_time - start_time;

    printf("Time taken for parallel matrix multiplication: %f seconds\n", time_taken);

    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
