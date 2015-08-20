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
extern float angle[3];
extern float now_angle; 
extern int R_step ; 

float angle_list2[63] = {0,1.01,2.02,3.05,4.09,5.15,6.22,7.31,8.41,9.53,10.66,
						11.80,12.97,14.15,15.35,16.57,17.81,19.07,20.35,21.66,22.98,
						24.33,25.70,27.10,28.52,31.45,32.95,34.48,36.04,37.63,39.25,
						40.90,42.58,44.30,46.05,47.82,49.64,51.48,53.36,55.27,57.21,
						59.18,61.18,63.21,65.27,67.36,69.48,71.61,73.77,75.95,78.15,
						80.36,82.58,84.82,87.06,89.30,91.55,93.79,96.03,98.26,100.48,
						102.69,104.88}; 
float angle_list1[63] = {0,0.99,1.98,2.95,3.91,4.86,5.80,6.74,7.66,8.57,9.48,
						10.38,11.27,12.15,13.02,13.89,14.75,15.60,16.45,17.29,18.12,
						18.95,19.78,20.59,21.40,22.21,23.01,23.81,24.60,25.39,26.17,
						26.95,27.72,28.49,29.25,30.02,30.77,31.53,32.28,33.02,33.77,
						34.51,35.25,35.98,36.71,37.44,38.17,38.89,39.61,40.33,41.04,
						41.75,42.46,43.17,43.88,44.58,45.28,45.98,46.68,47.37,48.07,
						48.76,49.45};

int col_angle1 = 0,col_angle2 = 0, anti_col_angle1 = 0, anti_col_angle2 = 0, diff_angle = 0;
int diff_step = 0;
int main(void)
{								  
	u8 i;
	float zero_mpu = -12.0;
	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);
	uart1_init(72,9600); 
	uart2_init(36,115200);
		     
	LED_Init();		  	 //初始化与LED连接的硬件接口
	KEY_Init();          //初始化与按键连接的硬件接口
	MOTOR_Init(); 
	TIMER_init(CNT_PERIOD,0);
	TIMER3_start();
	while(1)
	{	 	
 		col_angle1 = (int)GET_angle();
		get_mpu();
		if(col_angle1 ==0) //调零点
		{ 
			
			if((int)(angle[1] - zero_mpu)  <0)
		    {
				for(i=0;i<(int)fabs((angle[1] - zero_mpu)/0.225);i++)
				{ 
					MOTOR_FMove();
				}
			}
			else if((int)(angle[1] - zero_mpu)  >0)
			{
				for(i=0;i<(int)((angle[1] - zero_mpu)/0.225);i++)
				{
					MOTOR_ZMove();
			
				}
			}
        } //调零结束
		
		if(col_angle1 > 0 && col_angle2 >=0)//在右半边
		{				
			diff_step = (int)((angle[1] + (angle_list1[col_angle1]+12.0))/0.225);

			if(col_angle1 > col_angle2)//上升时
				for(i = 0; i<  fabs(diff_step); i++)
				{
				MOTOR_ZMove();
				}
					
			else if(col_angle1 < col_angle2)//下降时
			for(i = 0; i< fabs(diff_step); i++)
				{
				MOTOR_FMove();
				} 
		 }


		 /*else if(col_angle1 < 0 && col_angle2 < 0)//在左半边时
		 {			
			
			diff_step = (int)((angle[1]  - (angle_list2[col_angle1]+12.0))/0.225);	
		    
			if(col_angle1 < col_angle2)//上升时
			    for(i = 0; i<  fabs(diff_step); i++)
				    {	
					MOTOR_FMove();
					}
									
	        else if(col_angle1 >col_angle2)//下降时
				    for(i = 0; i< fabs(diff_step); i++)
				    {
					MOTOR_ZMove();
					}
    	 } 


		else
				diff_step = 0; 	*/
						
		col_angle2 = col_angle1;  	
	} 
}

























