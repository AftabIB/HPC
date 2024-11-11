#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000

double min_scalar_product_sequential(int *vec1, int *vec2, int size) {
    double result = 0;
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

    clock_t start, end;
    start = clock();
    double result = min_scalar_product_sequential(vec1, vec2, N);
    end = clock();
    
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Sequential minimum scalar product: %.2f\n", result);
    printf("Time taken by sequential computation: %.6f seconds\n", time_taken);

    free(vec1);
    free(vec2);
    return 0;
}
