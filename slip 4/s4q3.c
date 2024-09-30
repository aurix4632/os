#include <stdio.h>

#define P 5  // Number of processes
#define R 4  // Number of resource types

void calculateNeed(int need[P][R], int max[P][R], int allocation[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int isSafe(int processes[], int available[], int max[][R], int allocation[][R]) {
    int need[P][R];
    calculateNeed(need, max, allocation);

    int finish[P] = {0};
    int safeSeq[P];
    int work[R];

    for (int i = 0; i < R; i++)
        work[i] = available[i];

    int count = 0;
    while (count < P) {
        int found = 0;
        for (int p = 0; p < P; p++) {
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;
                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += allocation[p][k];

                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0) {
            printf("System is not in a safe state\n");
            return 0;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++)
        printf("%d ", safeSeq[i]);
    printf("\n");
    return 1;
}

void requestResources(int process, int request[], int available[], int allocation[][R], int max[][R]) {
    int need[P][R];
    calculateNeed(need, max, allocation);

    for (int i = 0; i < R; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return;
        }
        if (request[i] > available[i]) {
            printf("Process must wait, resources are not available.\n");
            return;
        }
    }

    for (int i = 0; i < R; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    if (isSafe((int[]){0, 1, 2, 3, 4}, available, max, allocation)) {
        printf("Request can be granted immediately.\n");
    } else {
        printf("Request cannot be granted immediately. Rolling back.\n");
        for (int i = 0; i < R; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
    }
}

int main() {
    int processes[] = {0, 1, 2, 3, 4};

    int allocation[P][R] = {
        {0, 0, 1, 2},
        {1, 0, 0, 0},
        {1, 3, 5, 4},
        {0, 6, 3, 2},
        {0, 0, 1, 4}
    };

    int max[P][R] = {
        {2, 0, 1, 2},
        {1, 7, 5, 0},
        {2, 3, 5, 6},
        {0, 6, 5, 2},
        {0, 6, 5, 6}
    };

    int available[R] = {1, 5, 2, 0};

    isSafe(processes, available, max, allocation);

    int request[] = {0, 4, 2, 0};
    requestResources(1, request, available, allocation, max);

    return 0;
}
