#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//structure to represent a job
typedef struct
{
    int arrival_time;
    int first_cpu_burst;
    int next_cpu_burst;
    int turnaround_time;
    int waiting_time;
}Job;

//function to calculate average turnaround & waiting time
void calculateAverages(Job jobs[], int n, float *avg_turnaround, float *avg_waiting)
{
    int total_turnaround = 0;
    int total_waiting = 0;
    
    for(int i=0;i<n;i++)
    {
        total_turnaround += jobs[i].turnaround_time;
        total_waiting += jobs[i].waiting_time;
    }
    *avg_turnaround = (float)total_turnaround/n;
    *avg_waiting = (float)total_waiting/n;
}

int main()
{
    int n; //number of jobs
    srand(time(NULL)); //send the random no. generator with the current time
    printf("Enter the number of jobs : ");
    scanf("%d",&n);
    
    Job jobs[n];
    
    //input arrival time & first CPU burst for each job
    for(int i=0;i<n;i++)
    {
        printf("Job %d\n",i+1);
        printf("Arrival Time : ");
        scanf("%d",&jobs[i].arrival_time);
        printf("First CPU Burst Time : ");
        scanf("%d",&jobs[i].first_cpu_burst);
        
        //initialize other job attributes
        jobs[i].next_cpu_burst=0;
        jobs[i].turnaround_time=0;
        jobs[i].waiting_time=0;
    }
    
    int current_time=0;
    
    //process jobs in FCFS order
    for(int i=0;i<n;i++)
    {
        //wait for the job to arrive
        if(current_time < jobs[i].arrival_time)
        {
            current_time = jobs[i].arrival_time;
        }
        
        //update next CPU burst using a random function (e.g., rand())
        jobs[i].next_cpu_burst = rand() % 10 + 1; //generating random burst time between 1 & 10 units
        
        //calculate turnaround & waiting times
        {
            jobs[i].turnaround_time = current_time + jobs[i].first_cpu_burst + jobs[i].next_cpu_burst - jobs[i].arrival_time;
            jobs[i].waiting_time = jobs[i].turnaround_time - jobs[i].first_cpu_burst - jobs[i].next_cpu_burst;
            
            //update the current time
            current_time += jobs[i].first_cpu_burst + jobs[i].next_cpu_burst;
        }
        
        //calculate & display the Gantt chart
        printf("\n Gantt Chart : \n");
        printf("0");
        for(int i=0;i<n;i++)
        {
            printf(" -> Job %d -> %d", i+1, current_time);
        }
        printf("\n");
        
        //display turnaround & waiting times for each job
        printf("\n Turnaround Time and Waiting Time : \n");
        for(int i=0;i<n;i++)
        {
            printf("Job %d - Turnaround Time : %d, Waiting Time : %d\n",i+1,jobs[i].turnaround_time, jobs[i].waiting_time);
        }
        //calculate & display average turnaround & waiting time
        float avg_turnaround, avg_waiting;
        calculateAverages(jobs, n, &avg_turnaround, &avg_waiting);        
        printf("\n Average Turnaround Time : %.2fn", avg_turnaround);
        printf("\n Average Waiting Time : %.2fn", avg_waiting);
    }
    return 0;
}

