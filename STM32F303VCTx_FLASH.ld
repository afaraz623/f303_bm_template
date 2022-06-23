OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(Reset_Handler) /* entry Point */

MEMORY { /* memory map of Tiva TM4C123GH6PM */
    RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 40K
	CCMRAM (xrw) : ORIGIN = 0x10000000, LENGTH = 8K
    ROM (rx)  : ORIGIN = 0x00000000, LENGTH = 256K

}

/* The size of the stack used by the application. NOTE: you need to adjust  */
STACK_SIZE = 1024;

/* The size of the heap used by the application. NOTE: you need to adjust   */
HEAP_SIZE = 16;

SECTIONS 
{
    .isr_vector : {        /* the vector table goes FIRST into ROM */
        KEEP(*(.isr_vector)) /* vector table */
        . = ALIGN(4);
    } >ROM

    .text : {              /* code and constants */
        . = ALIGN(4);
        *(.text)           /* .text sections (code) */
        *(.text*)          /* .text* sections (code) */
        *(.rodata)         /* .rodata sections (constants, strings, etc.) */
        *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */

        KEEP (*(.init))
        KEEP (*(.fini))

        . = ALIGN(4);
    } >ROM

	/* .ARM.extab : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >ROM
  	
	.ARM : {
    	__exidx_start = .;
    	*(.ARM.exidx*)
    	__exidx_end = .;
  	} >ROM */

    .preinit_array : {
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array*))
        PROVIDE_HIDDEN (__preinit_array_end = .);
    } >ROM

    .init_array : {
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
    } >ROM

    .fini_array : {
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(.fini_array*))
        KEEP (*(SORT(.fini_array.*)))
        PROVIDE_HIDDEN (__fini_array_end = .);
    } >ROM

    _etext = .;            /* global symbols at end of code */

    .stack : {
        __stack_start__ = .;
        . = . + STACK_SIZE;
        . = ALIGN(4);
        __stack_end__ = .;
    } >RAM

    .data :  AT (_etext) {
        __data_load = LOADADDR (.data);
        __data_start = .;
        *(.data)           /* .data sections */
        *(.data*)          /* .data* sections */
        . = ALIGN(4);
        __data_end__ = .;
        _edata = __data_end__;
    } >RAM

    .bss : {
        __bss_start__ = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;         /* define a global symbol at bss end */
        __bss_end__ = .;
    } >RAM

    PROVIDE ( end = _ebss );
    PROVIDE ( _end = _ebss );
    PROVIDE ( __end__ = _ebss );

    .heap : {
        __heap_start__ = .;
        . = . + HEAP_SIZE;
        . = ALIGN(4);
        __heap_end__ = .;
    } >RAM

	_siccmram = LOADADDR(.ccmram);

	/* CCM-RAM section 
	* 
	* IMPORTANT NOTE! 
	* If initialized variables will be placed in this section,
	* the startup code needs to be modified to copy the init-values.  
	*/
	.ccmram :
	{
		. = ALIGN(4);
		_sccmram = .;       /* create a global symbol at ccmram start */
		*(.ccmram)
		*(.ccmram*)
		
		. = ALIGN(4);
		_eccmram = .;       /* create a global symbol at ccmram end */
	} >CCMRAM AT> ROM

    /* Remove information from the standard libraries */
    /DISCARD/ : {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }
}
