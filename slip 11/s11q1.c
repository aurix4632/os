#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    int pid;
    pid=fork();
    if(pid<0)  //-ve value error
    {
        printf("\n Error in creation of child process");
        exit(1);
    }
    else if(pid==0)  //child process
    {
        printf("\n Hello World");
        exit(0);
    }
    else
    {
        printf("\n Hi");
        exit(1);
    }
}
