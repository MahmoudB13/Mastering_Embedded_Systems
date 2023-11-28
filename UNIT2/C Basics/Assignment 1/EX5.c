#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char input;
	printf("Enter a character: ");
	fflush(stdout);
	scanf("%c",&input);
	printf("ASCII value of %c = %d",input,input);
	return 0;
}
