#include <stdio.h>
#include <stdlib.h>

 void main()
 {
	 int num,sum;
	 printf("Enter an integer: ");
	 fflush(stdout);
	 scanf("%d",&num);
	 sum = num*(num+1)/2;
	 printf("sum = %d",sum);
 }
