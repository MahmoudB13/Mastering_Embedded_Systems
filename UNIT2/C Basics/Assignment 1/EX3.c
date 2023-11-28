#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int first_num,second_num,sum;
	printf("Enter two numbers: ");
	fflush(stdout);
	scanf("%d %d", &first_num, &second_num);
	sum= first_num + second_num;
	printf("Sum= %d",sum);
	return 0;
}
