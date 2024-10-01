#include<stdio.h>
#include<time.h>

int main()
{
    int i;
    clock_t start_time = clock();
    for(i=1;i<1000000;i++)
    {
        
    }
    clock_t end_time = clock();
    double execution_time = (double)(end_time-start_time)/CLOCKS_PER_SEC;
    printf("Execution time : %f seconds\n",execution_time);
    return 0;
}
