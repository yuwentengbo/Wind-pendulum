#include "delay.h"
#include "function.h"
#include "sys.h"
#include "motor.h"
#include "timer.h"
#include "usart.h"
#include "math.h"
#include "delay.h"
#include "mpu.h"


extern float now_angle;
int col_angle1 = 0,col_angle2 = 0, anti_col_angle1 = 0, anti_col_angle2 = 0, diff_angle = 0;
int diff_step = 0;

int angle_list[63] =  { 0,8,5,5,5,5,5,5,5,5,
                        6,6,6,6,6,6,6,6,6,6,
						6,6,8,6,6,6,6,6,6,6,
						8,7,7,7,7,7,7,7,7,7,
					   }; 

int angle_list2[63] = { 0,-13,-5,-5,-5,-5,-5,-5,-5,
                        -6,-6,-6,-6,-6,-6,-6,-6,-6,-6,
						-6,-6,-8,-6,-6,-6,-6,-6,-6,-6,
						-8,-7,-7,-7,-7,-7,-7,-7,-7,-7,
					   };

int anti_angle_list[63] = {0,4,5,5,5,4,4,4,4,4,4,
					   	   4,4,4,4,4,4,4,4,4,4,
					       4,3,3,3,3,3,3,3,3,3,
					  	   3,3,3,3,3,3,3,3,3,3,
					       }; 
int anti_angle_list2[63] = {0,-9,-5,-5,-4,-4,-4,-4,-4,-4,
					   	   -4,-4,-4,-4,-4,-4,-4,-4,-4,-4,
					       -4,-3,-3,-3,-3,-3,-3,-3,-3,-3,
					  	   -3,-3,-3,-3,-3,-3,-3,-3,-3,-3,
					      	};

 


void  function1(void)
 {		
  	int i;
	for(i=0;i<16000;i++)
	{	
		DIR = 1;
		RUN = 1;
		delay_us(594);
	    RUN = 0;
		delay_us(594);		
	}
 }


void function2(void)
  {
  	int i;		
    int step = (int)(GET_angle()/0.225);
	for(i=0;i<step;i++)
	{	
		MOTOR_FMove();		
	}
  }

void function3(void)
{
	int step,i; 
	float temp,angle_abs;
	now_angle = GET_angle(); 
	if(now_angle > 0)
	{
	temp = atan((150-103*sin(now_angle*3.1416/180))/(103-103*cos(now_angle*3.1416/180)))*180/3.1416;		
	step = ((int)((90+now_angle-temp)/0.225));
	for( i = 0;i<step;i++)
		MOTOR_ZMove();
	 }
	else if(now_angle < 0)
	{
	  angle_abs=fabs(now_angle);
	 temp = atan((103-103*cos(angle_abs*3.1416/180))/(150+103*sin(angle_abs*3.1416/180)))*180/3.1416;		
	step = ((int)((angle_abs-temp)/0.225));
	for( i = 0;i<step;i++)
		MOTOR_FMove();
	}

}



