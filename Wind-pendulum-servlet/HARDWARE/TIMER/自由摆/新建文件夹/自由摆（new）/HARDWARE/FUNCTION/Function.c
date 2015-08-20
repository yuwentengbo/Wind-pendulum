#include "delay.h"
#include "function.h"
#include "sys.h"
#include "motor.h"
#include "timer.h"
#include "usart.h"
#include "math.h"
#include "delay.h"
#include "mpu.h"

extern float angle[3];
extern float now_angle;
extern int col_angle1;

 void  function1(void)
 {		
  	int i;
	for(i=0;i<2000;i++)
	{	
		MOTOR_ZMove();
		delay_ms(9);
		delay_us(500);		
	}

//	 delay_ms(1000);
//	 	for(i=0;i<1000;i++)
//	{	
//		MOTOR_FMove();
//		delay_ms(9);
//		delay_us(500);		
//	}

 }

void  function2(void)
  {
  	int i;		
  	u8 step = (int)(GET_angle()/1.8);
	printf("%d\n",step);
	for(i=0;i<=step;i++)
	{	
		MOTOR_FMove();
		delay_ms(4);		
	}
  }

void function3(void)
{
	int step,i;  
	float temp = atan((150-103*sin(now_angle*3.1416/180))/(103-103*cos(now_angle*3.1416/180)))*180/3.1416;	
	step = ((int)((90+now_angle-temp)/1.8));
	printf("function 3   :%d",step);
	for( i = 0;i<step;i++)
	{
		MOTOR_ZMove();
		delay_ms(3);
	}
}

int  caculate_step(void)
  {
  	if(now_angle >= 1)
	{
  		float temp = atan((150-103*sin(now_angle*3.1416/180))/(103-103*cos(now_angle*3.1416/180)))*180/3.1416;	
	    return  ((int)((90+now_angle-temp)/1.8));
	}
	return 0;	
  }


void R_adjust_move(int std)
{
	int i;
	if((int)(angle[1] - (std))  <0)
	{
		for(i=0;i<(int)fabs((angle[1] - std)/0.9);i++)
		{ 
			MOTOR_FMove();
			delay_ms(2);
		}
					} 
	if((int)(angle[1] - (std))  >0)
	{
		for(i=0;i<(int)((angle[1] - std)/0.9);i++)
		{
			MOTOR_ZMove();
			delay_ms(2);
	    }
	}
}

void R_adjust_mpu()
{
	if(col_angle1 == 5 || col_angle1 == 10)
	get_mpu();	   
	R_adjust_move(-12);
}
