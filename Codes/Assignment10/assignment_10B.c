#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: reduce message_size1 message_size2 ... message_sizeN\n");
        return 1;
    }

    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int num_sizes = argc - 1; 
    int *sizes = malloc(num_sizes * sizeof(int));  
    char *input_buffer = NULL;
    char *output_buffer = NULL;

    for (int i = 0; i < num_sizes; i++) {
        sizes[i] = atoi(argv[i + 1]);
    }

    for (int j = 0; j < num_sizes; j++) {
        int size = sizes[j];

        input_buffer = malloc(size * sizeof(char));
        output_buffer = malloc(size * sizeof(char));

        srand(time(NULL) + rank);
        for (int i = 0; i < size; i++) {
            input_buffer[i] = rand() % 256;
        }

        double total_time = 0.0;

        for (int i = 0; i < 100; i++) {
            MPI_Barrier(MPI_COMM_WORLD);
            double start_time = MPI_Wtime();

            MPI_Reduce(input_buffer, output_buffer, size, MPI_BYTE, MPI_BOR, 0, MPI_COMM_WORLD);
            MPI_Barrier(MPI_COMM_WORLD);
            total_time += (MPI_Wtime() - start_time);
        }

        if (rank == 0) {
            printf("Average time for reduce with message size %d: %f secs\n", size, total_time / 100);
        }

        free(input_buffer);
        free(output_buffer);
    }

    free(sizes);
    MPI_Finalize();
    return 0;
}
