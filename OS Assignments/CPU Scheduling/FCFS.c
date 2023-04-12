#include <stdio.h>
#include <stdlib.h>

struct ProcessInfo {
    char job;
    int at;
    int bt;
    int ft;
    int tat;
    int wat;
};

struct GanttChartInfo {
    char job;
    int start;
    int stop;
};

struct ProcessInfo* fcfs(int* arrivalTime, int* burstTime, int len) {
    struct ProcessInfo* processesInfo = malloc(len * sizeof(struct ProcessInfo));

    for (int i = 0; i < len; i++) {
        processesInfo[i].job = (char)(i + 10 + 'A');
        processesInfo[i].at = arrivalTime[i];
        processesInfo[i].bt = burstTime[i];
    }

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            if (processesInfo[j].at > processesInfo[j + 1].at) {
                struct ProcessInfo temp = processesInfo[j];
                processesInfo[j] = processesInfo[j + 1];
                processesInfo[j + 1] = temp;
            }
        }
    }

    int* finishTime = calloc(len, sizeof(int));
    struct GanttChartInfo* ganttChartInfo = malloc(len * sizeof(struct GanttChartInfo));
    int index = 0;

    for (int i = 0; i < len; i++) {
        if (i == 0 || processesInfo[i].at > finishTime[i - 1]) {
            finishTime[i] = processesInfo[i].at + processesInfo[i].bt;

            ganttChartInfo[index].job = processesInfo[i].job;
            ganttChartInfo[index].start = processesInfo[i].at;
            ganttChartInfo[index].stop = finishTime[i];
            index++;
        } else {
            finishTime[i] = finishTime[i - 1] + processesInfo[i].bt;

            ganttChartInfo[index].job = processesInfo[i].job;
            ganttChartInfo[index].start = finishTime[i - 1];
            ganttChartInfo[index].stop = finishTime[i];
            index++;
        }

        processesInfo[i].ft = finishTime[i];
        processesInfo[i].tat = finishTime[i] - processesInfo[i].at;
        processesInfo[i].wat = finishTime[i] - processesInfo[i].at - processesInfo[i].bt;
    }

    free(finishTime);
    free(ganttChartInfo);

    return processesInfo;
}

int main() {
    int arrivalTime[] = {4, 1, 0, 3, 2};
    int burstTime[] = {2, 1, 8, 4, 5};
    int len = sizeof(arrivalTime) / sizeof(arrivalTime[0]);

    struct ProcessInfo* solvedProcessesInfo = fcfs(arrivalTime, burstTime, len);

    printf("JOB\tAT\tBT\tFT\tTAT\tWT\n");

    for (int i = 0; i < len; i++) {
        printf("%c\t%d\t%d\t%d\t%d\t%d\n", solvedProcessesInfo[i].job, solvedProcessesInfo[i].at,
               solvedProcessesInfo[i].bt, solvedProcessesInfo[i].ft, solvedProcessesInfo[i].tat,
               solvedProcessesInfo[i].wat);
    }

    free(solvedProcessesInfo);

    return 0;
}
