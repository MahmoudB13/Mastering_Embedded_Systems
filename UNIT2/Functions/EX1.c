#include<stdio.h>
#include<stdlib.h>

void prime(int min,int max)
{
	int i,j,flag;
	for(i=min;i<=max;i++)
	{
		flag=1;
		for(j=2;j<=i/2;j++)
		{
			if(i%j==0)
			{
				flag=0;
				break;
			}
			else flag=1;
		}
		/*if(i==2 || i==3)
		{
			flag=1;
		}*/
		if(flag==1&&i>1) printf("%d ",i);
	}
}

void main(void)
{
	int min,max;
	printf("Enter the minimum limit: ");
	fflush(stdout);
	scanf("%d",&min);
	printf("Enter the maximum limit: ");
	fflush(stdout);
	scanf("%d",&max);
	printf("Prime numbers between %d and %d are: ",min,max);
	prime(min,max);
}
