#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float first_num,second_num,mul;
	printf("Enter two numbers");
	fflush(stdout);
	scanf("%f %f", &first_num, &second_num);
	mul = first_num * second_num;
	printf("Product= %f",mul);
	return 0;
}
