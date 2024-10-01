#include <stdio.h>

int main() {
    int processes, max_resources, available, i, j;
    
    // Input the number of processes and maximum resources
    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter the number of resource instances: ");
    scanf("%d", &max_resources);
    
    int max[processes], allocated[processes];
    
    // Input maximum and allocated resources for each process
    printf("Enter the maximum resources required by each process:\n");
    for (i = 0; i < processes; i++) {
        printf("Process %d: ", i);
        scanf("%d", &max[i]);
    }
    
    printf("Enter the currently allocated resources for each process:\n");
    for (i = 0; i < processes; i++) {
        printf("Process %d: ", i);
        scanf("%d", &allocated[i]);
    }
    
    // Calculate the minimum number of resources needed to avoid deadlock
    int total_max = 0, total_allocated = 0;
    for (i = 0; i < processes; i++) {
        total_max += max[i];
        total_allocated += allocated[i];
    }
    
    int min_resources_needed = total_max - total_allocated;
    printf("Minimum additional resources needed to avoid deadlock: %d\n", min_resources_needed);
    
    return 0;
}



