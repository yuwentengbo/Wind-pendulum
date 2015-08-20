#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "timer.h"
#include "motor.h"	 
#include "math.h"
#include "mpu.h"
	 
//Mini STM32开发板范例代码2
//按键输入实验
//正点原子@ALIENTEK
//技术论坛:www.openedv.com	
extern float now_angle; 
extern int R_step ;
extern float angle[3]; 
//int angle_list[63] = {  0,8,5,5,5,5,5,5,5,5,
//                        6,6,6,6,6,6,6,6,6,6,
//						6,6,8,6,6,6,6,6,6,6,
//						8,7,7,7,7,7,7,7,7,7,
//					   }; 
int angle_list[63] = {  0,8,13,18,23,28,33,38,43,48,
                        54,60,66,72,78,84,90,96,102,108,
						114,120,128,136,142,148,154,160,166,172,
						180,187,194,201,208,315,322,329,336,343,
					   }; 

//int angle_list2[63] = { 0,-13,-5,-5,-5,-5,-5,-5,-5,
//                        -6,-6,-6,-6,-6,-6,-6,-6,-6,-6,
//						-6,-6,-8,-6,-6,-6,-6,-6,-6,-6,
//						-8,-7,-7,-7,-7,-7,-7,-7,-7,-7,
//					    };

//int anti_angle_list[63] = {0,4,5,5,5,4,4,4,4,4,4,
//					   	   4,4,4,4,4,4,4,4,4,4,
//					       4,3,3,3,3,3,3,3,3,3,
//					  	   3,3,3,3,3,3,3,3,3,3,
//					       }; 
int anti_angle_list[63] = {0,4,9,14,19,23,27,31,35,39,43,
					   	   47,51,55,59,63,67,71,75,79,83,
					       87,90,93,96,99,102,105,108,111,114,
					  	   117,120,123,126,129,132,135,138,141,144,
					       };
//int anti_angle_list2[63] = {0,-9,-5,-5,-4,-4,-4,-4,-4,-4,
//					   	   -4,-4,-4,-4,-4,-4,-4,-4,-4,-4,
//					       -4,-3,-3,-3,-3,-3,-3,-3,-3,-3,
//					  	   -3,-3,-3,-3,-3,-3,-3,-3,-3,-3,
//					      	};


int col_angle1 = 0,col_angle2 = 0, anti_col_angle1 = 0, anti_col_angle2 = 0, diff_angle = 0;
int diff_step = 0;
int main(void)
{								  
	u8 i;
	float zero_mpu = -5.0;
	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);
	uart1_init(72,9600); 
	uart2_init(36,9600);
		     
	LED_Init();		  	 //初始化与LED连接的硬件接口
	KEY_Init();          //初始化与按键连接的硬件接口
	MOTOR_Init(); 
	TIMER_init(CNT_PERIOD,0);
	TIMER3_start();
	while(1)
	{	  
		col_angle1 = (int)GET_angle();
	 	/*if(col_angle1==0)
		{	 
			get_mpu();
			if((int)(angle[1] - zero_mpu)  < -0.5)
		    {
				for(i=0;i<(int)fabs((angle[1] - zero_mpu)/0.225);i++)
				{ 
					MOTOR_FMove();
				}
			}
			else if((int)(angle[1] - zero_mpu)  >0.5)
			{
				for(i=0;i<(int)((angle[1] - zero_mpu)/0.225);i++)
				{
					MOTOR_ZMove();
				}
			}  
		 } */
		if(col_angle1 > 0 && col_angle2 > 0 )
		{					
			diff_step = angle_list[col_angle1]-angle_list[col_angle2];				 
		}
		else if(col_angle1 < 0 && col_angle2 < 0 )
		{	
			anti_col_angle1 = fabs(col_angle1);
			anti_col_angle2 = fabs(col_angle2);
			diff_step = anti_angle_list[anti_col_angle1]-anti_angle_list[anti_col_angle2];
    	}
		else if(col_angle1 > 0 && col_angle2 <0 )
		{
			diff_step = 5;	
		}
		 
		else if(col_angle1 < 0 && col_angle2 >0 )
		{
			diff_step = 5;	
		}
				
		if(col_angle1 > 0)
		{    
			if(diff_step > 0)			
			for(i = 0; i< diff_step; i++)
			{
				MOTOR_ZMove();
			}
			
			else			
			for(i = 0; i< fabs(diff_step); i++)
			{							  
				MOTOR_FMove();
			}
		}
		else if(col_angle1 < 0)
		{
			if(diff_step > 0)			
			for(i = 0; i< diff_step; i++)
			{
				MOTOR_FMove();
			}
			else			
			for(i = 0; i< fabs(diff_step); i++)
			{
				MOTOR_ZMove();
			}
		} 	
		col_angle2 = col_angle1; 
	}	 
}

























