#include<stdio.h>
#include<stdlib.h>

int factorial(int num)
{
	static int fact=1;
	fact*=num;
	if(num>1)
	{
		factorial(num-1);
	}
}

void main(void)
{
	int num;
	printf("Enter a positive integer: ");
	fflush(stdout);
	scanf("%d",&num);
	printf("%d factorial is %d",num,factorial(num));
}
