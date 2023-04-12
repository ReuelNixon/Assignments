#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define N_THREADS 3

int counter = 0;

#define N 3
int turn;
bool flag[N];

void enter_region(int process_num) {
    int other = 1 - process_num;  // the other process
    printf("Entered \n");
    // Set my flag and give turn to the other process
    flag[process_num] = true;
    turn = process_num;

    // Wait until the other process is not in its critical section and it's my turn
    while (flag[other] && turn == process_num)
        ;
}

void leave_region(int process_num) {
    flag[process_num] = false;
    printf("exited\n");
}

void *thread(void *arg) {
    int i;
    int id = *(int *)arg;
    for (i = 0; i < 5; i++) {
        enter_region(id);
        counter++;
        leave_region(id);
    }
    return NULL;
}

int main(int argc, char **argv) {
    pthread_t threads[N_THREADS];
    int thread_ids[N_THREADS];
    int i, rc;

    // Create threads
    for (i = 0; i < N_THREADS; i++) {
        thread_ids[i] = i;
        rc = pthread_create(&threads[i], NULL, thread, (void *)&thread_ids[i]);
    }

    // Join threads
    for (i = 0; i < N_THREADS; i++) {
        rc = pthread_join(threads[i], NULL);
    }

    printf("Counter value: %d\n", counter);

    return 0;
}
