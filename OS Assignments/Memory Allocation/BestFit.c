#include <stdio.h>
#include <stdlib.h>

void insertBestFit(int* arr, int n, int target, int* newMemory) {
    int i = 0, min = 999999, minIndex = -1;
    while (i < n) {
        if (arr[i] >= target && arr[i] < min && newMemory[i] == 0) {
            min = arr[i];
            minIndex = i;
        }
        i++;
    }
    if (minIndex != -1)
        newMemory[minIndex] = target;
    return;
}

int main() {
    int n;
    printf("Enter number of blocks: ");
    scanf("%d", &n);
    int sizes[n];
    int processes[n];

    printf("Enter size of blocks\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &sizes[i]);

    printf("\nEnter memory required by %d processes\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &processes[i]);

    int newMemory[n];
    for (int i = 0; i < n; i++) newMemory[i] = 0;

    printf("\nMemory blocks before allocating:\n");
    for (int i = 0; i < n; i++)
        printf(" %d ", sizes[i]);

    for (int i = 0; i < n; i++) {
        insertBestFit(sizes, n, processes[i], newMemory);
    }

    printf("\nMemory blocks after allocating:\n");
    for (int i = 0; i < n; i++) {
        if (newMemory[i] != 0) {
            printf(" %d ", newMemory[i]);
        } else {
            printf(" - ");
        }
    }
}

// 100 500 200 450 400
// 212 417 112 426 532