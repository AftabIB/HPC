#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VECTOR_SIZE 1000000
#define PRINT_LIMIT 10 

int main() {
    int i;

    float vector[VECTOR_SIZE];
    float scalar = 5.0;

    clock_t start, end;
    double cpu_time_used;

    for (i = 0; i < VECTOR_SIZE; i++) 
    {
        vector[i] = i * 1.0;
    }

    start = clock();

    for (i = 0; i < VECTOR_SIZE; i++) 
    {
        vector[i] += scalar;
    }

    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Total execution time for sequential scalar addition: %f seconds\n", cpu_time_used);

    printf("First %d elements:\n", PRINT_LIMIT);
    for (i = 0; i < PRINT_LIMIT; i++) 
    {
        printf("vector[%d] = %f\n", i, vector[i]);
    }

    printf("Last %d elements:\n", PRINT_LIMIT);
    for (i = VECTOR_SIZE - PRINT_LIMIT; i < VECTOR_SIZE; i++) 
    {
        printf("vector[%d] = %f\n", i, vector[i]);
    }

    return 0;
}
