#include <stdio.h>

int main() 
{
    int num_processes, num_resources;

    // Accept the number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    int max[num_processes][num_resources];
    int allocation[num_processes][num_resources];
    int need[num_processes][num_resources];

    // Accept the Max matrix
    printf("Enter the Max matrix (%d x %d):\n", num_processes, num_resources);
    for (int i = 0; i < num_processes; i++) 
    {
        for (int j = 0; j < num_resources; j++) 
        {
            scanf("%d", &max[i][j]);
        }
    }

    // Accept the Allocation matrix
    printf("Enter the Allocation matrix (%d x %d):\n", num_processes, num_resources);
    
    for (int i = 0; i < num_processes; i++) 
    {
        for (int j = 0; j < num_resources; j++) 
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Calculate the Need matrix
    for (int i = 0; i < num_processes; i++) 
    {
        for (int j = 0; j < num_resources; j++) 
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Display the Need matrix
    printf("The Need matrix is:\n");
    for (int i = 0; i < num_processes; i++) 
    {
        for (int j = 0; j < num_resources; j++) 
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    return 0;
}
