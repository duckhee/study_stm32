//----------------------------------------------------------------------------
//    프로그램명 	: CDS  관련 함수
//
//    만든이     	: Cho Han Cheol
//
//    날  짜     	: 2013.10.14.
//    
//    최종 수정  	:
//
//    MPU_Type	:
//
//    파일명     	: Hw_Cds.c
//----------------------------------------------------------------------------


//----- 헤더파일 열기
//
#define  HW_CDS_LOCAL

#include "Hw_Cds.h"








/*---------------------------------------------------------------------------
     TITLE   : Hw_Cds_Init
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Hw_Cds_Init( void )
{

}





/*---------------------------------------------------------------------------
     TITLE   : Hw_Cds_GetData
     WORK    :
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
u16 Hw_Cds_GetData( void )
{
	u16 AdcValue;
	u16 RetValue;

	AdcValue = Hw_Adc_GetData(7);

	RetValue = AdcValue * HW_CDS_MAX_LIMIT / HW_ADC_MAX_LIMIT;

	return RetValue;
}

