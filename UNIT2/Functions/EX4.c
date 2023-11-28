#include<stdio.h>
#include<stdlib.h>

int power(int base,int pow)
{
	if(pow>1)
		base*=power(base,pow-1);
	return base;
}

void main(void)
{
	int base,pow;
	printf("Enter base: ");
	fflush(stdout);
	scanf("%d",&base);
	printf("Enter power: ");
	fflush(stdout);
	scanf("%d",&pow);
	printf("%d",power(base,pow));
}
