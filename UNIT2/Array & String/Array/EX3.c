#include <stdio.h>
#include <stdlib.h>

void main()
{
	int matrix[3][3];
	int rows,columns;

	printf("Enter number of rows of the matrix: ");
	fflush(stdout);
	scanf("%d",&rows);

	printf("Enter number of columns of the matrix: ");
	fflush(stdout);
	scanf("%d",&columns);
	int i,j;
	for(i=0;i<rows;i++)
	{
		for(j=0;j<columns;j++)
		{
			printf("Enter element a%d%d: ",i+1,j+1);
			fflush(stdout);
			scanf("%d",&matrix[i][j]);
		}
	}

	for(i=0;i<columns;i++)
		{
			for(j=0;j<rows;j++)
			{
				printf("%d ",matrix[j][i]);
			}
			printf("\n");
		}

}
