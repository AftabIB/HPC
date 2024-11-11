#include <stdio.h>
#include <time.h>

int main() {
    int num_threads;
    clock_t start_time, end_time;

    printf("Enter number of iterations: ");
    scanf("%d", &num_threads);

    start_time = clock();
    printf("Sequential execution:\n");
    for (int i = 0; i < num_threads; ++i) {
        for (volatile int j = 0; j < 1000; ++j); 
        printf("Hello, World from thread %d\n", i);
    }
    end_time = clock();
    
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Time taken for sequential execution: %f seconds\n", time_taken);

    return 0;
}
