#include <stdio.h>
#include <stdlib.h>

void main()
{
	char letter;
	printf("Enter a letter: ");
	fflush(stdout);
	scanf("%c",&letter);
	switch(letter)
	{
	case 'a':
	case 'e':
	case 'i':
	case 'o':
	case 'u':
		printf("%c is a vowel",letter);
		break;
	default: printf("%c is a consonant",letter);
	break;
	}
}
