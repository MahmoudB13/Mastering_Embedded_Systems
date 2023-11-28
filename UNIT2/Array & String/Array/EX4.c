#include <stdio.h>
#include <stdlib.h>

void main(void)
{
	int num_of_elements,element,pos,elements[100];
	printf("Enter number of elements: ");
	fflush(stdout);
	scanf("%d",&num_of_elements);
	int i;
	for(i=0;i<num_of_elements;i++)
	{
		elements[i]=i+1;
	}

	printf("Enter element to be inserted: ");
	fflush(stdout);
	scanf("%d",&element);

	printf("Enter element position: ");
	fflush(stdout);
	scanf("%d",&pos);

	for(i=num_of_elements;i>0;i--)
		{
			if(i>pos-1)
			{
				elements[i]=elements[i-1];
			}
			else if (i==pos-1)
			{
				elements[i]=element;
			}
		}

	for(i=0;i<=num_of_elements;i++)
		{
			printf("%d ",elements[i]);
		}
}
