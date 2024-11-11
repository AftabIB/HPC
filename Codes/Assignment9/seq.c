#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void matrix_vector_mult(int n, int m, int matrix[n][m], int vector[m], int result[n]) {
    for (int i = 0; i < n; i++) {
        result[i] = 0;
        for (int j = 0; j < m; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

int main() {
    int n, m;
    
    printf("Enter the number of rows and columns for the matrix: ");
    scanf("%d %d", &n, &m);

    int matrix[n][m], vector[m], result[n];

    // Initialize matrix and vector with random values
    srand(time(0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
    for (int i = 0; i < m; i++) {
        vector[i] = rand() % 10;
    }

    // Measure time for sequential execution
    clock_t start = clock();
    matrix_vector_mult(n, m, matrix, vector, result);
    clock_t end = clock();

    printf("Sequential Execution Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Output result
    printf("Resultant vector: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}
