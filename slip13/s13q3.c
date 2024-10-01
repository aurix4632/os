#include<stdio.h>
#include<stdlib.h>

struct job
{
    int atime;  //arrival time
    int btime;  //brust time
    int ft;  //finish time
    int tat;  //turnaround time
    int wt;  //waiting time
}p[10];

int arr[10],brust[10],n,rq[10],no_rq=0,time=0;

void main()
{
    int i,j;
    printf("Enter the job number : ");
    scanf("%d",&n); 
    printf("\n");
    
    for(i=0;i<n;i++)
    {
        printf("Enter the arrival time p%d : ",i);
        scanf("%d",&p[i].atime);  //assign arrival time
        arr[i]=p[i].atime;
    }
    printf("\n");
    
    for(i=0;i<n;i++)
    {
        printf("Enter the arrival time p%d : ",i);
        printf("%d\n",p[i].atime);  //printing arrival time
        arr[i]=p[i].atime;
    }
    printf("\n");
    
    for(i=0;i<n;i++)
    {
        printf("Enter the brust time p%d:",i);
        scanf("%d",&p[i].btime);  //assigning brust time
        brust[i]=p[i].btime;
    }
    printf("\n");
    
    for(i=0;i<n;i++)
    {
        printf("Enter the brust time p%d:",i);
        printf("%d\n",p[i].btime);  //printing brust time
        brust[i]=p[i].btime;
    }
    printf("\n");
    
    addrq();  //adding process
    //process start now
    printf("Gantt Chart is : ");
    while(1)
    {
        j=selectionjob();  //search process now
        if(j==-1)
        {
            printf("CPU is dead");
            time++;
            addrq();
        }
        else
        {
            while(brust[j]!=0)
            {
                printf("\t j %d",j);
                brust[j]--;
                time++;
                addrq();
            }
            p[j].ft=time;
        }
        if(fsahll()==1)
        break;
    }
    
    int Tat=0,Twt=0;
    
    printf("\n");
    printf("\nJob\tFT\tTAT\tWT");
    for(i=0;i<n;i++)
    {
        p[i].tat=p[i].ft-p[i].atime;
        p[i].wt=p[i].tat-p[i].btime;
        
        printf("\n Job %d \t %d \t %d \t %d",i,p[i].ft,p[i].tat,p[i].wt);
        Tat+=p[i].tat;
        Twt+=p[i].wt;
    }
    
    float avgtat=Tat/n;
    float avgwt=Twt/n;
    
    printf("\n Average trunaround time is : %f",avgtat);
    printf("\n Average waiting time is : %f",avgwt);
}

int addrq()
{
    int i;
    for(i=0;i<n;i++)
    {
        if(arr[i]==time)
        {
            rq[no_rq]=i;
            no_rq++;
        }
    }
}

int selectionjob()
{
    int i,j;
    if(no_rq==0)
    return 1;
    j=rq[0];
    
    for(i=1;i<no_rq;i++)
    if(brust[j]>brust[rq[i]])
    j=rq[i];
    
    deleteq(j);
    return j;
}

int deleteq(int j)
{
    int i;
    for(i=0;i<no_rq;i++)
    
    if(rq[i]==j)
    break;
    
    for(i=i+1;i<no_rq;i++)
    rq[i-1]=rq[i];
    no_rq--;
}

int fsahll()
{
    int i;
    for(i=0;i<n;i++)
    if(brust[i]!=0)
    return -1;
    return 1;
}
