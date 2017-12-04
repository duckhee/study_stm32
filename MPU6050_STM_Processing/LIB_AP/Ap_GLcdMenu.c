//----------------------------------------------------------------------------
//    프로그램명 	: GLcd Menu 관련 함수
//
//    만든이     	: Cho Han Cheol
//
//    날  짜     	: 
//    
//    최종 수정  	: 
//
//    MPU_Type		:
//
//    파일명     	: Ap_GLcdMenu.h
//----------------------------------------------------------------------------



//----- 헤더파일 열기
//
#define  AP_GLCDMENU_LOCAL

#include "Ap_GLcdMenu.h"



#define POLYNOM1(x, a)  ((a)[1]*(x)+(a)[0])
#define POLYNOM2(x, a)  (POLYNOM1((x),(a)+1)*(x)+(a)[0])
#define POLYNOM3(x, a)  (POLYNOM2((x),(a)+1)*(x)+(a)[0])
#define POLYNOM4(x, a)  (POLYNOM3((x),(a)+1)*(x)+(a)[0])
#define M_PI_2          1.57

/*
double pow(double a, double n){
	double sum=1;
	double i;
	for(i =0 ; i<n ; i++){
		sum = sum*a;
	}
	return sum;
}
*/
double pow(double a, double n){
	return a*a;	
}


/*
double sqrt(double x){
	double xhalf = 0.5f * x;
	double i = 0x5f3759df - ((*(int*)&x)>>1);
	double y = *(double*)&i;
	y = y*(1.5f-y*y*xhalf);
	y = y*(1.5f-y*y*xhalf);
	return (x*y);
}
*/
double sqrt(double input)
{
	double x = 1;                                                         //임의의 수를 지정해도 하나로 수렴하는 수열임
	for (int i = 0; i<30; i++)
	x = (x + (input / x)) / 2;
	return x;
}


double abs(double n){
	if(n>0) return n;
	else return -n;
}


double atan(double x)
{
	static double p[] = {
		-0.13688768894191926929e+2,
		-0.20505855195861651981e+2,
		-0.84946240351320683534e+1,
		-0.83758299368150059274e+0
	};
	static double q[] = {
		0.41066306682575781263e+2,
		0.86157349597130242515e+2,
		0.59578436142597344465e+2,
		0.15024001160028576121e+2,
		1.0
	};
	static double a[] = {
		0.0,
		0.52359877559829887307710723554658381,  /* pi/6 */
		M_PI_2,
		1.04719755119659774615421446109316763   /* pi/3 */
	};

	int     neg = x < 0;
	int     n;
	double  g;

	if (neg) {
		x = -x;
	}
	if (x > 1.0) {
		x = 1.0/x;
		n = 2;
	}
	else    n = 0;

	if (x > 0.26794919243112270647) {       /* 2-sqtr(3) */
		n = n + 1;
		x = (((0.73205080756887729353*x-0.5)-0.5)+x)/
		(1.73205080756887729353+x);
	}

	g = x * x;
	x += x * g * POLYNOM3(g, p) / POLYNOM4(g, q);
	if (n > 1) x = -x;
	x += a[n];
	return neg ? -x : x;
}


  

//-- 내부 선언
//



//-- 내부 변수
//

  

//-- 내부 함수
//
void Ap_GLcdMenu_ShowMenu(void);


  



/*---------------------------------------------------------------------------
     TITLE   : Ap_GLcdMenu_ShowMenu
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Ap_GLcdMenu_ShowMenu(void)
{
	u8 key;

	Lb_printf("\n\n");
	Lb_printf("*******************************************************\n");
	Lb_printf("                      MPU6050                          \n");
	Lb_printf("*******************************************************\n");
	Lb_printf("* 1. LCD Clear                                        *\n");
	Lb_printf("* 2. Show Acc                                         *\n");
	Lb_printf("* 3. Show MPU6050 Regs                                *\n");
	Lb_printf("* 4.                                                  *\n");
	Lb_printf("* 5.                                                  *\n");
	Lb_printf("* 6.                                                  *\n");
	Lb_printf("* 7.                                                  *\n");
	Lb_printf("* 8.                                                  *\n");
	Lb_printf("* 9.                                                  *\n");
	Lb_printf("* m.  Menu                                            *\n");
	Lb_printf("*******************************************************\n");
	Lb_printf("\n");
}





/*---------------------------------------------------------------------------
     TITLE   : Ap_GLcdMenu_GetCmd
     WORK    : 
     ARG     : void
     RET     : 
				u8 : 눌려진 메뉴키 데이터 
---------------------------------------------------------------------------*/
u8 Ap_GLcdMenu_GetCmd(void)
{
	u8  key;
	

	Lb_printf(">> ");

    key=get_byte();
	
	Lb_printf("\n");
	
    return key;
}




double d_a;
double d_b;
double d_c;
double d_x;
double d_y;
double d_z;
short s_a;
short s_b;
short s_c;
short s_x;
short s_y;
short s_z;

