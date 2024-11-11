#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include<time.h>

#define N 100000

void sort_ascending(int *vec, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (vec[i] > vec[j]) {
                int temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            }
        }
    }
}

void sort_descending(int *vec, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (vec[i] < vec[j]) {
                int temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            }
        }
    }
}


long long int minimum_scalar_product(int *vec1, int *vec2, int size) {
    sort_ascending(vec1, size);

    sort_descending(vec2, size);

    long long int result = 0;
    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < size; i++) {
        result += (long long int)vec1[i] * vec2[i];
    }

    return result;
}

int main() {
    int vec1[N], vec2[N];
    int num_threads;
    
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);
    
    omp_set_num_threads(num_threads);

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        vec1[i] = rand() % 100;
        vec2[i] = rand() % 100;
    }

    double start = omp_get_wtime();
    
    long long int min_scalar_product = minimum_scalar_product(vec1, vec2, N);

    double end = omp_get_wtime();
    double time_taken = end - start;

    printf("Parallel minimum scalar product with %d threads: %lld\n", num_threads, min_scalar_product);
    printf("Parallel execution time: %f seconds\n", time_taken);

    return 0;
}
