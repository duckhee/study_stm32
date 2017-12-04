//----------------------------------------------------------------------------
//    프로그램명 	: I2C IMU 관련 함수
//
//    만든이     	: 
//
//    날  짜     	: 
//    
//    최종 수정  	:
//
//    MPU_Type		:
//
//    파일명     	: Hw_I2C_IMU.c
//----------------------------------------------------------------------------


//----- 헤더파일 열기
//
#define  HW_I2C_IMU_LOCAL


#include "Hw_I2C_IMU.h"
#include "Lb_Printf.h"

//-- I2C
//
#define I2C1_BASE					0x40005400
#define I2C1_CR1					(*(volatile unsigned long *)(I2C1_BASE + 0x0000))
#define I2C1_CR2					(*(volatile unsigned long *)(I2C1_BASE + 0x0004))
#define I2C1_OAR1					(*(volatile unsigned long *)(I2C1_BASE + 0x0008))
#define I2C1_OAR2					(*(volatile unsigned long *)(I2C1_BASE + 0x000C))
#define I2C1_DR						(*(volatile unsigned long *)(I2C1_BASE + 0x0010))
#define I2C1_SR1					(*(volatile unsigned long *)(I2C1_BASE + 0x0014))
#define I2C1_SR2					(*(volatile unsigned long *)(I2C1_BASE + 0x0018))
#define I2C1_CCR					(*(volatile unsigned long *)(I2C1_BASE + 0x001C))
#define I2C1_TRISE				(*(volatile unsigned long *)(I2C1_BASE + 0x0020))

#define AFIO_MAPR					(*(volatile unsigned long *)(0x40010000 + 0x0004))

#define RCC_APB1ENR			  (*(volatile unsigned long *)(0x40021000 + 0x001C))

#define GPIOB_CRH					(*(volatile unsigned long *)(0x40010C00 + 0x0004))


#define HW_I2C_ERR_NONE		0
#define HW_I2C_ERR_TIMEOUT	1
#define HW_I2C_ERR_START	2
#define HW_I2C_ERR_ADDR		3
#define HW_I2C_ERR_TXE		4
#define HW_I2C_ERR_RXE		5
#define HW_I2C_ERR_STOP		6


void Hw_I2C_IMU_IO_Setup( void );
u16  Hw_I2C_IMU_WaitForBitSet( u32 *reg_addr, u32 reg_bit, u32 time_out );
u16  Hw_I2C_IMU_GetErrStatus( void );


