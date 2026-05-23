EXTERN(vector_table)

ENTRY(reset_handler)

MEMORY
{
	rom (rx)  : ORIGIN = 0x00000000, LENGTH = 0x00400000
	ram (rwx) : ORIGIN = 0x20000000, LENGTH = 0x00400000
}

SECTIONS
{
	.text :
	{
		KEEP(*(.vectors))

		_stext = .;
		*(.text*)
		_etext = .;
	} > rom

	.bss : 
	{
		_sbss = .;
		*(.bss*)
		_ebss = .;
	} > ram

	.stack :
	{

	}

	.data :
	{
		_sidata = LOADADDR(.data);
		_sdata = .;
		*(.data*)
		_edata = .;
	} > ram AT > rom
}

_estack = ORIGIN(ram) + LENGTH(ram);
