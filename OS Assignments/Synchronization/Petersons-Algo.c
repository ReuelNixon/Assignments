#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 2

int turn = 0;
int flag[NUM_THREADS] = {0};

void* thread_func(void* arg) {
    int id = *(int*)arg;
    int other = (id + 1) % NUM_THREADS;
    for (int i = 0; i < 5; i++) {
        flag[id] = 1;
        turn = other;
        while (flag[other] && turn == other)
            ;
        printf("Thread %d entered critical section\n", id);
        // Critical section
        printf("Thread %d exited critical section\n", id);
        flag[id] = 0;
        // Remainder section
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}