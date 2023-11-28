#include <stdio.h>
#include <stdlib.h>

void main()
{
	int num;
	printf("enter a number: ");
	fflush(stdout);
	scanf("%d",&num);
	if(num%2)
	{
		printf("%d is odd",num);
	}
	else
	{
		printf("%d is even",num);
	}
}
