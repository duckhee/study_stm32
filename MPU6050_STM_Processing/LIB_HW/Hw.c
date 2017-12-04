//----------------------------------------------------------------------------
//    프로그램명 	: Hw 관련 함수
//
//    만든이     	: 
//
//    날  짜     	: 
//    
//    최종 수정  	:
//
//    MPU_Type		:
//
//    파일명     	: Hw.c
//----------------------------------------------------------------------------


//----- 헤더파일 열기
//
#define  HW_LOCAL  

#include "Hw.h"





/*---------------------------------------------------------------------------
     TITLE   : Hw_I2C_SW_IO_Setup
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Hw_I2C_HW_IO_Setup( void )
{

	//-- I2C1 Remap
	//
	SET_BIT( REG_AFIO_MAPR, 1 );	// SCL/PB8, SDA/PB9)


	//-- SCL PB.8
	//
	REG_GPIOB_CRH &= ~(0x0F << ( 0));	// Clear
	REG_GPIOB_CRH |=  (0x03 << ( 0));	// MODE, PB.8 Output mode, max speed 50Mhz
	REG_GPIOB_CRH |=  (0x03 << ( 2));	// CNF,  PB.8 Alternate function output Open-drain	


	//-- SDA PB.9
	//
	REG_GPIOB_CRH &= ~(0x0F << ( 4));	// Clear
	REG_GPIOB_CRH |=  (0x03 << ( 4));	// MODE, PB.9 Output mode, max speed 50Mhz
	REG_GPIOB_CRH |=  (0x03 << ( 6));	// CNF,  PB.9 Alternate function output Open-drain	
}







/*---------------------------------------------------------------------------
     TITLE   : Hw_Init
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Hw_Init( void )
{
	//-- PLL 설정
	//
	Hw_PLL_Init();
	
	
	//-- 인터럽트 관련 초기화
	//
	Hw_ISR_Init();
	
		
	//-- GPIO 기본값 설정
	//
	REG_GPIOA_CRL = 0x33333333;	// PA0 - 7
	REG_GPIOA_CRH = 0x333334B3;	// PA8 - 15    //PA9,10,11,12는 가각 UART, USB에 할당됨
	REG_GPIOB_CRL = 0x33333333;	// PB0 - 7
	REG_GPIOB_CRH = 0x33333333;	// PB8 - 15
	REG_GPIOC_CRH = 0x33444444;	// PC14, 15
	
	Hw_Uart_Init();
	
	
	Hw_I2C_HW_Init();
	Hw_MPU6050_Init();
}




/*---------------------------------------------------------------------------
     TITLE   : Hw_Wait
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Hw_Wait( u32 delay )
{
    volatile u32 i;
    for ( i = 0 ; i < delay ; i++ ){ };
}





/*---------------------------------------------------------------------------
     TITLE   : Hw_Wait_Usec
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Hw_Wait_Usec( u32 usec )
{
    Hw_Wait( usec * 6 );
}





/*---------------------------------------------------------------------------
     TITLE   : Hw_Wait_us
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Hw_Wait_us( u32 usec )
{
    Hw_Wait_Usec( usec );
}





/*---------------------------------------------------------------------------
     TITLE   : Hw_Wait_ms
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Hw_Wait_ms( u32 msec )
{
    Hw_Wait_Usec( msec*1000 );
}
















 
