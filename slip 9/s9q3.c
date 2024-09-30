#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int id, arrival, burst, remaining, waiting, turnaround;
} Process;

typedef struct {
    int processId, startTime, endTime;
} GanttChart;

int main() {
    int n, quantum, time = 0, completed = 0;
    Process p[MAX];
    GanttChart gantt[MAX];
    int ganttIndex = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time and CPU burst for P%d: ", p[i].id);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst;
        p[i].waiting = 0;
        p[i].turnaround = 0;
    }

    printf("\nGantt Chart:\n");

    while (completed < n) {
        bool idle = true;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0 && p[i].arrival <= time) {
                idle = false;
                int execTime = (p[i].remaining > quantum) ? quantum : p[i].remaining;
                p[i].remaining -= execTime;
                
                gantt[ganttIndex].processId = p[i].id;
                gantt[ganttIndex].startTime = time;
                gantt[ganttIndex].endTime = time + execTime;
                ganttIndex++;

                time += execTime;

                if (p[i].remaining == 0) {
                    p[i].turnaround = time - p[i].arrival;
                    p[i].waiting = p[i].turnaround - p[i].burst;
                    completed++;
                }
            }
        }
        if (idle) time++;  // Handle idle time
    }

    // Print the Gantt chart
    for (int i = 0; i < ganttIndex; i++) {
        printf("| P%d (%d-%d) ", gantt[i].processId, gantt[i].startTime, gantt[i].endTime);
    }
    printf("|\n\n");

    // Process results
    printf("Process\tArrival\tBurst\tWaiting\tTurnaround\n");

    float totalWait = 0, totalTurnaround = 0;
    for (int i = 0; i < n; i++) {
        totalWait += p[i].waiting;
        totalTurnaround += p[i].turnaround;
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
    }

    printf("\nAverage waiting time: %.2f\n", totalWait / n);
    printf("Average turnaround time: %.2f\n", totalTurnaround / n);

    return 0;
}
