#include <stdio.h>
#include <stdlib.h>

void main(void)
{
	int num_of_elements,value,pos,elements[100];
	printf("Enter number of elements: ");
	fflush(stdout);
	scanf("%d",&num_of_elements);
	printf("Enter elements: ");
	fflush(stdout);
	int i;
	for(i=0;i<num_of_elements;i++)
	{
		scanf("%d",&elements[i]);
	}

	printf("Enter element to be searched for: ");
	fflush(stdout);
	scanf("%d",&value);

	for(i=0;i<num_of_elements;i++)
	{
		if(value==elements[i]) pos=i+1;
	}
	printf("Number found at location: %d",pos);
}
