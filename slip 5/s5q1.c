#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main() 
{
    pid_t pid;

    // Fork a child process
    pid = fork();

    if (pid < 0) 
    {  
        // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) 
    {  
        // Child process
        printf("Child process (PID: %d) before changing priority\n", getpid());

        // Set a higher priority (decrease the nice value)
        int new_nice_value = nice(-5);  // Decrease nice value by 5
        
        if (new_nice_value == -1 && errno != 0) 
        {
            perror("Nice failed");
            exit(EXIT_FAILURE);
        }

        printf("Child process (PID: %d) after changing priority. New nice value: %d\n", getpid(), new_nice_value);

        // Simulate some work
        for (int i = 0; i < 5; i++) 
        {
            printf("Child process (PID: %d) is working...\n", getpid());
            sleep(1);
        }

        exit(EXIT_SUCCESS);
    } 
    else 
    {  
        // Parent process
        printf("Parent process (PID: %d)\n", getpid());

        // Wait for the child process to complete
        wait(NULL);
        printf("Parent process (PID: %d) after child has completed.\n", getpid());
    }

    return 0;
}
