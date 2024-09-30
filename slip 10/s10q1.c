#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int pid = fork();

    if (pid > 0) {
        // Parent process
        printf("Parent process \n");
        printf("ID : %d \n\n", getpid());
    } 
    else if (pid == 0) {
        // Child process
        printf("Child process \n");
        printf("ID : %d \n", getpid());
        sleep(10);  // Child process sleeps for 10 seconds
        printf("\nChild process woke up\n");
        printf("ID : %d \n", getpid());
    } 
    else {
        // Fork failed
        printf("Failed to create child process\n");
    }

    return 0;
}
