#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void matrix_vector_mult_parallel(int local_rows, int m, int matrix[][m], int vector[], int local_result[]) {
    for (int i = 0; i < local_rows; i++) {
        local_result[i] = 0;
        for (int j = 0; j < m; j++) {
            local_result[i] += matrix[i][j] * vector[j];
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n, m;
    int *matrix = NULL, *vector = NULL, *result = NULL;
    int *local_matrix = NULL, *local_result = NULL;

    if (rank == 0) {
        printf("Enter the number of rows and columns for the matrix: ");
        scanf("%d %d", &n, &m);

        // Allocate memory for matrix and vectors
        matrix = (int *)malloc(n * m * sizeof(int));
        vector = (int *)malloc(m * sizeof(int));
        result = (int *)malloc(n * sizeof(int));

        // Initialize matrix and vector with random values
        srand(time(0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                matrix[i * m + j] = rand() % 10;
            }
        }
        for (int i = 0; i < m; i++) {
            vector[i] = rand() % 10;
        }
    }

    // Broadcast the number of columns
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Broadcast the vector to all processes
    if (rank != 0) {
        vector = (int *)malloc(m * sizeof(int));
    }
    MPI_Bcast(vector, m, MPI_INT, 0, MPI_COMM_WORLD);

    // Determine the local number of rows each process will handle
    int local_rows = n / size;
    if (rank == 0) {
        // Allocate local matrix for each process
        local_matrix = (int *)malloc(local_rows * m * sizeof(int));
        local_result = (int *)malloc(local_rows * sizeof(int));
    }

    // Scatter the rows of the matrix to all processes
    MPI_Scatter(matrix, local_rows * m, MPI_INT, local_matrix, local_rows * m, MPI_INT, 0, MPI_COMM_WORLD);

    // Start measuring parallel execution time
    double start_time = MPI_Wtime();

    // Perform matrix-vector multiplication in parallel
    matrix_vector_mult_parallel(local_rows, m, local_matrix, vector, local_result);

    // Gather the local results from each process
    MPI_Gather(local_result, local_rows, MPI_INT, result, local_rows, MPI_INT, 0, MPI_COMM_WORLD);

    // End measuring parallel execution time
    double end_time = MPI_Wtime();

    if (rank == 0) {
        printf("Parallel Execution Time: %f seconds\n", end_time - start_time);

        // Output result
        printf("Resultant vector: \n");
        for (int i = 0; i < n; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");

        // Free allocated memory
        free(matrix);
        free(result);
    }

    free(local_matrix);
    free(local_result);
    free(vector);

    MPI_Finalize();
    return 0;
}
