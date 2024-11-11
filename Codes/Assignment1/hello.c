#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        printf("Hello, OpenMP from thread %d \n", omp_get_thread_num());
    }
    return 0;
}