double accel_x;
double accel_y;
double accel_z;




double dt = 0.012;

double gyro_angle_x;
double gyro_angle_y;
double gyro_angle_z;

double alpha = 0.96;
double angle_x;
double angle_y;
double angle_z;
double accel_angle_x;
double accel_angle_y;
double accel_angle_z;
double gyro_x;
double gyro_y;
double gyro_z;
double RADIANS_TO_DEGREES = 180/3.14159;
double FS_SEL = 131;


  double                x_accel = 0;
  double                 y_accel = 0;
  double                 z_accel = 0;
  double                 x_gyro = 0;
  double                 y_gyro = 0;
  double                 z_gyro = 0;
  double  base_x_accel ;
  double  base_y_accel ;
  double  base_z_accel ;
  double  base_x_gyro ;
  double  base_y_gyro ;
  double  base_z_gyro ;
  
  double unfiltered_gyro_angle_x;
  double unfiltered_gyro_angle_y;
  double unfiltered_gyro_angle_z;
  


/*---------------------------------------------------------------------------
     TITLE   : Ap_GLcdMenu_ExeCmd
     WORK    : 
     ARG     : void
     RET     : 
				u8 : 눌려진 메뉴키 데이터 
---------------------------------------------------------------------------*/
u8 Ap_GLcdMenu_ExeCmd(void)
{
	u8 key;
	u8 Status;
	static u8 ExeFirst = TRUE;
	u16 Ret;
	static u8  Count    = 0;	
	static s8  CircleX  = 0;	
	u8 I2C_Data[20];	
	s16 Temperature;	
	s16 x;
    s16 y;
    u16 i;
	

    HW_MPU6050_DATA_OBJ MPU6050_Data;
	
	  for (int i = 0; i < 10; i++) {
		  Ret = Hw_MPU6050_GetData( &MPU6050_Data );
		  x_accel += MPU6050_Data.X_Acc;
		  y_accel += MPU6050_Data.Y_Acc;
		  z_accel += MPU6050_Data.Z_Acc;
		  x_gyro += MPU6050_Data.X_Gyro;
		  y_gyro += MPU6050_Data.Y_Gyro;
		  z_gyro += MPU6050_Data.Z_Gyro;
		 
	  }
	  x_accel /= 10;
	  y_accel /= 10;
	  z_accel /= 10;
	  x_gyro /= 10;
	  y_gyro /= 10;
	  z_gyro /= 10;
	  
	    base_x_accel = x_accel;
	    base_y_accel = y_accel;
	    base_z_accel = z_accel;
	    base_x_gyro = x_gyro;
	    base_y_gyro = y_gyro;
	    base_z_gyro = z_gyro;
	
	


	if( ExeFirst == TRUE )
	{
		Ap_GLcdMenu_ShowMenu();		
	}

    while( (key = Ap_GLcdMenu_GetCmd()) != 0 )
    {
        switch(key)
        {
           case '1':
		   
               	break;

           case '2':
                
                while( get_byte_check() == 0 )
                {
                    Ret = Hw_MPU6050_GetData( &MPU6050_Data );

                    Lb_printf("AX %d ", MPU6050_Data.X_Acc );
                    Lb_printf("AY %d ", MPU6050_Data.Y_Acc );
                    Lb_printf("AZ %d ", MPU6050_Data.Z_Acc );
                    Lb_printf("T %d \n",  MPU6050_Data.Temp);

//                    Hw_Wait_ms(100);
                }
           		
				break;

           case '3':
				 Ret = Hw_MPU6050_GetData( &MPU6050_Data );
           		d_x = MPU6050_Data.X_Acc * MPU6050_Data.X_Acc;   
				Lb_printf("%d.%d \n",(short)d_x, (short)(d_x * 1000)%1000);  						
               break; 

           case '4':






               while( get_byte_check() == 0 )
                {
	                Ret = Hw_MPU6050_GetData( &MPU6050_Data );
/*
	                Lb_printf("AX %d ", MPU6050_Data.X_Acc );
	                Lb_printf("AY %d ", MPU6050_Data.Y_Acc );
	                Lb_printf("AZ %d ", MPU6050_Data.Z_Acc );
	                Lb_printf("T %d \n",  MPU6050_Data.Temp);
*/


//					MPU6050_Data.X_Acc = 10;
//					Lb_printf("MPU6050_Data.X_Acc : %d\n", MPU6050_Data.X_Acc);
//Lb_printf("s_x : %d\n", s_x);

//					s_x = MPU6050_Data.X_Acc;
//					s_x = 10;
//d_x = (double)s_x/3;
//d_x = (double)MPU6050_Data.X_Acc/3;
//Lb_printf("%d.%d \n",(short)d_x, (short)(d_x * 1000)%1000);

//s_y = 10;
//d_y = (double)s_y/3;
//Lb_printf("%d.%d \n",(short)d_y, (short)(d_y * 1000)%1000);

//s_z = 10;
//d_z = (double)s_z/3;
//Lb_printf("%d.%d \n",(short)d_z, (short)(d_z * 1000)%1000);



  accel_x = (double)MPU6050_Data.X_Acc;
  accel_y = (double)MPU6050_Data.Y_Acc;
  accel_z = (double)MPU6050_Data.Z_Acc;
  
  gyro_x = (MPU6050_Data.X_Gyro - base_x_gyro)/FS_SEL;
  gyro_y = (MPU6050_Data.Y_Gyro - base_y_gyro)/FS_SEL;
  gyro_z = (MPU6050_Data.Z_Gyro - base_z_gyro)/FS_SEL;
  
  
  gyro_angle_x = gyro_x*dt + x_gyro;
  gyro_angle_y = gyro_y*dt + y_gyro;
  gyro_angle_z = gyro_z*dt + z_gyro;
  
  unfiltered_gyro_angle_x = gyro_x*dt ;
  unfiltered_gyro_angle_y = gyro_y*dt ;
  unfiltered_gyro_angle_z = gyro_z*dt ;
  
  
 
  accel_angle_y = atan(-1*accel_x/sqrt(pow(accel_y,2) + pow(accel_z,2)))*RADIANS_TO_DEGREES;
  accel_angle_x = atan(accel_y/sqrt(pow(accel_x,2) + pow(accel_z,2)))*RADIANS_TO_DEGREES;
  accel_angle_z = 0;
  
  
//angle_x = alpha*gyro_angle_x + (1.0 - alpha)*accel_angle_x;
  
  angle_x = alpha*gyro_angle_x + (1.0 - alpha)*accel_angle_x;
  angle_y = alpha*gyro_angle_y + (1.0 - alpha)*accel_angle_y;
  angle_z = gyro_angle_z;  //Accelerometer doesn't give z-angle


					//d_x = accel_y/sqrt(pow(accel_x,2) + pow(accel_z,2));
					//Lb_printf("%d.%d \n",(short)d_x, (short)(d_x * 1000)%1000);

					
					Lb_printf("DEL:");
					Lb_printf("0.01200000");
#if 0
					Lb_printf("#ACC:");
					Lb_printf("%d.%d", (short)accel_angle_x  , (short)(accel_angle_x * 100)%100);
					Lb_printf(",");
					Lb_printf("%d.%d", (short)accel_angle_y  , (short)(accel_angle_y * 100)%100);
					Lb_printf(",");
					Lb_printf("%d.%d", (short)accel_angle_z  , (short)(accel_angle_z * 100)%100);
					
					Lb_printf("#GYR:");
					Lb_printf("%d.%d", (short)unfiltered_gyro_angle_x  , (short)(unfiltered_gyro_angle_x * 100)%100);
					Lb_printf(",");
					Lb_printf("%d.%d", (short)unfiltered_gyro_angle_y  , (short)(unfiltered_gyro_angle_y * 100)%100);
					Lb_printf(",");
					Lb_printf("%d.%d", (short)unfiltered_gyro_angle_z  , (short)(unfiltered_gyro_angle_z * 100)%100);
					
					Lb_printf("#FIL:");
					Lb_printf("%d.%d", (short)angle_x  , (short)(angle_x * 100)%100);
					Lb_printf(",");
					Lb_printf("%d.%d", (short)angle_y  , (short)(angle_y * 100)%100);
					Lb_printf(",");
					Lb_printf("%d.%d", (short)angle_z  , (short)(angle_z * 100)%100);
					Lb_printf("\n");
#endif					
					
					
					Lb_printf("#ACC:");
					Lb_printf("%d", (short)accel_angle_x );
					Lb_printf(",");
					Lb_printf("%d", (short)accel_angle_y  );
					Lb_printf(",");
					Lb_printf("%d", (short)accel_angle_z );
					
					Lb_printf("#GYR:");
					Lb_printf("%d", (short)unfiltered_gyro_angle_x  );
					Lb_printf(",");
					Lb_printf("%d", (short)unfiltered_gyro_angle_y  );
					Lb_printf(",");
					Lb_printf("%d", (short)unfiltered_gyro_angle_z );
					
					Lb_printf("#FIL:");
					Lb_printf("%d", (short)angle_x );
					Lb_printf(",");
					Lb_printf("%d", (short)angle_y );
					Lb_printf(",");
					Lb_printf("%d", (short)angle_z );
					Lb_printf("\n");





	                //                    Hw_Wait_ms(100);
                }







               break;  


			case 'm':
			case 'M':
				Ap_GLcdMenu_ShowMenu();
				break;
				
           default :
               break;
        }
    }
    
    return key;
}



/*---------------------------------------------------------------------------
     TITLE   :	main          
     WORK    : 	
     			메인 함수
     ARG     : 	void
     RET     : 	
     			int
---------------------------------------------------------------------------*/
int main(void)
{
	int key;
	u32 TimeStart;
	u32 TimeEnd;
	
	Hw_Init();

	//-- 명령어 처리
	//  
	Ap_GLcdMenu_ExeCmd();    


    while(1);
    
    return 0;
}
