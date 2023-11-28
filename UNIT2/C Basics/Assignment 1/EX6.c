#include <stdio.h>
#include <stdlib.h>

int main()
{
	int first_num,second_num,temp;
	printf("Enter first number: ");
	fflush(stdout);
	scanf("%d",&first_num);
	printf("Enter second number: ");
	fflush(stdout);
	scanf("%d",&second_num);
	temp= first_num;
	first_num = second_num;
	second_num = temp;
	printf("after swapping value of fisrt number= %d\nafter swapping value of second number= %d",first_num,second_num);
	return 0;
}
