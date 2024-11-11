#include <stdio.h>
#include <omp.h>

unsigned long long fibonacci(int n) {
    if (n <= 1) return n;

    unsigned long long fib1, fib2;

    if (n > 5) 
    {
        #pragma omp task shared(fib1)
        fib1 = fibonacci(n - 1);

        #pragma omp task shared(fib2)
        fib2 = fibonacci(n - 2);

        #pragma omp taskwait
    } 
    else 
    {
        fib1 = fibonacci(n - 1);
        fib2 = fibonacci(n - 2);
    }

    return fib1 + fib2;
}

int main() {
    int n, num_threads;
    unsigned long long result;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    printf("Enter the number of threads : ");
    scanf("%d", &num_threads);

    omp_set_num_threads(num_threads);

    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fibonacci(n);
        }
    }

    double end_time = omp_get_wtime();

    printf("Fibonacci(%d) = %llu\n", n, result);
    printf("Total time taken: %f seconds\n", end_time - start_time);

    return 0;
}
