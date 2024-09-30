#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() 
{
    pid_t pid = fork();

    if (pid < 0) 
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) 
    {
        printf("Child process (PID: %d) is executing 'ls' command using execl().\n", getpid());
        execl("/bin/ls", "ls", "-l", (char *)NULL);
        perror("execl() failed");
        exit(EXIT_FAILURE);
    } 
    else 
    {
        printf("Parent process (PID: %d) is going to sleep.\n", getpid());
        sleep(5);
        wait(NULL);
        printf("Parent process (PID: %d) has woken up and child process completed.\n", getpid());
    }
    return 0;
}
