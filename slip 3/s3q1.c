#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();  // Create child process
    
    if (pid < 0) {
        perror("Fork Failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        printf("Child Process: My PID is %d\n", getpid());
        printf("Child Process: Executing 'ls' command...\n");
        
        // Execute the 'ls' command in the child process
        execlp("ls", "ls", (char*)NULL);
        
        // This line is reached only if execlp fails
        perror("execlp failed");
        exit(EXIT_FAILURE);
    }
    else {
        printf("Parent Process: My PID is %d\n", getpid());
        printf("Parent Process: Waiting for the child to finish...\n");
        
        // Wait for the child process to terminate
        wait(NULL);
        
        printf("Parent Process: Child has finished\n");
    }

    return 0;
}
