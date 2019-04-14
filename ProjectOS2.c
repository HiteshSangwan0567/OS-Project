#include<stdio.h>

#include<conio.h>

#include<string.h>

void main()

{
int ts,need[10],wt[10],tat[10],pr[10],i,j,n,n1, pos,temp, temp1 ;
int bt[10],flag[10],ttat=0,twt=0;
char pid[10];
float awt,atat;

 //clrscr();


printf("\t\t ROUND ROBIN SCHEDULING");
printf("Enter the number of Processors \n");

scanf("%d",&n);

n1=n;

printf("\n Enter the Time Quantum \n");

scanf("%d",&ts);
for(i=1;i<=n;i++)

 {
   printf("\n Enter the process ID %d",i);
   scanf("%s",&pid[i]);
   printf("\n Enter the Burst Time for the process");
   scanf("%d",&bt[i]);
   printf("Enter Priority");
   scanf("%d", &pr[i]);
   need[i]=bt[i];
 }
for (i=0;i<n-1;i++)
	{
		for(j =i+1; j<n; j++)
		{
			if(pr[i]>pr[j])
			{
				temp1=pr[i];
				pr[i]=pr[j];
				pr[j]=temp1;
                temp1=bt[i];
				bt[i]=bt[j];
				bt[j]=temp1;
				strcpy(temp,pid[i]);
				strcpy(pid[i],pid[j]);
				strcpy(pid[j],temp);
			}
		}
	}

for(i=1;i<=n;i++)
 {
  flag[i]=1;
  wt[i]=0;
 }

while(n!=0)

 {
   for(i=1;i<=n;i++)

{
if(need[i]>=ts)

{
    for(j=1;j<=n;j++)

{
	  if((i!=j)&&(flag[i]==1)&&(need[j]!=0))

wt[j]+=ts;
       }





need[i]-=ts;

 if(need[i]==0)

 {
	 flag[i]=0;
	 n--;
       }
     }

else

 {
       for(j=1;j<=n;j++)

 {
	  if((i!=j)&&(flag[i]==1)&&(need[j]!=0))

wt[j]+=need[i];
       }

need[i]=0;

n--;

flag[i]=0;

 }
 }
}

for(i=1;i<=n1;i++)

{
  tat[i]=wt[i]+bt[i];

  twt=twt+wt[i];

  ttat=ttat+tat[i];
}

awt=(float)twt/n1;

atat=(float)ttat/n1;


printf("\n\n ROUND ROBIN SCHEDULING ALGORITHM \n\n");

printf("\n\n Process \t Process ID  \t BurstTime \t Waiting Time \t TurnaroundTime \n ");

for(i=1;i<=n1;i++)
{

 printf("\n %5d \t %d \t\t %5d \t\t %5d \t\t %5d \n",i,pid[i],bt[i],wt[i],tat[i]);
}


printf("\n The average Waiting Time=4%f",awt);

printf("\n The average Turn around Time=4%f",atat);
getch();
}

