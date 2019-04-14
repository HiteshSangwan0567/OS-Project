#include<stdio.h>
#include<conio.h>
int main()
{
 int bt[100],wt[100],tat[100],b[100],time,remain,flag=0;
 int i,j, q=0,n,count, a, n1, tq , pr[100], temp, temp1, rt[100], at[100];
 char pid[100];
 float twt=0,tTT=0,awt=0,att=0, wait_time=0, turnaround_time=0;
 //clrscr();
 printf("Enter total number of process : ");
 scanf("%d",&n);
 printf("Enter the time Quantum");
 scanf("%d", &tq);

 remain=n;

 for(count=0;count<n;count++)
 {
  printf("\n Enter the process ID %d",count+1);
  scanf("%s",&pid[count]);
  printf("\nEnter the burst time of %d process : ",count+1);
  scanf("%d",&bt[count]);
  printf("\nEnter the Priority of process %d", count+1);
  scanf("%d",&pr[count]);
  printf("Enter Arrival Time for Process Process Number %d :",count+1);
  scanf("%d",&at[count]);
  rt[count]=bt[count];
  //pid[count]=count+1;
}
  int pos;
  for(count=0;count<n;count++)
    {
        pos=count;
        for(j=count+1;j<n;j++)
        {
            if(pr[j]<pr[pos])
                pos=j;
        }

        temp=pr[count];
        pr[count]=pr[pos];
        pr[pos]=temp;

        temp=bt[count];
        bt[count]=bt[pos];
        bt[pos]=temp;

        temp=pid[count];
        pid[count]=pid[pos];
        pid[pos]=temp;
    }

 printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");
  for(time=0,count=0;remain!=0;)
  {
    if(rt[count]<=tq && rt[count]>0)
    {
      time+=rt[count];
      rt[count]=0;
      flag=1;
    }
    else if(rt[count]>0)
    {
      rt[count]-=tq;
      time+=tq;
    }
    if(rt[count]==0 && flag==1)
    {
      remain--;
      printf("P[%d]\t|\t%d\t|\t%d\n",count+1,time-at[count],time-at[count]-bt[count]);
      wait_time+=time-at[count]-bt[count];
      turnaround_time+=time-at[count];
      flag=0;
    }
    if(count==n-1)
      count=0;
    else if(at[count+1]<=time)
      count++;
    else
      count=0;
  }
  printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n);
  printf("Avg Turnaround Time = %f",turnaround_time*1.0/n);
  return 0;
}



