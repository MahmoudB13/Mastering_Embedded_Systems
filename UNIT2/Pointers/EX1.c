#include <stdio.h>


int main()
{
	int m=29;
	int *ab=&m;
	printf("value of m = %d\naddress of m = 0x%x \n",m,&m);
	printf("value of ab = %d\naddress of ab = 0x%x \n",*ab,ab);
	m=34;
	printf("value of ab = %d\naddress of ab = 0x%x \n",*ab,ab);
	*ab=7;
	printf("value of ab = %d\naddress of ab = 0x%x \n",*ab,ab);
}
