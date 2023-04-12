#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int count = 0;

sem_t mutex;
sem_t empty;
sem_t full;

void* producer_func(void* arg) {
    int id = *(int*)arg;
    while (1) {
        int item = rand() % 100;
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = item;
        printf("Producer %d produced item %d at position %d\n", id, item, in);
        in = (in + 1) % BUFFER_SIZE;
        count++;
        sem_post(&mutex);
        sem_post(&full);
        sleep(rand() % 2 + 1);  // Sleep for 1-2 seconds
    }
    return NULL;
}

void* consumer_func(void* arg) {
    int id = *(int*)arg;
    while (1) {
        sem_wait(&full);
        sem_wait(&mutex);
        int item = buffer[out];
        printf("Consumer %d consumed item %d from position %d\n", id, item, out);
        out = (out + 1) % BUFFER_SIZE;
        count--;
        sem_post(&mutex);
        sem_post(&empty);
        sleep(rand() % 2 + 1);  // Sleep for 1-2 seconds
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];
    int producer_args[NUM_PRODUCERS];
    int consumer_args[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        producer_args[i] = i;
        pthread_create(&producers[i], NULL, producer_func, &producer_args[i]);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        consumer_args[i] = i;
        pthread_create(&consumers[i], NULL, consumer_func, &consumer_args[i]);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    return 0;
}
