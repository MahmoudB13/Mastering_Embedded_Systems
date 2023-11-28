#include <stdio.h>
#include <stdlib.h>

int main()
{
	int first_num,second_num;
	printf("Enter first number: ");
	fflush(stdout);
	scanf("%d",&first_num);
	printf("Enter second number: ");
	fflush(stdout);
	scanf("%d",&second_num);

	//using addition
	/*first_num+=second_num;
	second_num=first_num-second_num;
	first_num-=second_num;*/

	//using xor
	first_num^=second_num;
	second_num^=first_num;
	first_num^=second_num;

	printf("after swapping value of fisrt number= %d\nafter swapping value of second number= %d",first_num,second_num);
	return 0;
}