/*---------------------------------------------------------------------------
     TITLE   : Hw_I2C_SW_Init
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Hw_I2C_HW_Init( void )
{
	u32 SR;


	//-- I/O 초기화
	//
	Hw_I2C_HW_IO_Setup();	


	I2C1_CR1 = 0;

	//-- 1. I2C 클럭 입력 주파수 설정 
	//
	I2C1_CR2 = 0 
				| ( 36 << 0 );		// FREQ = 36Mhz

	//-- 2. Clock Control 
	//
//	I2C1_CCR = 0 
//				| (  1 << 15 )		// Fast Mode I2C
//				| (  0 << 14 )		// Duty Tlow/Thig = 2
//				| ( 30 <<  0 );		// 30*27ns + 2*30*27ns = 400Khz

	//-- 3. Maximum Rise Time  
	//
	I2C1_TRISE = 4;				// 300ns / 100ns + 1 = 4 


	//-- Clock Enable
	//
	RCC_APB1ENR |= (1<<21);		// I2C1 Clock enable


	I2C1_CR1 &= ~(0x01 << 1);      // CLR_BIT( REG_I2C1_CR1, 1 );		// I2C Mode		
	I2C1_CR1 |=   0x01 << 0;       //	SET_BIT( REG_I2C1_CR1, 0 );		// Peripheral enable	

	SR = REG_I2C1_SR1;
	SR = REG_I2C1_SR2;
	
	//-- 2. Clock Control 
	//
	I2C1_CCR = 0 
				| (  1 << 15 )		// Fast Mode I2C
				| (  0 << 14 )		// Duty Tlow/Thig = 2
				| ( 30 <<  0 );		// 30*27ns + 2*30*27ns = 400Khz
}



/*---------------------------------------------------------------------------
     TITLE   : Hw_I2C_IMU_Init
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Hw_I2C_IMU_Init( void )
{
	u32 SR;


	//-- I/O 초기화
	//
//	Hw_I2C_IMU_IO_Setup();	


//	I2C1_CR1 = 0;

	//-- 1. I2C 클럭 입력 주파수 설정 
	//
//	I2C1_CR2 = 0 
//				| ( 36 << 0 );		// FREQ = 36Mhz

	//-- 2. Clock Control 
	//
//	I2C1_CCR = 0 
//				| (  1 << 15 )		// Fast Mode I2C
//				| (  0 << 14 )		// Duty Tlow/Thig = 2
//				| ( 30 <<  0 );		// 30*27ns + 2*30*27ns = 400Khz

	//-- 3. Maximum Rise Time  
	//
//	I2C1_TRISE = 11;			// 300ns / 28ns + 1 = 11 


	//-- Clock Enable
	//
//	RCC_APB1ENR |= (1<<21);		// I2C1 Clock enable


//	I2C1_CR1 &= ~(0x01 << 1);      //CLR_BIT( I2C1_CR1, 1 );		// I2C Mode		
//	I2C1_CR1 |=   0x01 << 0;       //SET_BIT( I2C1_CR1, 0 );		// Peripheral enable	

//	SR = I2C1_SR1;
//	SR = I2C1_SR2;


//	power_on = TRUE;
}





/*---------------------------------------------------------------------------
     TITLE   : Hw_I2C_IMU_IO_Setup
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Hw_I2C_IMU_IO_Setup( void )
{

	//-- I2C1 Remap
	//
	AFIO_MAPR |=   0x01 << 1;         // SET_BIT( REG_AFIO_MAPR, 1 );	// SCL/PB8, SDA/PB9)

	//-- SCL PB.8
	//
	GPIOB_CRH &= ~(0x0F << ( 0));	// Clear
	GPIOB_CRH |=  (0x03 << ( 0));	// MODE, PB.8 Output mode, max speed 50Mhz
	GPIOB_CRH |=  (0x03 << ( 2));	// CNF,  PB.8 Alternate function output Open-drain	

	//-- SDA PB.9
	//
	GPIOB_CRH &= ~(0x0F << ( 4));	// Clear
	GPIOB_CRH |=  (0x03 << ( 4));	// MODE, PB.9 Output mode, max speed 50Mhz
	GPIOB_CRH |=  (0x03 << ( 6));	// CNF,  PB.9 Alternate function output Open-drain	
}







/*---------------------------------------------------------------------------
     TITLE   : Hw_I2C_IMU_WriteRegs
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
u16 Hw_I2C_IMU_WriteRegs( u16 i2c_addr, u8 reg_addr, u8 *ptr_data, u16 len )
{
    u16 Ret = 0;
    u16 Err = 0;
    u8  i;
    u32 TimeOut;
    u32 SR1;
    u32 SR2;


    while(1)
    {
        //-- START
        //
        I2C1_CR1 |=   0x01 << 8;     // SET_BIT( I2C1_CR1, 8 );

#if 0
        Ret = Hw_I2C_IMU_WaitForBitSet( (u32 *)&I2C1_SR1, 0, 10000 );
        if( Ret != 0 )
        {
            Err = HW_I2C_ERR_START;
            break;
        }
#endif
    Ret = 10000;
    while(Ret--)
    {
        if(I2C1_SR1 & (0x01 << 0)) break;
    }
    if(Ret == 0)
    {
				Err = HW_I2C_ERR_START;
				break;
    }

        //Lb_printf("S1 %x\n", I2C1_SR1);
        //Lb_printf("S1 %x\n", I2C1_SR2);

        //-- ADDR
        //
        I2C1_DR = i2c_addr<<1;	// ADDR Write 

#if 0
        Ret = Hw_I2C_IMU_WaitForBitSet( (u32 *)&I2C1_SR1, 1, 10000 );	// ADDR Sent
        SR2 = I2C1_SR2;

        if( Ret != 0 ) 
        {
            Err = HW_I2C_ERR_ADDR;
            break;
        }
#endif
    Ret = 10000;
    while(Ret--)
    {
        if(I2C1_SR1 & (0x01 << 1)) break;
    }
    SR2 = I2C1_SR2;
    if(Ret == 0)
    {
				Err = HW_I2C_ERR_ADDR;
				break;
    }


        //Lb_printf("S2 %x\n", I2C1_SR1);
        //Lb_printf("S2 %x\n", I2C1_SR2);
				
#if 0
        Ret = Hw_I2C_IMU_WaitForBitSet( (u32 *)&I2C1_SR1, 7, 10000 );	// TXE
        if( Ret != 0 )
        			{
            Err = HW_I2C_ERR_TXE;
            break;
        }
#endif
    Ret = 10000;
    while(Ret--)
    {
        if(I2C1_SR1 & (0x01 << 7)) break;
    }
    if(Ret == 0)
    {
				Err = HW_I2C_ERR_TXE;
				break;
    }


#if 0
        Ret = Hw_I2C_IMU_WaitForBitSet( (u32 *)&I2C1_SR1, 7, 10000 );	// TXE
        if( Ret != 0 )
        {
            Err = HW_I2C_ERR_TXE;
            break;
        }
#endif
    Ret = 10000;
    while(Ret--)
    {
        if(I2C1_SR1 & (0x01 << 7)) break;
    }
    if(Ret == 0)
    {
				Err = HW_I2C_ERR_TXE;
				break;
    }

        I2C1_DR = reg_addr;	



        for( i=0; i<len; i++ )
        {
#if 0
            Ret = Hw_I2C_IMU_WaitForBitSet( (u32 *)&I2C1_SR1, 7, 10000 );	// TXE
            if( Ret != 0 )
            {
                Err = HW_I2C_ERR_TXE;
                break;
            }
#endif
    Ret = 10000;
    while(Ret--)
    {
        if(I2C1_SR1 & (0x01 << 7)) break;
    }
    if(Ret == 0)
    {
				Err = HW_I2C_ERR_TXE;
				break;
    }

            I2C1_DR = ptr_data[i];						
        }


        //-- STOP
        //
        if( len > 0 )
        {
#if 0
            Ret = Hw_I2C_IMU_WaitForBitSet( (u32 *)&I2C1_SR1, 2, 10000 );	// BTF
            if( Ret != 0 ) 
            {
                Err = HW_I2C_ERR_STOP;
                break;
            }
#endif
    Ret = 10000;
    while(Ret--)
    {
        if(I2C1_SR1 & (0x01 << 2)) break;
    }
    if(Ret == 0)
    {
				Err = HW_I2C_ERR_STOP;
				break;
    }
        }

        I2C1_CR1 |=   0x01 << 9;     // SET_BIT( I2C1_CR1, 9 );	// STOP
        break;
    }


    if( Err == 0 )
    {
        Err = Hw_I2C_IMU_GetErrStatus();
    }
	

    return Err;
}





/*---------------------------------------------------------------------------
     TITLE   : Hw_I2C_IMU_ReadRegs
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
u16 Hw_I2C_IMU_ReadRegs( u16 i2c_addr, u8 reg_addr, u8 *ptr_reg, u16 len )
{
    u16 Ret = 0;
    u16 Err = 0;
	u8  i;
	u32 TimeOut;
	volatile u32 SR1;
	volatile u32 SR2;
	u8  LastIndex = 0;


	if( len > 0 ) LastIndex = len - 1;


	while(1)
	{

			//Lb_printf("C1 %x\n", I2C1_CR1);

			SR1 = I2C1_SR1;
			SR2 = I2C1_SR2;


			//Lb_printf("S1 %x\n", I2C1_SR1);
			//Lb_printf("S1 %x\n", I2C1_SR2);

			//-- START
			//
			I2C1_CR1 |=   0x01 << 8;     // SET_BIT( I2C1_CR1, 8 );

#if 0
			Ret = Hw_I2C_IMU_WaitForBitSet( (u32 *)&I2C1_SR1, 0, 10000 );

			//Lb_printf("S1 %x\n", I2C1_SR1);
			//Lb_printf("S1 %x\n", I2C1_SR2);

			if( Ret != 0 )
			{
				Err = HW_I2C_ERR_START;
				break;
			}
#endif
    Ret = 10000;
    while(Ret--)
    {
        if(I2C1_SR1 & (0x01 << 0)) break;
    }
    if(Ret == 0)
    {
				Err = HW_I2C_ERR_START;
				break;
    }


#if 0
			Ret = Hw_I2C_IMU_WaitForBitSet( (u32 *)&I2C1_SR2, 0, 10000 );
			if( Ret != 0 ) 
			{
				Err = HW_I2C_ERR_START;
				break;
			}
#endif
    Ret = 10000;
    while(Ret--)
    {
        if(I2C1_SR2 & (0x01 << 0)) break;
    }
    if(Ret == 0)
    {
				Err = HW_I2C_ERR_START;
				break;
    }



			//-- ADDR
			//
			I2C1_DR = i2c_addr<<1;	// ADDR Write 

#if 0
			Ret = Hw_I2C_IMU_WaitForBitSet( (u32 *)&I2C1_SR1, 1, 10000 );	// ADDR Sent
			SR2 = I2C1_SR2;

			if( Ret != 0 ) 
			{
				Err = HW_I2C_ERR_ADDR;
				break;
			}
#endif
    Ret = 10000;
    while(Ret--)
    {
        if(I2C1_SR1 & (0x01 << 1)) break;
    }
    SR2 = I2C1_SR2;
    if(Ret == 0)
    {
				Err = HW_I2C_ERR_START;
				break;
    }

			
#if 0
			Ret = Hw_I2C_IMU_WaitForBitSet( (u32 *)&I2C1_SR1, 7, 10000 );	// TXE
			if( Ret != 0 )
			{
				Err = HW_I2C_ERR_TXE;
				break;
			}
#endif
    Ret = 10000;
    while(Ret--)
    {
        if(I2C1_SR1 & (0x01 << 7)) break;
    }
    if(Ret == 0)
    {
				Err = HW_I2C_ERR_TXE;
				break;
    }


#if 0
			Ret = Hw_I2C_IMU_WaitForBitSet( (u32 *)&I2C1_SR1, 7, 10000 );	// TXE
			if( Ret != 0 )
			{
				Err = HW_I2C_ERR_TXE;
				break;
			}
#endif
    Ret = 10000;
    while(Ret--)
    {
        if(I2C1_SR1 & (0x01 << 7)) break;
    }
    if(Ret == 0)
    {
				Err = HW_I2C_ERR_TXE;
				break;
    }

			I2C1_DR = reg_addr;						


#if 0
			Ret = Hw_I2C_IMU_WaitForBitSet( (u32 *)&I2C1_SR1, 2, 10000 );	// BTF
			if( Ret != 0 ) 
			{
				Err = HW_I2C_ERR_STOP;
				break;
			}
#endif
    Ret = 10000;
    while(Ret--)
    {
        if(I2C1_SR1 & (0x01 << 2)) break;
    }
    if(Ret == 0)
    {
				Err = HW_I2C_ERR_STOP;
				break;
    }



			//-- START
			//
			I2C1_CR1 |=   0x01 << 8;     // SET_BIT( I2C1_CR1, 8 );

#if 0
			Ret = Hw_I2C_IMU_WaitForBitSet( (u32 *)&I2C1_SR1, 0, 10000 );
			if( Ret != 0 )
			{
				Err = HW_I2C_ERR_START;
				break;
			}
#endif
    Ret = 10000;
    while(Ret--)
    {
        if(I2C1_SR1 & (0x01 << 0)) break;
    }
    if(Ret == 0)
    {
				Err = HW_I2C_ERR_START;
				break;
    }


			//-- ADDR
			//
			I2C1_DR = (i2c_addr<<1) | (1<<0) ;	// ADDR Read

#if 0
			Ret = Hw_I2C_IMU_WaitForBitSet( (u32 *)&I2C1_SR1, 1, 10000 );	// ADDR Sent
			SR2 = I2C1_SR2;

			if( Ret != 0 ) 
			{
				Err = HW_I2C_ERR_ADDR;
				break;
			}
#endif
    Ret = 10000;
    while(Ret--)
    {
        if(I2C1_SR1 & (0x01 << 1)) break;
    }
    SR2 = I2C1_SR2;
    if(Ret == 0)
    {
				Err = HW_I2C_ERR_ADDR;
				break;
    }


			//-- Read DATA
			//
			for( i=0; i<len; i++ )
			{
				if( i < LastIndex )
				{
					I2C1_CR1 |=   0x01 << 10;     // SET_BIT( I2C1_CR1, 10 );	// ACK Enable					
				}
				else
				{
					I2C1_CR1 &= ~(0x01 << 10);        // CLR_BIT( I2C1_CR1, 10 );	// ACK Disable
					I2C1_CR1 |=   0x01 << 9;          // SET_BIT( I2C1_CR1, 9 );	// STOP
				}


#if 0
				Ret = Hw_I2C_IMU_WaitForBitSet( (u32 *)&I2C1_SR1, 6, 10000 );
				if( Ret == 0 )
				{
					ptr_reg[i] = I2C1_DR;
				}
				else
				{
					Err = HW_I2C_ERR_RXE;
					break;
				}					 		
#endif
    Ret = 10000;
    while(Ret--)
    {
        if(I2C1_SR1 & (0x01 << 6)) break;
    }
    if(Ret == 0)
    {
				Err = HW_I2C_ERR_RXE;
				break;
    }
    else
				ptr_reg[i] = I2C1_DR;
       
			}

			break;
	}


	if( Err == 0 )
	{
		Err = Hw_I2C_IMU_GetErrStatus();
	}
	

    return Err;

}


/*---------------------------------------------------------------------------
     TITLE   : Hw_I2C_IMU_WaitForBitSet
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
u16 Hw_I2C_IMU_WaitForBitSet( u32 *reg_addr, u32 reg_bit, u32 time_out )
{
	u32 Ret = 0;
	volatile u32 Reg;


	while( time_out )
	{
		Reg = *reg_addr;

		if( IS_SET_BIT( Reg, reg_bit ) ) break;

		time_out--;
	}
			
	if( time_out == 0 ) 
	{
		Ret = HW_I2C_ERR_TIMEOUT;
	}

	return Ret;
}





/*---------------------------------------------------------------------------
     TITLE   : Hw_I2C_IMU_GetErrStatus
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
u16 Hw_I2C_IMU_GetErrStatus( void )
{
	u16 Err = 0;

	if( IS_SET_BIT(I2C1_SR1, 11) ) Err = 11;
	if( IS_SET_BIT(I2C1_SR1, 10) ) Err = 10;
	if( IS_SET_BIT(I2C1_SR1,  9) ) Err =  9;
	if( IS_SET_BIT(I2C1_SR1,  8) ) Err =  8;

	return Err;
}






//----------------------------------------------------------------------------
//    프로그램명 	: I2C MPU6050 관련 함수
//
//    만든이     	: 
//
//    날  짜     	: 
//    
//    최종 수정  	:
//
//    MPU_Type		:
//
//    파일명     	: Hw_MPU6050.c
//----------------------------------------------------------------------------


//----- 헤더파일 열기
//


#include "Lb_Printf.h"




typedef struct
{
	u8	X_Acc_H;
	u8	X_Acc_L;
	u8	Y_Acc_H;
	u8	Y_Acc_L;
	u8	Z_Acc_H;
	u8	Z_Acc_L;

	u8	Temp_H;
	u8	Temp_L;

	u8	X_Gyro_H;
	u8	X_Gyro_L;
	u8	Y_Gyro_H;
	u8	Y_Gyro_L;
	u8	Z_Gyro_H;
	u8	Z_Gyro_L;

} HW_MPU6050_RAW_DATA_OBJ;



/*---------------------------------------------------------------------------
     TITLE   : Hw_MPU6050_Init
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
u8 Hw_MPU6050_Init( void )
{
	u8  Ret = TRUE;
	u16 Err = 0;
	u8  RegData[20];



	//-- I2C 초기화
	//
//	Hw_I2C_IMU_Init();	


	while(1)
	{

		//Err = Hw_I2C_IMU_MPU6050_ReadReg( MPU6050_RA_WHO_AM_I, RegData );
    Err = Hw_I2C_IMU_ReadRegs( HW_I2C_IMU_ADDR_MPU6050, MPU6050_RA_WHO_AM_I, RegData, 1 );
		if( Err != 0 )
		{
			Lb_printf("Can't find MPU6050 \n");
			break;
		}

    RegData[0] = 0x00;
		//Err = Hw_I2C_IMU_MPU6050_WriteReg( MPU6050_RA_PWR_MGMT_1, 0x00 );	// 내부 오실레이터, SLEEP = 0
    Err = Hw_I2C_IMU_WriteRegs( HW_I2C_IMU_ADDR_MPU6050, MPU6050_RA_PWR_MGMT_1, RegData, 1 );

		if( Err != 0 )
		{
			Lb_printf("Err write MPU6050_RA_PWR_MGMT_1 : %d\n", Err);
			break;
		}

		break;
	}


	if( Err != 0 ) Ret = FALSE;


	return Ret;
}





/*---------------------------------------------------------------------------
     TITLE   : Hw_MPU6050_GetData
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
u16 Hw_MPU6050_GetData( HW_MPU6050_DATA_OBJ *ptr_data )
{
	u16 Err;
	s16 Temp;

	HW_MPU6050_RAW_DATA_OBJ raw_data;


//	Err = Hw_I2C_IMU_MPU6050_ReadRegs( MPU6050_RA_ACCEL_XOUT_H, (u8 *)&raw_data, 14 );
	Err = Hw_I2C_IMU_ReadRegs( HW_I2C_IMU_ADDR_MPU6050, MPU6050_RA_ACCEL_XOUT_H, (u8 *)&raw_data, 14 );

	if( Err == 0 )
	{
		ptr_data->X_Acc = (s16)((raw_data.X_Acc_H<<8) | (raw_data.X_Acc_L<<0));	
		ptr_data->Y_Acc = (s16)((raw_data.Y_Acc_H<<8) | (raw_data.Y_Acc_L<<0));	
		ptr_data->Z_Acc = (s16)((raw_data.Z_Acc_H<<8) | (raw_data.Z_Acc_L<<0));	

		ptr_data->X_Gyro = (s16)((raw_data.X_Gyro_H<<8) | (raw_data.X_Gyro_L<<0));	
		ptr_data->Y_Gyro = (s16)((raw_data.Y_Gyro_H<<8) | (raw_data.Y_Gyro_L<<0));	
		ptr_data->Z_Gyro = (s16)((raw_data.Z_Gyro_H<<8) | (raw_data.Z_Gyro_L<<0));	

		Temp = (s16)((raw_data.Temp_H<<8) | (raw_data.Temp_L<<0));	
		Temp = Temp/340 + 36;
		ptr_data->Temp = Temp;
	}

	return Err;
}
