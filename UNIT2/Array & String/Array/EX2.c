#include<stdio.h>
#include<stdlib.h>

void main()
{
	int num_of_elements,elements[100];
	float sum=0,average;
	printf("Enter the number of elements: ");
	fflush(stdout);
	scanf("%d",&num_of_elements);
	printf("Enter the value of elements: ");
	fflush(stdout);
	int i;
	for(i=0;i<num_of_elements;i++)
	{
		scanf("%d",&elements[i]);
		sum=sum+elements[i];
	}
	average=sum/num_of_elements;
	printf("The average is: %f",average);
}
