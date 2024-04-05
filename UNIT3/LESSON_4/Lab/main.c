#include <stdio.h>
#include <stdint.h>

#define SYSCTL 0X400FE000
#define SYSCTL_RCGC2_R (*((volatile uint32_t*)(SYSCTL+0x108)))

#define GPIOF 0X40025000
#define GPIOF_PORTF_DIR_R (*((volatile uint32_t*)(GPIOF+0x400)))
#define GPIOF_PORTF_DR_R  (*((volatile uint32_t*)(GPIOF+0x3FC)))
#define GPIOF_PORTF_DEN_R (*((volatile uint32_t*)(GPIOF+0x51C)))

int main()
{
	volatile uint32_t delay;

	SYSCTL_RCGC2_R = 0x20;
	for(delay=0;delay<5000;delay++);

	GPIOF_PORTF_DIR_R |= 1<<3;
	GPIOF_PORTF_DEN_R |= 1<<3;

	while(1)
	{
		GPIOF_PORTF_DR_R |= 1<<3;
		for(delay=0;delay<5000;delay++);
		GPIOF_PORTF_DR_R &= ~(1<<3);
		for(delay=0;delay<5000;delay++);
	}
	return 0;
}