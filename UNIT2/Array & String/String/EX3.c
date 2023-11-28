#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main(void)
{
	char string[100];
	char reversed[100];
	printf("Enter a string: ");
	fflush(stdout);
	gets(string);
	int len=strlen(string);
	int i;
	for(i=0;i<len;i++)
	{
		reversed[i]=string[len-i-1];
	}
	reversed[i]=0;
	printf("%s",reversed);
}
