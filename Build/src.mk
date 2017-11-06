

SRC_LB = ../LIB/Ld_Printf.c                \
         ../LIB/Util.c
         
SRC_AP = ../LIB_AP/Ap_Core/Get_clock.c      \
         ../Main/main.c                     \

SRC_HW = ../LIB_HW/Hw_Core/$(STARTUP_C)    \
		 ../LIB_HW/Hw_Core/Hw.c            \
		 ../LIB_HW/Hw_Core/Hw_Gpio.c       \
		 ../LIB_HW/Hw_Core/Hw_Usart.c      \
		 ../LIB_HW/Hw_Core/Hw_HSE.c        \
		 ../LIB_HW/Hw_Core/Hw_NVIC.c       \
		 ../LIB_HW/Hw_Lib/Hw_Led.c         \
		 ../LIB_HW/Hw_Lib/Hw_Key.c         \
         ../LIB_HW/Hw_Lib/Hw_Segment.c     \

SRC_MENU = ../Menu/Key_Menu.c              \
           ../Menu/Led_Menu.c              \
		   ../Menu/Segment_Menu.c          \
