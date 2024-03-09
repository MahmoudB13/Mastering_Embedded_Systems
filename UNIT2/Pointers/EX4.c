#include <stdio.h>

int main()
{
	int num;
	printf("Input the number of elements to store in the array (max 15): ");
	fflush(stdout);
	scanf("%d",&num);
	int elements[15];
	int i;
	for(i=0;i<num;i++)
	{
		printf("Enter element number %d: ",i+1);
		fflush(stdout);
		scanf("%d",&elements[i]);
	}

	int *ptr = elements;
	for(i=0;i<num;i++)
		{
			printf("element number %d: %d\n",num-i,(*ptr+num-1-i));
			fflush(stdout);
		}
}
