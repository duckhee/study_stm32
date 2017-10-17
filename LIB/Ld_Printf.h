#ifndef __LSTRING_H__
#define __LSTRING_H__

#include "Ap.h"

 #ifdef LDSTRING_LOCAL
 #define LDSTRING_DEF
 #else
 #define LDSTRING_DEF        extern
 #endif

 
#define USART1_BASE					0x40013800
#define USART1_SR					(*(volatile unsigned long *)(USART1_BASE + 0x0000))
#define USART1_DR					(*(volatile unsigned long *)(USART1_BASE + 0x0004))
#define USART1_BRR					(*(volatile unsigned long *)(USART1_BASE + 0x0008))
#define USART1_CR1					(*(volatile unsigned long *)(USART1_BASE + 0x000C))
#define USART1_CR2					(*(volatile unsigned long *)(USART1_BASE + 0x0010))
#define USART1_CR3					(*(volatile unsigned long *)(USART1_BASE + 0x0014))
#define USART1_GTPR					(*(volatile unsigned long *)(USART1_BASE + 0x0018))



 LDSTRING_DEF void printf(char *fmt, ...);
 LDSTRING_DEF char check_byte(char *key);
 LDSTRING_DEF char get_byte(void);

#endif