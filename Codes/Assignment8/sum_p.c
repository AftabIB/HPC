#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2)
    {
        if (rank == 0)
        {
            printf("This program requires exactly 2 processes.\n");
        }
        MPI_Finalize();
        return 1;
    }

    int n = 100000;
    int *A = (int *)malloc(n * sizeof(int));
    int local_sum = 0, total_sum = 0;

    if (rank == 0)
    {
        for (int i = 0; i < n; i++)
        {
            A[i] = i + 1;
        }
    }

    MPI_Bcast(A, n, MPI_INT, 0, MPI_COMM_WORLD);

    double start_time = MPI_Wtime();

    if (rank == 0)
    {
        for (int i = 0; i < n / 2; i++)
        {
            local_sum += A[i];
        }
    }
    else if (rank == 1)
    {
        for (int i = n / 2; i < n; i++)
        {
            local_sum += A[i];
        }
    }

    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();
    double time_taken = end_time - start_time;

    if (rank == 0)
    {
        printf("Total Sum: %d\n", total_sum);
        printf("Time taken (Parallel): %f seconds\n", time_taken);
    }

    free(A);
    MPI_Finalize();
    return 0;
}
