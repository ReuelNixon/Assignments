#include <stdbool.h>
#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int processes, resources;
int available[MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

void calculate_need() {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    printf("Need matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

bool is_safe() {
    int work[MAX_RESOURCES];
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    bool finish[MAX_PROCESSES];
    for (int i = 0; i < processes; i++) {
        finish[i] = false;
    }

    int safe_sequence[MAX_PROCESSES];
    int count = 0;
    while (count < processes) {
        bool found = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    safe_sequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("The system is not in a safe state\n");
            return false;
        }
    }

    printf("The system is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < processes; i++) {
        printf("%d ", safe_sequence[i]);
    }
    printf("\n");

    return true;
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the max matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the available matrix:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    is_safe();
    calculate_need();

    return 0;
}
