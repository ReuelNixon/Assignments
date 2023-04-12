#include <stdio.h>
#include <stdlib.h>

void enqueue(int* arr, int target, int n) {
    for (int i = 0; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[n - 1] = target;
}

int front(int* arr) {
    return arr[0];
}

int LRU(int* frames, int target, int n, int* queue) {
    int hit = 0;
    for (int i = 0; i < n; i++) {
        if (frames[i] == target) {
            hit = 1;
            int ind = 0;
            while (queue[ind] != i)
                ind++;
            for (int j = ind; j < n - 1; j++) {
                queue[j] = queue[j + 1];
            }
            queue[n - 1] = i;
            break;
        }
    }

    if (!hit) {
        int i = 0;
        while (frames[i] != 0) {
            i++;
        }
        if (i != n) {
            frames[i] = target;
            enqueue(queue, i, n);
        } else {
            int j = front(queue);
            frames[j] = target;
            enqueue(queue, j, n);
        }
    }

    return hit;
}

int main() {
    int n;
    printf("Enter number of frames: ");
    scanf("%d", &n);
    int frames[n];
    int queue[n];
    for (int i = 0; i < n; i++) {
        frames[i] = 0;
        queue[i] = -1;
    }
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
        int hit = LRU(frames, target, n, queue);
        if (hit)
            printf("Page Hit\t");
        else
            printf("Page Miss\t");
        printf("Frames: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", frames[i]);
        }
        printf("\tQueue: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", queue[i]);
        }
        printf("\n\n");
    }

    return 0;
}