#include <stdio.h>
#include <stdlib.h>

 void main()
 {
	 int num,fact=1;
	 printf("Enter an integer: ");
	 fflush(stdout);
	 scanf("%d",&num);
	 int i;
	 for(i=num;i>0;i--)
	 {
		 fact*=i;
	 }
	 printf("Factorial of %d is: %d",num,fact);
 }
