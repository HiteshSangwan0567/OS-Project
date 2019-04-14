#include<stdio.h>
#include<conio.h>
int main()
{
 int bt[100],wt[100],tat[100],b[100],time,remain,flag=0;
 int i,j, q=0,n,count=0, a, n1, tq , pr[100], temp, cst, temp1, rt[100], at[100];
 char pid[100];
 float twt=0,tTT=0,avgwt,avgtt;
 //clrscr();
 printf("Enter total number of process : ");
 scanf("%d",&n);
 printf("Enter the time Quantum");
 scanf("%d", &tq);

 remain=n;

 for(i=0;i<n;i++)
 {
  printf("\n Enter the process ID %d",i+1);
  scanf("%s",&pid[i]);
  printf("\nEnter the burst time of %d process : ",i+1);
  scanf("%d",&bt[i]);
  printf("\nEnter the Priority of process %d", i+1);
  scanf("%d",&pr[i]);

  //printf("Enter Arrival Time for Process Number %d :",count+1);
  //scanf("%d",&at[count]);
  b[i]= bt[i];
  //pid[c]=count+1;
}
  int pos;
  for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(pr[j]<pr[pos])
                pos=j;
        }

        temp=pr[i];
        pr[i]=pr[pos];
        pr[pos]=temp;

        temp=bt[i];
        bt[i]=bt[pos];
        bt[pos]=temp;

        temp=pid[i];
        pid[i]=pid[pos];
        pid[pos]=temp;
    }
i=0;
 for(time=0;count!=n;time++)
 {
   while(bt[i] == 0)
   {
     i=(i+1)%n;
   }
   bt[i]--;
   if(bt[i]==0)
   {
     tat[i] = time+1;
     count++;
   }
   i = (i+1)%n;
 }
 printf("\nprocess   burst   waitng   turnaround   ");
 for(i=0;i<n;i++)
 {  wt[i] = tat[i] - b[i];
    printf("\n   %d \t    %d \t     %d \t    %d",i+1,b[i],wt[i],tat[i]);
    twt = twt + wt[i];
    tTT = tTT + tat[i];
 }
 printf("\n  %d  %f  %f",n,twt,tTT);
 avgwt = twt / n;
 avgtt = tTT / n;
 printf("\nAverage waiting time is %f",avgwt);
 printf("\nAverage turnaround time is %f ",avgtt);
 getch();
}
