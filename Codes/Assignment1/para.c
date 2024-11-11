#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads;
    double start_time, end_time;

    printf("Enter number of threads: ");
    scanf("%d", &num_threads);

    omp_set_num_threads(num_threads);

    start_time = omp_get_wtime();
    printf("\nParallel execution:\n");
    #pragma omp parallel
    {
        for (volatile int j = 0; j < 1000; ++j); 
        printf("Hello, World from thread %d\n", omp_get_thread_num());
    }
    end_time = omp_get_wtime();
    
    printf("Time taken for parallel execution: %f seconds\n", end_time - start_time);

    return 0;
}
