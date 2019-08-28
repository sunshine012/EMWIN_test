/*
*****************************************************************************
**
**  File        : K70FN1M0_flash.ld
**
**  Default linker command file for Flash targets
**
*****************************************************************************
*/
/* Entry Point */
ENTRY(__thumb_startup)

/* Highest address of the user mode stack */
_estack = 0x20010000;    /* end of lower SRAM */
__SP_INIT = _estack;

/* Generate a link error if heap and stack don't fit into RAM */ /* These value together plus the defined '.romp' should not be exeeding the m_data2 size*/
__heap_size = 0x100;        /* required amount of heap  */
__stack_size = 0x100;       /* required amount of stack */

/* Specify the memory areas */
MEMORY
{
  m_interrupts  (rx) : ORIGIN = 0x00000000, LENGTH = 0x200
  m_cfmprotrom  (rx) : ORIGIN = 0x00000400, LENGTH = 0x10
  m_text        (rx) : ORIGIN = 0x00000800, LENGTH = 1M - 0x800
  m_data       (rwx) : ORIGIN = 0x1FFF0000, LENGTH = 92K            /* Lower SRAM */
  m_data2      (rwx) : ORIGIN = 0x20007000, LENGTH = 36K            /* Upper SRAM */ /* only use for stack and heap*/
  m_ddrramframe (rw) : ORIGIN = 0x80000000, LENGTH = 0x400000
  m_ddrramdata  (rw) : ORIGIN = 0x80400000, LENGTH = 0x800000
}

        
/* Define output sections */
SECTIONS
{
  /* The startup code goes first into Flash */
  .interrupts :
  {
    __vector_table = .;
    . = ALIGN(4);
    KEEP(*(.vectortable)) /* Startup code */
    . = ALIGN(4);
  } > m_interrupts
  
  .cfmprotect :
  {
    . = ALIGN(4);
    KEEP(*(.cfmconfig)) /* Flash Configuration Field (FCF) */
    . = ALIGN(4);
  } > m_cfmprotrom

  /* The program code and other data goes into Flash */
  .text :
  {
    . = ALIGN(4);
    *(.text)                        /* .text sections (code) */
    *(.text*)                       /* .text* sections (code) */
    *(.rodata)                      /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)                     /* .rodata* sections (constants, strings, etc.) */
    *(._SectionHeaders_)            /* .rodata sections (SectionHeaders) */
    *(._SectionHeaders_*)           /* .rodata* sections (SectionHeaders) */
    *(._AppHeaders_)                /* .rodata sections (AppHeader) */
    *(._AppHeaders_*)               /* .rodata* sections (AppHeader) */
    *(._AppStandardStates_)         /* .rodata sections (AppStandardStates) */
    *(._AppStandardStates_*)        /* .rodata* sections (AppStandardStates) */
    *(._AlgorithmHeaders_)          /* .rodata sections (AlgorithmHeaders) */
    *(._AlgorithmHeaders_*)         /* .rodata* sections (AlgorithmHeaders) */
    *(._Algorithms_)                /* .rodata sections (Algorithms) */
    *(._Algorithms_*)               /* .rodata* sections (Algorithms) */
    *(._DatHeader_)                 /* .rodata sections (DatHeader) */
    *(._DatHeader_*)                /* .rodata* sections (DatHeader) */
    *(._DatDictionary_)             /* .rodata sections (DatDictionary) */
    *(._DatDictionary_*)            /* .rodata* sections (DatDictionary) */
    *(._DatDictionaryStdString_)    /* .rodata sections (DatDictionaryStdString) */
    *(._DatDictionaryStdString_*)   /* .rodata* sections (DatDictionaryStdString) */
    *(._DatDictionaryPtr_)          /* .rodata sections (DatDictionaryPtr) */
    *(._DatDictionaryPtr_*)         /* .rodata* sections (DatDictionaryPtr) */
    *(._DatFontHeader_)             /* .rodata sections (DatFontHeader) */
    *(._DatFontHeader_*)            /* .rodata* sections (DatFontHeader) */
    *(._DatFont_)                   /* .rodata sections (DatFont) */
    *(._DatFont_*)                  /* .rodata* sections (DatFont) */
    *(._ListHeaders_)               /* .rodata sections (ListHeaders) */
    *(._ListHeaders_*)              /* .rodata* sections (ListHeaders) */
    *(._Lists_)                     /* .rodata sections (Lists) */
    *(._Lists_*)                    /* .rodata* sections (Lists) */
    *(._TableHeaders_)              /* .rodata sections (TableHeaders) */
    *(._TableHeaders_*)             /* .rodata* sections (TabelHeaders) */
    *(._Tables_)                    /* .rodata sections (Tables) */
    *(._Tables_*)                   /* .rodata* sections (Tabels) */
	*(.fixed_location)				/* .fixed_location sections	*/
	*(.fixed_location*)				/* .fixed_location* sections */
    *(.glue_7)                      /* glue arm to thumb code */
    *(.glue_7t)                     /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } > m_text

  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } > m_text
  .ARM : {
    __exidx_start = .;
      *(.ARM.exidx*)
      __exidx_end = .;
  } > m_text
  
  .ctors :
  {
    __CTOR_LIST__ = .;
    /* gcc uses crtbegin.o to find the start of
       the constructors, so we make sure it is
       first.  Because this is a wildcard, it
       doesn't matter if the user does not
       actually link against crtbegin.o; the
       linker won't look for a file to match a
       wildcard.  The wildcard also means that it
       doesn't matter which directory crtbegin.o
       is in.  */
    KEEP (*crtbegin.o(.ctors))
    /* We don't want to include the .ctor section from
       from the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */
    KEEP (*(EXCLUDE_FILE (*crtend.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    __CTOR_END__ = .;
  } > m_text  
  .dtors :
  {
    __DTOR_LIST__ = .;
    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    __DTOR_END__ = .;
  } > m_text  

  .preinit_array :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } > m_text
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } > m_text
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    
    ___ROM_AT = .;
  } > m_text

  /* Initialized data sections goes into RAM, load LMA copy after code */
  .data : AT(___ROM_AT)
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } > m_data
  
  ___data_size = _edata - _sdata;
  
  ___m_data2_ROMStart = ___ROM_AT + SIZEOF(.data);
  .user_data2 : AT(___m_data2_ROMStart)
  {
     . = ALIGN(4);
     ___m_data2_RAMStart = .;
     *(.data2) /* This is an User defined section */
     *(.USBModuleData)
     *(.USBModuleData*)
     KEEP (*(.USBModuleData))
     ___m_data2_RAMEnd = .;
     . = ALIGN(4);
  } > m_data2
  ___m_data2_ROMSize = ___m_data2_RAMEnd - ___m_data2_RAMStart;


  .ddrramframe :
  {									/* section for external DDR video frames */
    . = ALIGN(4);
    _sddrramframe = .;

    . = ALIGN(4);
    _eddrramframe = .;
  } > m_ddrramframe

  ___m_ddr_ROMStart = ___ROM_AT + SIZEOF(.data) + SIZEOF(.user_data2);
  .ddrramdata :	AT(___m_ddr_ROMStart)
  {									/* section for external DDR code and data */
    . = ALIGN(4);
    _sddrramdata = .;
    *(._D4DRamData_)
    *(._D4DRamData_*)
    *(._BMISRamData_)
    *(._BMISRamData_*)
    *(.DataManagerModuleData)
    *(.DataManagerModuleData*)
    *(.RadioModuleData)
    *(.RadioModuleData*)
    *(._MdcaCurve_)
    *(._MdcaCurve_*)
    *(.TestRecordsRamData)
    *(.TestRecordsRamData*)
    . = ALIGN(4);
    _eddrramdata = .;
  } > m_ddrramdata
  ___m_ddr_ROMSize = _eddrramdata - _sddrramdata;


  /* Uninitialized data section */
  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section */
    __START_BSS = .;
    PROVIDE ( __bss_start__ = __START_BSS );
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    __END_BSS = .;
    PROVIDE ( __bss_end__ = __END_BSS );
  } > m_data

  /* User_heap_stack section, used to check that there is enough RAM left */
  ._user_heap_stack :
  {
    . = ALIGN(4);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    __heap_addr = .;
    . = . + __heap_size;
    . = . + __stack_size;
    . = ALIGN(4);
  } > m_data2
  
 /* start address for ROM area for initialized RAM and DDR */
  _romp_at = ___ROM_AT + SIZEOF(.data) + SIZEOF(.user_data2) + SIZEOF(.ddrramdata);
  .romp : AT(_romp_at)	
  {
    __S_romp = _romp_at;
    LONG(___ROM_AT);				/* ROM start address for RAM data */
    LONG(_sdata);					/* RAM start address for initialized data */
    LONG(___data_size);				/* number of bytes to be initialized */
    LONG(___m_data2_ROMStart);		/* ROM start address for RAM data */
    LONG(___m_data2_RAMStart);	    /* RAM start address for initialized data */
    LONG(___m_data2_ROMSize);	    /* number of bytes to be initialized */
    LONG(___m_ddr_ROMStart);	    /* ROM start address for DDR data */
    LONG(_sddrramdata);			    /* DDR start address for initialized data */
    LONG(___m_ddr_ROMSize);		    /* number of bytes to be initialized */
    LONG(0);						/* end indicator */
    LONG(0);
    LONG(0);
  } > m_data2
									/* start address of checksum or CRC */
   ___crcdata_loc = _romp_at + SIZEOF(.romp);
  .CRCSection ___crcdata_loc :
  {
   . = ALIGN(8);
   *(._Checksum_)					/* .rodata sections (_Checksum_) */
   *(._Checksum_*)					/* .rodata sections (_Checksum_*) */
   *(.CRCDataSection)				/* .rodata sections (CRCDataSection) */
   *(.CRCDataSection*)				/* .rodata sections (CRCDataSection*) */
   KEEP (*(._Checksum_))
   KEEP (*(.CRCDataSection))
   . = ALIGN(8);
  }
 
  .ARM.attributes 0 : { *(.ARM.attributes) }
}
