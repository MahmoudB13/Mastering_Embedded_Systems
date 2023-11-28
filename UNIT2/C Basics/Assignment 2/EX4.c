#include <stdio.h>
#include <stdlib.h>
void main()
{
	int num;
	printf("Enter a number: ");
	fflush(stdout);
	scanf("%d",&num);
	if(num>0) printf("%d is positive",num);
	else if (num<0) printf("%d is negative",num);
	else printf("%d is zero",num);
}
