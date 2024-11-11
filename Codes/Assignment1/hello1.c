#include <stdio.h>
#include <omp.h>

int main(void) {
    int num_threads;

    printf("Enter number of threads: ");
    scanf("%d", &num_threads);

    omp_set_num_threads(num_threads);

    #pragma omp parallel
    {
        printf("Hello, world from thread %d.\n", omp_get_thread_num());
    }

    return 0;
}
