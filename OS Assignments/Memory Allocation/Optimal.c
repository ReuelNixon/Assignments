#include <stdio.h>
#include <stdlib.h>

int findFarthestPage(int* frames, int* pages, int n, int m, int startIndex) {
    int farthestIndex = -1;
    int farthestDistance = -1;
    for (int i = 0; i < n; i++) {
        int j = startIndex + 1;
        while (j < m && pages[j] != frames[i]) {
            j++;
        }
        if (j == m) {
            return i;
        } else {
            int distance = j - startIndex;
            if (distance > farthestDistance) {
                farthestDistance = distance;
                farthestIndex = i;
            }
        }
    }
    return farthestIndex;
}

int optimal(int* frames, int* queue, int target, int n, int m, int* pages) {
    int hit = 0;
    for (int i = 0; i < n; i++) {
        if (frames[i] == target) {
            hit = 1;
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
        } else {
            int farthestIndex = findFarthestPage(frames, pages, n, m, queue[0]);
            frames[farthestIndex] = target;
        }
    }

    for (int i = 0; i < n; i++) {
        queue[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int j = 0;
        while (queue[j] != -1) {
            j++;
        }
        queue[j] = frames[i];
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
    int pages[m];
    printf("Enter %d pages: ", m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &pages[i]);
    }
    printf("\n");
    for (int i = 0; i < m; i++) {
        int hit = optimal(frames, queue, pages[i], n, m, pages);
        printf("Page %d: ", pages[i]);
        if (hit)
            printf("\tPage hit\t");
        else
            printf("\tPage miss\t");
        printf("Frames: ");
        for (int i = 0; i < n; i++)
            printf("%d ", frames[i]);
        printf("\n\n");
    }
    return 0;
}