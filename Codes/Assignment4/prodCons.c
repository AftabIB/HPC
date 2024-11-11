#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int full = 0;
int empty = 10, x = 0;
omp_lock_t lock;

void producer() {
    omp_set_lock(&lock);
    if (empty > 0) {
        full++;
        empty--;
        x++;
        printf("\nProducer produces item %d\n", x);
    } else {
        printf("\nBuffer is full!\n");
    }
    omp_unset_lock(&lock);
}

void consumer() {
    omp_set_lock(&lock);
    if (full > 0) {
        full--;
        empty++;
        printf("\nConsumer consumes item %d\n", x);
        x--;
    } else {
        printf("\nBuffer is empty!\n");
    }
    omp_unset_lock(&lock);
}

int main() {
    int n;

    omp_init_lock(&lock);

    while (1) {
        printf(
            "\n1. Press 1 for Producer"
            "\n2. Press 2 for Consumer"
            "\n3. Press 3 for Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &n);

        switch (n) {
            case 1:
                #pragma omp task
                {
                    producer();
                }
                break;

            case 2:
                #pragma omp task
                {
                    consumer();
                }
                break;

            case 3:
                omp_destroy_lock(&lock);
                exit(0);

            default:
                printf("\nInvalid choice! Please try again.");
                break;
        }
    }

    return 0;
}
