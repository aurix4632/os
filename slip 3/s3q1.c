
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    pid = fork();  // Create a new child process

    if (pid < 0) {
        // If fork() fails
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        // Child process
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());

        // Replace child process with a new program using exec()
        // Here, we use `execlp` to run the "ls" command as an example.
        // Replace "ls" with any program you wish to run in the child process.
        if (execlp("ls", "ls", NULL) == -1) {
            perror("Exec failed");
            exit(1);
        }
    } 
    else {
        // Parent process
        printf("Parent process: PID = %d\n", getpid());

        // Wait for child to complete
        wait(NULL);  // wait() blocks until the child process terminates
        printf("Child process terminated. Control is back to the parent process.\n");
    }
    
    return 0;
}
