# Toolchain prefix (i.e arm-elf- -> arm-elf-gcc.exe)-----------------------------------------------
TCHAIN_PREFIX = arm-none-eabi-

#REMOVE_CMD=cs-rm ---------------------------------------------------------------------------------
REMOVE_CMD=rm

# Target ------------------------------------------------------------------------------------------
TARGET = remote_ctrl

# List C++ source files here.
# use file-extension .cpp for C++-files (not .C)
# SRC = start_stm32f10x.c

# SRC ---------------------------------------------------------------------------------------------
SRC = stm32md_startup.c main.c

# Compiler flags. ---------------------------------------------------------------------------------

THUMB = -mthumb
INCLUDE = -I./include -I.

#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
#
# Flags for C and C++ (arm-elf-gcc/arm-elf-g++)
CFLAGS  = -gdwarf-2 -O2 -mcpu=cortex-m3 -mthumb-interwork -DSTM32F10X_MD 
CFLAGS += $(INCLUDE) -mlong-calls -ffunction-sections -fdata-sections -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls 
CFLAGS += -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=start_stm32f10x.lst -MD -MP -MF $(TARGET).elf.d

CONLYFLAGS += -Wnested-externs 
CONLYFLAGS += -std=gnu99

LDFLAGS = -nostartfiles -Wl,-Map=$(TARGET).map,--cref,--gc-sections -L./ -lc  -lm  -lc -lgcc -T.//STM32F10x_128k_20k_flash.ld

# Define programs and commands.
CC      = $(TCHAIN_PREFIX)gcc
CPP     = $(TCHAIN_PREFIX)g++
AR      = $(TCHAIN_PREFIX)ar
OBJCOPY = $(TCHAIN_PREFIX)objcopy
OBJDUMP = $(TCHAIN_PREFIX)objdump
SIZE    = $(TCHAIN_PREFIX)size
NM      = $(TCHAIN_PREFIX)nm
REMOVE  = $(REMOVE_CMD) -f
SHELL   = sh
###COPY    = cp


# Define Messages
# English
MSG_LOAD_FILE = Creating load file:
MSG_EXTENDED_LISTING = Creating Extended Listing/Disassembly:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = ---- Linking :
MSG_CLEANING = Cleaning project:
MSG_ASMFROMC = "Creating asm-File from C-Source:"

# List of all source files.
ALLSRC     =  $(SRC)
# List of all source files without directory and file-extension.
ALLSRCBASE = $(notdir $(basename $(ALLSRC)))

# Define all object files.
#ALLOBJ = $(addprefix $(OUTDIR)/, $(addsuffix .o, $(ALLSRCBASE)))
ALLOBJ = $(addsuffix .o, $(ALLSRCBASE))


# Default target.
all: createdirs build

elf: $(TARGET).elf
lss: $(TARGET).lss 
sym: $(TARGET).sym
hex: $(TARGET).hex
bin: $(TARGET).bin


build: elf hex bin lss sym

# Create output directories.
createdirs:
	-@md $(OUTDIR) >NUL 2>&1 || echo "" >NUL
	-@md $(OUTDIR)\dep >NUL 2>&1 || echo "" >NUL

# Create final output file (.hex) from ELF output file.
%.hex: %.elf
	@echo $(MSG_LOAD_FILE) $@
	$(OBJCOPY) -O ihex $< $@
	
# Create final output file (.bin) from ELF output file.
%.bin: %.elf
	@echo $(MSG_LOAD_FILE) $@
	$(OBJCOPY) -O binary $< $@

# Create extended listing file/disassambly from ELF output file.
# using objdump testing: option -C
%.lss: %.elf
	@echo $(MSG_EXTENDED_LISTING) $@
	$(OBJDUMP) -h -S -C -r $< > $@
#	$(OBJDUMP) -x -S $< > $@

# Create a symbol table from ELF output file.
%.sym: %.elf
	@echo $(MSG_SYMBOL_TABLE) $@
	$(NM) -n $< > $@

# Link: create ELF output file from object files.
.SECONDARY : $(TARGET).elf
.PRECIOUS : $(ALLOBJ)
%.elf:  $(ALLOBJ)
	@echo $(MSG_LINKING) $@
	$(CC) $(THUMB) $(CFLAGS) $(ALLOBJ) --output $@ $(LDFLAGS)

# Compile: create object files from C source files.
define COMPILE_C_TEMPLATE
$(notdir $(basename $(1))).o : $(1)
	@echo $(MSG_COMPILING) $$< to $$@
	$(CC) -c $(THUMB) $$(CFLAGS) $$(CONLYFLAGS) $$< -o $$@ 
endef
$(foreach src, $(SRC), $(eval $(call COMPILE_C_TEMPLATE, $(src)))) 


# Compile: create assembler files from C source files. ARM/Thumb
$(SRC:.c=.s) : %.s : %.c
	@echo $(MSG_ASMFROMC) $< to $@
	$(CC) $(THUMB) -S $(CFLAGS) $(CONLYFLAGS) $< -o $@

###################################################################################################
###################################################################################################
###################################################################################################
###################################################################################################
###################################################################################################
# Define all listing files (used for make clean).
LSTFILES   = $(addsuffix .lst, $(ALLSRCBASE))
# Define all depedency-files (used for make clean).
DEPFILES   = $(addsuffix .o.d, $(ALLSRCBASE))


# Target: clean project.
clean: clean_list

clean_list :
	@echo $(MSG_CLEANING)
	$(REMOVE) $(TARGET).map
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(TARGET).elf.d
	$(REMOVE) $(TARGET).hex
	$(REMOVE) $(TARGET).bin
	$(REMOVE) $(TARGET).sym
	$(REMOVE) $(TARGET).lss
	$(REMOVE) $(ALLOBJ)
	$(REMOVE) $(LSTFILES)
	$(REMOVE) $(DEPFILES)
	$(REMOVE) $(SRC:.c=.s)

# Create object files directory
##$(shell mkdir $(OBJDIR) 2>/dev/null)

# Include the dependency files.
##-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)
-include $(wildcard dep/*)

# Listing of phony targets.
.PHONY : all finish \
build elf hex bin lss sym clean clean_list createdirs

