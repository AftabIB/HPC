#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 1000000 

double min_scalar_product_parallel(int *vec1, int *vec2, int size, int num_threads) {
    double result = 0.0;
    
    omp_set_num_threads(num_threads);

    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < size; i++) {
        result += (double)(vec1[i] * vec2[i]);
    }

    return result;
}

int main() {
    int *vec1 = (int *)malloc(N * sizeof(int));
    int *vec2 = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        vec1[i] = rand() % 100;
        vec2[i] = rand() % 100;
    }

    int num_threads;
    printf("Enter the number of threads (cores) to use: ");
    scanf("%d", &num_threads);

    double start_time, end_time;

    start_time = omp_get_wtime();
    double result_parallel = min_scalar_product_parallel(vec1, vec2, N, num_threads);
    end_time = omp_get_wtime();
    
    printf("Parallel minimum scalar product: %.2f\n", result_parallel);
    printf("Time taken by parallel computation with %d threads: %.6f seconds\n", num_threads, end_time - start_time);

    free(vec1);
    free(vec2);
    return 0;
}
