ENTRY(Reset_Handler)

MEMORY
{
    FLASH   (RX) : ORIGIN = 0x08000000,        LENGTH = 128K
    RAM    (RWX) : ORIGIN = 0x20000000,        LENGTH = 20K
}

_ld_stack_address = ORIGIN(RAM) + LENGTH(RAM);

_ld_ram_start = ORIGIN(RAM);

SECTIONS
{
   . = ALIGN(4);
   .text 0x08000000:
   {
      _ld_text_start = .;
      . = ALIGN(0x80); /* PM0056, Rev.1 (4/2009), 4.3.3 */
      _isr_vectorsflash_offs = . - 0x08000000;
      KEEP(*(.isr_vectorsflash))
      . = ALIGN(4);
      *(.text)
      *(.text.*)                             /* remaining code (-ffunction-sections)*/
      *(.stub .gnu.linkonce.t.*)
      *(.rodata .rodata.* .gnu.linkonce.r.*) /* read-only data (constants) */
      *(.glue_7 .glue_7t)                    /* redundant for thumb2 ?! */
      _ld_text_end = .;
   } >FLASH
   _ld_text_size = SIZEOF(.text);

   .data  : AT (ADDR(.text) + SIZEOF(.text))
   {
      _ld_data_start = .;
		*(vtable)
		*(.data*)
    *(.data .data.* .gnu.linkonce.d.*)
		. = ALIGN(4);
		/* All data end */
      _ld_data_end = .;
   } >RAM
   _ld_data_size = SIZEOF(.data);

    .bss (NOLOAD):
   {
      _ld_bss_start = .;
      *(.bss)
      *(COMMON)
      _ld_bss_end = .;
   } >RAM
   _ld_bss_size = SIZEOF(.bss);
}