#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];
sem_t max_philosophers;

void* philosopher_func(void* arg) {
    int id = *(int*)arg;
    while (1) {
        // Wait for permission to start eating
        sem_wait(&max_philosophers);

        // Pick up left fork
        pthread_mutex_lock(&forks[id]);
        printf("Philosopher %d picked up fork %d\n", id, id);

        // Pick up right fork
        int right_fork = (id + 1) % NUM_PHILOSOPHERS;
        pthread_mutex_lock(&forks[right_fork]);
        printf("Philosopher %d picked up fork %d\n", id, right_fork);

        // Eat
        printf("Philosopher %d is eating\n", id);
        sleep(rand() % 2 + 1);  // Sleep for 1-2 seconds

        // Put down right fork
        pthread_mutex_unlock(&forks[right_fork]);
        printf("Philosopher %d put down fork %d\n", id, right_fork);

        // Put down left fork
        pthread_mutex_unlock(&forks[id]);
        printf("Philosopher %d put down fork %d\n", id, id);

        // Release permission to eat
        sem_post(&max_philosophers);

        // Think
        printf("Philosopher %d is thinking\n", id);
        sleep(rand() % 2 + 1);  // Sleep for 1-2 seconds
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    sem_init(&max_philosophers, 0, NUM_PHILOSOPHERS);

    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_args[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_args[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher_func, &philosopher_args[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}