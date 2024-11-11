#include "mpi.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv) {
    int world_rank, world_size;
    double start_time, end_time, process_start_time, process_end_time;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_size != 10) {
        if (world_rank == 0) {
            printf("Please run with 10 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (world_rank == 0) {
        start_time = MPI_Wtime();
    }

    process_start_time = MPI_Wtime();

    printf("Hello World from process %d\n", world_rank);

    process_end_time = MPI_Wtime();
    printf("Process %d execution time: %f seconds\n\n", world_rank, process_end_time - process_start_time);

    MPI_Finalize();

    return 0;
}
