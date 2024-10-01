#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() 
{
    pid_t pid;
    // Fork a child process
    pid = fork();

    if (pid < 0) 
    {  // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) 
    {  // Child process
        printf("Child process (PID: %d) is executing 'ls' command using execl().\n", getpid());

        // Execute the "ls" command
        execl("/bin/ls", "ls", "-l", (char *)NULL);

        // If execl() fails
        perror("execl() failed");
        exit(EXIT_FAILURE);
    } 
    else {  // Parent process
        printf("Parent process (PID: %d) is going to sleep.\n", getpid());

        // Parent process goes to sleep
        sleep(5);

        // Wait for the child process to complete
        wait(NULL);

        printf("Parent process (PID: %d) has woken up and child process completed.\n", getpid());
    }
    return 0;
}
