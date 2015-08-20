#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "timer.h"
#include "motor.h"	 
#include "math.h"
#include "mpu.h"
int main(void)
{								  
    u8 t;
	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);
	uart1_init(72,9600); 
	uart2_init(36,115200);	     
	LED_Init();		  	 //初始化与LED连接的硬件接口
	KEY_Init();          //初始化与按键连接的硬件接口
    LCD_Init();
	MOTOR_Init(); 
	TIMER_init(CNT_PERIOD,0);
	TIMER3_start();
	LCD_ShowString(40,80,"Now_angle is :");

	while(1)
	{
		GET_angle();
		t=KEY_Scan();//得到键值
	   	if(t)
		{						   
			switch(t)
			{				 
				case 1:	
		       		function1();
					break;
				case 2:
					function2(); 
			     	break;	
				case 3:	
					function3();
					break;
			}
		}else delay_ms(10); 		
}	
}

























