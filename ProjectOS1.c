#include<stdio.h>
#include<conio.h>
#include<string.h>
int main()
{
	char p[10][5], temp[5];
	int i, j, pt[10], totwt=0, pr[10], temp1, n, wt[10], et[10];
	float avgwt;
	printf("Enter the no fo Processes");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Enter process %d name",i+1);
		scanf("%s", &i);
		printf("Enter process time");
		scanf("%s", &p[i]);
		printf("Enter Priority");
		scanf("%d", &pr[i]);
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
				strcpy(temp,p[i]);
				strcpy(p[i],p[j]);
				strcpy(p[j],temp);
			}
		}
	}
	wt[0]=0;
	for(i=1;i<n;i++)
	{
		wt[i]=wt[i+1]+et[i-1];
		totwt= totwt+wt[i];
	}

	avgwt= (float)totwt/n;

	printf("p_name\t    p_time\t    priority\t   w_time\n");

	for(i=0;i<n;i++)
	{
		printf("     %s\t   %d\t    %d\n", p[i], pt[j], pr[i], wt[i]);
	}
	printf("Total Waiting Time = %d\n  avg waiting time= %f", totwt, avgwt);

	getch();
}

