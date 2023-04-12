#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int n;           // Number of processes
bool* choosing;  // Boolean array to indicate if process i is choosing
int* numbers;
int counter = 0;
void* thread_func(void* arg) {
    int i = *(int*)arg;
    choosing[i] = true;

    // Find the largest number and increment it by 1
    int max_number = 0;
    for (int j = 0; j < n; j++) {
        if (numbers[j] > max_number) {
            max_number = numbers[j];
        }
    }
    numbers[i] = max_number + 1;
    choosing[i] = false;

    // Check if process i has the smallest number
    for (int j = 0; j < n; j++) {
        if (j != i) {
            while (choosing[j]) {
            }
            while (numbers[j] != 0 && (numbers[j] < numbers[i] || (numbers[j] == numbers[i] && j < i))) {
            }
        }
    }

    // Critical section
    printf("Thread %d is in critical section\n", i);
    // Do some work here

    // Release the number
    numbers[i] = 0;

    return NULL;
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    choosing = (bool*)malloc(n * sizeof(bool));
    numbers = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        choosing[i] = false;
        numbers[i] = 0;
    }

    pthread_t* threads = (pthread_t*)malloc(n * sizeof(pthread_t));
    for (int i = 0; i < n; i++) {
        int* arg = (int*)malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&threads[i], NULL, thread_func, arg);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
