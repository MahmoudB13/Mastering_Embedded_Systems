#include <stdio.h>
#include <stdlib.h>

void main()
{
	int num1,num2,num3;
	printf("Enter three numbers: ");
	fflush(stdout);
	scanf("%d %d %d",&num1 ,&num2 ,&num3);
	if(num1>num2)
	{
		if(num1>num3) printf("%d is the largest",num1);
		else printf("%d is the largest",num3);
	}
	else
	{
		if(num2>num3) printf("%d is the largest",num2);
		else printf("%d is the largest",num3);
	}
}

