#include <stdio.h>
#include <time.h>

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    clock_t start = clock();
    
    int result = fibonacci(n);
    
    clock_t end = clock();
    
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("Fibonacci(%d) = %d\n", n, result);
    printf("Time taken to compute Fibonacci(%d): %.6f seconds\n", n, time_taken);
    
    return 0;
}
