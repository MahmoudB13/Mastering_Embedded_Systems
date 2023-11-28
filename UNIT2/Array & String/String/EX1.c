#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main(void)
{
	char character,string[100];
	printf("Enter a string: ");
	fflush(stdout);
	gets(string);
	printf("Enter a character to find frequency: ");
	fflush(stdout);
	scanf("%c",&character);

	int i,count=0;
	for(i=0;i<strlen(string);i++)
	{
		if(string[i]==character) count++;
	}
	printf("Frequency of %c = %d",character,count);
}
