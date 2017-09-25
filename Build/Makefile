
PREFIX = arm-none-eabi-
REMOVE_CMD = rm
#start file
STARTUP_C = Hw_startup.c
#target file
TARGET = main
#build folder
OUTDIR = ./Build
#extra header folder
EXTRAINCDIRS = ../LIB              \
               ../LIB_AP/Ap_Core   \
               ../LIB_AP/Ap_Lib    \
               ../LIB_HW           \
               ../LIB_HW/Hw_Core   \
	           ../LIB_HW/Hw_Lib    \
	           ../Main

SRC_AP = ../Main/main.c

SRC_HW = ../LIB_HW/$(STARTUP_C)    \
         ../LIB_HW/Hw_Adc.c        \
		 ../LIB_HW/Hw_Dma.c        \
		 ../LIB_HW/Hw_Gpio.c       \
		 ../LIB_HW/Hw_I2c.c        \
		 ../LIB_HW/Hw_Pwm.c        \
		 ../LIB_HW/Hw_Systick.c    \
		 ../LIB_HW/Hw.c            \

		 ../LIB_HW/Hw_Lib/Hw_Led.c \


SRC_LB = ../LIB/Ld_Printf.c        \
         ../LIB/Util.c

#source file 
SRC = $(SRC_AP) $(SRC_LB) $(SRC_HW)
#thumb mode
THUMB = -mthumb
#include header
INCLUDE = -I./include -I.

#C compiler option
CC = $(PREFIX)gcc
CPP = $(PREFIX)g++
OBJCOPY = $(PREFIX)objcopy
OBJDUMP = $(PREFIX)objdump
OBJNM = $(PREFIX)nm
SIZE = $(PREFIX)size
REMOVE = $(REMOVE_CMD) -rf

CFLAGS  = -gdwarf-2 -O2 -mcpu=cortex-m3 -mthumb-interwork -DSTM32F10X_MD 
#CFLAGS += $(INCLUDE) -mlong-calls -ffunction-sections -fdata-sections -fpromote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls 
CFLAGS += $(INCLUDE) -mlong-calls -ffunction-sections -fdata-sections -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls 
CFLAGS += -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=start_stm32f10x.lst -MD -MP -MF $(TARGET).elf.d
CFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))
#무엇인지 확인
CONLYFLAGS += -Wnested-externs 
CONLYFLAGS += -std=gnu99
#이게 맞는지?
LDFLAGS = -static -nostdlib -nostartfiles -Wl,-Map=$(TARGET).map,--cref,--gc-sections -L./ -lc  -lm  -lc -lgcc -T.//stm32f10x.ld
ELF32_LDFLAGS = -Wl,-T,stm32f10x.ld