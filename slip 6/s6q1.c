#include <stdio.h>
#include <time.h>

int main() {
    int i;
    // Record the start time
    clock_t start_time = clock();
    
    // A simple loop running from 1 to 999,999
    for (i = 1; i < 1000000; i++) {
        // Loop body (currently empty)
    }
    
    // Record the end time
    clock_t end_time = clock();
    
    // Calculate the execution time in seconds
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    
    // Print the execution time
    printf("Execution time: %f seconds\n", execution_time);
    
    return 0;
}
