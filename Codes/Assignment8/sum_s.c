#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n = 100000;  
    int *A = (int*) malloc(n * sizeof(int));  
    int local_sum1 = 0, local_sum2 = 0, total_sum = 0;

    for (int i = 0; i < n; i++) {
        A[i] = i + 1; 
    }

    clock_t start = clock();

    for (int i = 0; i < n / 2; i++) {
        local_sum1 += A[i];
    }

    for (int i = n / 2; i < n; i++) {
        local_sum2 += A[i];
    }

    total_sum = local_sum1 + local_sum2;

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Total Sum: %d\n", total_sum);
    printf("Time taken (Sequential): %f seconds\n", time_taken);

    free(A);

    return 0;
}
