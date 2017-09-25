ENTRY(Reset_Handler)

MEMORY
{
    FLASH   (RX) : ORIGIN = 0x08000000,        LENGTH = 128K
    RAM    (RWX) : ORIGIN = 0x20000000,        LENGTH = 20K
}

_ld_stack_address = ORIGIN(RAM) + LENGTH(RAM);

_ld_ram_satrt = ORIGIN(RAM);

SECTIONS
{
    . = ALIGIN(4);
    .text: 0x08000000:
    {
        _ld_text_start = .;
        . = ALIGIN(0x80);
        isr_vectorsflashoffs = . -0x08000000
        KEEP(*(".isr_vectorsflash"))
        . = ALIGIN(4);
        *(.text)
        *(.text.*)
        *(.stub .gnu.linkonce.t.*)
        *(.rodata .rodata.* gnu.linkonce.r.*)
        *(.glue_7 .glue_7t)
        _ld_text_end = .;
    } > FLASH
    _ld_text_size = SIZEOF(.text);

    .data:AT(ADDR(.text) + SIZEOF(.text))
    {
        _ld_data_start = .;
        *(vtable)
        *(.data*)
        *(.data .data.* .gnu.linkonce.d.*)
        . = ALIGIN(4);
        _ld_data_end = .;
    } > RAM
    _ld_data_size = SIZEOF(.data);

    .bss(NOLOAD)
    {
        _ld_bss_start = .;
        *(.bss)
        *(COMMON)
        _ld_bss_end = .;
    } > RAM
    _ld_bss_size = SIZEOF(.bss);
    
}