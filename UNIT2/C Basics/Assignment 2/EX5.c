#include <stdio.h>
#include <stdlib.h>

void main()
{
	char letter;
	printf("Enter a letter: ");
	fflush(stdout);
	scanf("%c",&letter);
	if((letter>='a' && letter <='z') || (letter>='A' && letter <='Z'))
		printf("%c is a letter",letter);
	else printf("%c is not a letter",letter);
}
