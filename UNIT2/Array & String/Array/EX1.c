#include <stdio.h>
#include <stdlib.h>

void main()
{
	int matrix1[2][2];
	int matrix2[2][2];
	int sum[2][2];
	printf("Enter elements of the first matrix: ");
	fflush(stdout);
	int i,j;
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			scanf("%d",&matrix1[i][j]);
		}
	}

	printf("Enter elements of the second matrix: ");
		fflush(stdout);
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			scanf("%d",&matrix2[i][j]);
		}
	}
	for(i=0;i<2;i++)
		{
			for(j=0;j<2;j++)
			{
				sum[i][j]=matrix1[i][j]+matrix2[i][j];
				printf("%d ",sum[i][j]);
			}
			printf("\n");
		}

}
