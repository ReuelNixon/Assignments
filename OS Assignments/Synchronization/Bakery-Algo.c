// #include <pthread.h>
// #include <stdatomic.h>
// #include <stdio.h>

// #define NUM_THREADS 2

// atomic_int ticket[NUM_THREADS];
// atomic_int choosing[NUM_THREADS];
// int counter = 0;

// void* thread_func(void* arg) {
//     int id = *(int*)arg;
//     for (int i = 0; i < 5; i++) {
//         choosing[id] = 1;
//         int max_ticket = 0;
//         for (int j = 0; j < NUM_THREADS; j++) {
//             int t = ticket[j];
//             max_ticket = (t > max_ticket) ? t : max_ticket;
//         }
//         ticket[id] = max_ticket + 1;
//         choosing[id] = 0;
//         for (int j = 0; j < NUM_THREADS; j++) {
//             if (j != id) {
//                 while (choosing[j]) {
//                     // Wait until thread j chooses its number
//                 }
//                 while (ticket[j] != 0 && (ticket[j] < ticket[id] || (ticket[j] == ticket[id] && j < id))) {
//                     // Wait until thread j gets its turn or exits choosing phase
//                 }
//             }
//         }
//         printf("Thread %d entered critical section (counter = %d)\n", id, ++counter);
//         // Critical section
//         printf("Thread %d exited critical section\n", id);
//         ticket[id] = 0;
//         // Remainder section
//     }
//     return NULL;
// }

// int main() {
//     pthread_t threads[NUM_THREADS];
//     int thread_args[NUM_THREADS];

//     for (int i = 0; i < NUM_THREADS; i++) {
//         thread_args[i] = i;
//         pthread_create(&threads[i], NULL, thread_func, &thread_args[i]);
//     }

//     for (int i = 0; i < NUM_THREADS; i++) {
//         pthread_join(threads[i], NULL);
//     }

//     return 0;
// }
#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 2

int ticket[NUM_THREADS];
int choosing[NUM_THREADS];
int counter = 0;

void* thread_func(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < 5; i++) {
        choosing[id] = 1;
        int max_ticket = 0;
        for (int j = 0; j < NUM_THREADS; j++) {
            int t = ticket[j];
            if (t > max_ticket) {
                max_ticket = t;
            }
        }
        ticket[id] = max_ticket + 1;
        choosing[id] = 0;
        for (int j = 0; j < NUM_THREADS; j++) {
            if (j != id) {
                while (choosing[j]) {
                    // Wait until thread j chooses its number
                }
                while (ticket[j] != 0 && (ticket[j] < ticket[id] || (ticket[j] == ticket[id] && j < id))) {
                    // Wait until thread j gets its turn or exits choosing phase
                }
            }
        }
        printf("Thread %d entered critical section (counter = %d)\n", id, ++counter);
        // Critical section
        printf("Thread %d exited critical section\n", id);
        ticket[id] = 0;
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
