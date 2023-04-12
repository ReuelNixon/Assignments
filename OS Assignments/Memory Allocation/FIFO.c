#include <stdio.h>
#include <stdlib.h>

void enqueue(int* arr, int target, int n) {
    for (int i = 0; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[n - 1] = target;
}

int FIFO(int* frames, int target, int n) {
    int hit = 0;
    for (int i = 0; i < n; i++) {
        if (frames[i] == target) {
            hit = 1;
            break;
        }
    }

    if (!hit) {
        int i = 0;
        while (frames[i] != 0) i++;
        if (i != n)
            frames[i] = target;
        else
            enqueue(frames, target, n);
    }
    return hit;
}

int main() {
    int n;
    printf("Enter number of frames: ");
    scanf("%d", &n);
    int frames[n];
    for (int i = 0; i < n; i++)
        frames[i] = 0;
    printf("Initial frames: ");
    for (int i = 0; i < n; i++)
        printf("%d ", frames[i]);

    int target;
    int m;
    printf("\nEnter number of pages: ");
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        printf("Enter page %d: ", i + 1);
        scanf("%d", &target);
        int hit = FIFO(frames, target, n);
        if (hit)
            printf("Page Hit\t");
        else
            printf("Page Miss\t");

        printf("Frames: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", frames[i]);
        }
        printf("\n\n");
    }
    return 0;
}