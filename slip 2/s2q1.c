#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pid;
    pid = fork();
    
    if (pid < 0) {
        printf("\nError in creation of child process");
        exit(1);
    } else if (pid == 0) {
        printf("\nHello World from Child Process (PID: %d)", getpid());
        exit(0);
    } else {
        printf("\nHi from Parent Process (PID: %d)", getpid());
        exit(0);
    }
}
