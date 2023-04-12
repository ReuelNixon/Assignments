#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

atomic_int lock = 0;

void* thread_func(void* arg) {
    int id = *(int*)arg;
    while (1) {
        // Acquire lock
        while (atomic_exchange(&lock, 1)) {
        }

        // Critical section
        printf("Thread %d is in the critical section\n", id);
        sleep(rand() % 2 + 1);  // Sleep for 1-2 seconds

        // Release lock
        atomic_store(&lock, 0);
        printf("Thread %d released the lock\n", id);
        sleep(rand() % 2 + 1);  // Sleep for 1-2 seconds
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    pthread_t threads[2];
    int thread_args[2];

    for (int i = 0; i < 2; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &thread_args[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
