#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main(void)
{
	char string[100];
	printf("Enter a string: ");
	fflush(stdout);
	gets(string);
	int i=0,length=0;
	while(string[i]!=0)
	{
		length++;
		i++;
	}
	printf("Length of the string: %d",length);
}
