#include <stdio.h>

int main()
{
	char str[50];
	printf("Enter a string: ");
	fflush(stdout);
	gets(str);
	int temp=strlen(str);
	char* ptr=str+temp-1;
	int i;
	for(i=0;i<temp;i++)
	{
	printf("%c",*(ptr-i));
	}
}
