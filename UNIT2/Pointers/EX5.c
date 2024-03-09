#include <stdio.h>

struct Employee
{
	char *name;
	int ID;
}Emp;

int main()
{
	Emp.name="Mahmoud";
	Emp.ID=1002;


	struct Employee *ptr[2];
	ptr[0]=&Emp;
	printf("%s\n",ptr[0]->name);
	printf("%d",ptr[0]->ID);


}
