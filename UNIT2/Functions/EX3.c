#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void reverse(char string[],int len)
{
	static int i=0;
	if(i<len-i)
	{
		char temp = string[i];
		string[i]=string[len-i-1];
		string[len-i-1]=temp;
		i++;
		reverse(string,len);
	}
	string[len]=0;

}

void main(void)
{
	char string[100];
	printf("Enter a string: ");
	fflush(stdout);
	gets(string);
	reverse(string,strlen(string));
	printf("%s ",string);
}
