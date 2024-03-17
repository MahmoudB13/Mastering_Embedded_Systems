#include <stdint.h>

extern int  main();
void Default_Handler();
void Reset_Handler();
void NMI_Handler() __attribute__((weak,alias("Default_Handler")));
void H_Fault_Handler() __attribute__((weak,alias("Default_Handler")));
void MM_Fault_Handler() __attribute__((weak,alias("Default_Handler")));
void Bus_Handler() __attribute__((weak,alias("Default_Handler")));
void Usage_Fault_Handler() __attribute__((weak,alias("Default_Handler")));

extern uint32_t _Stack_Top;

uint32_t vectors[] __attribute__((section(".vectors"))) = {
	(uint32_t)&_Stack_Top,
	(uint32_t)&Reset_Handler,
	(uint32_t)&NMI_Handler,
	(uint32_t)&H_Fault_Handler,
	(uint32_t)&MM_Fault_Handler,
	(uint32_t)&Bus_Handler,
	(uint32_t)&Usage_Fault_Handler
};

extern uint32_t _E_Text;
extern uint32_t _S_Data;
extern uint32_t _E_Data;
extern uint32_t _S_BSS;
extern uint32_t _E_BSS;
void Reset_Handler()
{
	uint32_t Data_Size = (uint8_t*)&_E_Data - (uint8_t*)&_S_Data;
	uint8_t* P_Source = (uint8_t*)&_E_Text;
	uint8_t* P_Distination = (uint8_t*)&_S_Data;

	for(int i=0;i<Data_Size;i++)
	{
		*((uint8_t*)P_Distination++) = *((uint8_t*)P_Source++);

	}

	uint32_t BSS_Size = (uint8_t*)&_E_BSS - (uint8_t*)&_S_BSS;
	uint8_t* P_BSS = (uint8_t*)&_S_BSS;

	for(int i=0;i<BSS_Size;i++)
	{
		*((uint8_t*)P_BSS++)=(uint8_t)0;
	}

	main();
}

void Default_Handler()
{
	Reset_Handler();
}