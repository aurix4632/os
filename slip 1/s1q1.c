#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
        exit(1);
    }

    if (pid == 0) // Child process
    {
        printf("\nI am the child process, id=%d", getpid());
        int priority = nice(-7); // Attempt to set a higher priority
        if (priority == -1) {
            perror("Unable to set priority");
        } else {
            printf("\nChild Process Priority: %d\n", priority);
        }
    }
    else // Parent process
    {
        printf("\nI am the parent process, id=%d\n", getpid());
        int priority = nice(15); // Set a lower priority
        if (priority == -1) {
            perror("Unable to set priority");
        } else {
            printf("\nParent Process Priority: %d\n", priority);
        }
    }
    return 0;
}
