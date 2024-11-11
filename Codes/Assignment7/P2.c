#include "mpi.h"
#include <stdio.h>

int main(int argc, char** argv) {
    int world_rank, world_size;
    MPI_Group world_group;
    MPI_Comm world_comm = MPI_COMM_WORLD;
    double start_time, end_time;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(world_comm, &world_size);

    MPI_Comm_rank(world_comm, &world_rank);

    if (world_size != 5) {
        if (world_rank == 0) {
            printf("Please run with 5 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    MPI_Comm_group(world_comm, &world_group);

    start_time = MPI_Wtime();

    printf("Process %d is part of communicator group.\n", world_rank);

    end_time = MPI_Wtime();

    printf("Process %d execution time: %f seconds\n\n", world_rank, end_time - start_time);

    MPI_Group_free(&world_group);
    MPI_Finalize();

    return 0;
}
