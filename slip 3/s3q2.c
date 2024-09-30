#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int arrival_time;
    int first_cpu_burst;
    int next_cpu_burst;
    int turnaround_time;
    int waiting_time;
} Job;

void calculateAverages(Job jobs[], int n, float *avg_turnaround, float *avg_waiting) {
    int total_turnaround = 0;
    int total_waiting = 0;

    for (int i = 0; i < n; i++) {
        total_turnaround += jobs[i].turnaround_time;
        total_waiting += jobs[i].waiting_time;
    }

    *avg_turnaround = (float)total_turnaround / n;
    *avg_waiting = (float)total_waiting / n;
}

int main() {
    int n;
    srand(time(NULL));

    printf("Enter the number of jobs: ");
    scanf("%d", &n);

    Job jobs[n];

    for (int i = 0; i < n; i++) {
        printf("Job %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &jobs[i].arrival_time);
        printf("First CPU Burst Time: ");
        scanf("%d", &jobs[i].first_cpu_burst);

        jobs[i].next_cpu_burst = 0;
        jobs[i].turnaround_time = 0;
        jobs[i].waiting_time = 0;
    }

    int current_time = 0;

    printf("\nGantt Chart:\n");
    printf("0");

    for (int i = 0; i < n; i++) {
        if (current_time < jobs[i].arrival_time) {
            current_time = jobs[i].arrival_time;
        }

        jobs[i].next_cpu_burst = rand() % 10 + 1;

        jobs[i].turnaround_time = current_time + jobs[i].first_cpu_burst + jobs[i].next_cpu_burst - jobs[i].arrival_time;
        jobs[i].waiting_time = jobs[i].turnaround_time - jobs[i].first_cpu_burst - jobs[i].next_cpu_burst;

        current_time += jobs[i].first_cpu_burst + jobs[i].next_cpu_burst;
        printf(" -> Job %d -> %d", i + 1, current_time);
    }

    printf("\n");

    printf("\nTurnaround Time and Waiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("Job %d - Turnaround Time: %d, Waiting Time: %d\n", i + 1, jobs[i].turnaround_time, jobs[i].waiting_time);
    }

    float avg_turnaround, avg_waiting;
    calculateAverages(jobs, n, &avg_turnaround, &avg_waiting);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround);
    printf("Average Waiting Time: %.2f\n", avg_waiting);

    return 0;
}
