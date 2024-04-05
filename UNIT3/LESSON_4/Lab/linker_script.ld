MEMORY
{
	Flash(rx):ORIGIN = 0x00000000 , LENGTH = 512M
	SRam(rwx):ORIGIN = 0x20000000 , LENGTH = 512M
}

SECTIONS
{
	.text :
	{
		*(.vector*)
		*(.text*)
		*(.rodata)
		. = ALIGN(4);
		_E_Text = .;
	}> Flash
	
	.data :
	{
		_S_Data = .;
		*(.data)
		. = ALIGN(4);
		_E_Data = .;
	}> SRam AT> Flash


	.bss :
	{
		_S_BSS = .;
		*(.bss) *(COMMON)
		. = ALIGN(4);
		_E_BSS = .;
	}> SRam
}