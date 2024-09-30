#include <stdio.h>
#include <stdbool.h>

#define P 5  
#define R 3  

void display(int arr[P][R], const char* name);
void calculateNeed(int need[P][R], int max[P][R], int allot[P][R]);
bool isSafe(int processes[], int n, int avail[], int max[][R], int allot[][R]);

int main() {
    int i, j;
    int available[R] = {7, 2, 6};
    int allocation[P][R], max[P][R], need[P][R];
    int processes[] = {0, 1, 2, 3, 4};

    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Display Allocation Matrix\n");
        printf("2. Display Max Matrix\n");
        printf("3. Calculate and Display Need Matrix\n");
        printf("4. Display Available Resources\n");
        printf("5. Check for Deadlock\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Allocation Matrix:\n");
                for (i = 0; i < P; i++) {
                    for (j = 0; j < R; j++) {
                        scanf("%d", &allocation[i][j]);
                    }
                }
                display(allocation, "Allocation");
                break;

            case 2:
                printf("Enter Max Matrix:\n");
                for (i = 0; i < P; i++) {
                    for (j = 0; j < R; j++) {
                        scanf("%d", &max[i][j]);
                    }
                }
                display(max, "Max");
                break;

            case 3:
                calculateNeed(need, max, allocation);
                display(need, "Need");
                break;

            case 4:
                printf("Available Resources:\n");
                for (i = 0; i < R; i++) {
                    printf("%d ", available[i]);
                }
                printf("\n");
                break;

            case 5:
                if (isSafe(processes, P, available, max, allocation)) {
                    printf("No Deadlock\n");
                } else {
                    printf("System is in Deadlock\n");
                }
                break;

            case 6:
                return 0;

            default:
                printf("Invalid choice, try again.\n");
        }
    }
}

void display(int arr[P][R], const char* name) {
    printf("%s Matrix:\n", name);
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void calculateNeed(int need[P][R], int max[P][R], int allot[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}

bool isSafe(int processes[], int n, int avail[], int max[][R], int allot[][R]) {
    int work[R];
    bool finish[n];
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }
    for (int i = 0; i < n; i++) {
        finish[i] = false;
    }
    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int k;
                for (k = 0; k < R; k++) {
                    if (max[i][k] - allot[i][k] > work[k])
                        break;
                }
                if (k == R) {
                    for (int l = 0; l < R; l++) {
                        work[l] += allot[i][l];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}
