#include <stdio.h>

int main()
{
	char x='A';
	char *ptr = &x;
	for(;x<='Z';(*ptr)++)
	{
		printf("%c ",x);
	}
}
