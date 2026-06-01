MEMORY
{
	rom (rx)  : ORIGIN = 0x00000000, LENGTH = 0x00400000
	ram (rwx) : ORIGIN = 0x20000000, LENGTH = 0x00400000
}

_eram = ORIGIN(ram) + LENGTH(ram);
_stack = _eram;

SECTIONS
{
    .text : ALIGN(4)
    {
        KEEP(*(.ivt))
        *(.text*)
        . = ALIGN(4);
        _etext = .;
    } > rom

    .init_array : ALIGN(4)
    {
        __init_array_start = .;
        KEEP(*(.init_array*))
        __init_array_end = .;
        . = ALIGN(4);
    } > rom

    _idata = LOADADDR(.data);

    .data : ALIGN(4)
    {
        _data = .;
        *(.data*);
        . = ALIGN(4);
        _edata = .;
    } > ram AT > rom

    .bss : ALIGN(4)
    {
        _bss = .;
        *(.bss*)
        . = ALIGN(4);
        _ebss = .;
        PROVIDE(_end = .);
    } > ram
}