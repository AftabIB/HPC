#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000

long long int minimum_scalar_product(int *vec1, int *vec2, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (vec1[i] > vec1[j]) {
                int temp = vec1[i];
                vec1[i] = vec1[j];
                vec1[j] = temp;
            }
        }
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (vec2[i] < vec2[j]) {
                int temp = vec2[i];
                vec2[i] = vec2[j];
                vec2[j] = temp;
            }
        }
    }

    long long int result = 0;
    for (int i = 0; i < size; i++) {
        result += (long long int)vec1[i] * vec2[i];
    }

    return result;
}

int main() {
    int vec1[N], vec2[N];
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        vec1[i] = rand() % 100;
        vec2[i] = rand() % 100;
    }

    clock_t start = clock();
    
    long long int min_scalar_product = minimum_scalar_product(vec1, vec2, N);

    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Sequential minimum scalar product: %lld\n", min_scalar_product);
    printf("Sequential execution time: %f seconds\n", time_taken);

    return 0;
}
