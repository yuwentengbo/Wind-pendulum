#include "led.h"
#include "delay.h"
#include "usart.h"
#include "mpu6050.h"
#include "24l01.h" 
#include "run.h"
#include "dc_moter.h"
#include "math.h"
/*
	usart PA9,10 PB10,11
	PWM  PB0(PB4 PB5)   PB1(PB6 P7)  PB8(PB12 PB13) PB9(PB14 PB15)
	NRF PA1234567 C4
	LED PD2 PC0
	
*/
extern float angle[3];
void System_init()
{
	delay_init();	    	 //延时函数初始化
	uart_init(9600);
	dc_moter_init();
	LED_Init();
	UART3_Init(115200);
	NRF24L01_Init();    	//初始化NRF24L01  
	  
 	while(NRF24L01_Check())	//检查NRF24L01是否在位.	
	{
		delay_ms(200);
		printf("nrf error\n");
	}								   
	NRF24L01_RX_Mode();
}


extern float w[3],a[3];
 int main(void)
 {	
	u8 rx_buf[10];
	System_init();
	TIM_Cmd(TIM3,ENABLE);
	TIM_Cmd(TIM4,ENABLE);
	 
	while(1)
	{
		while(1)
		{
			if(NRF24L01_RxPacket(rx_buf) == 0)
			{
				break;
			}
		}
		switch(rx_buf[0])
		{
			case '1':	run1();										break;
			case '2':	run2();										break;
			case '3':	run3();    delay_ms(3000);  PCout(0) = 0;	break;
			case '4':	run4();    delay_ms(3000);  PCout(0) = 0;   break;
			case '5':	run5(); 									break;
			default:		   									    break;
		}
		rx_buf[0] = 0;
	}
	
	return 0;
 }

/*
 void fun()
{
	int long_angle;
	int x_pwm,y_pwm;
	long_angle = 30;
	x_pwm = 60000;
	//y_pwm = (int)(x_pwm*(sin(long_angle)/cos(long_angle));
	//printf("")
	//printf("%lf",tan(45));
	//printf("%lf",sin(30));
	//printf("%lf",sin(long_angle)/cos(long_angle));
	//printf("%lf",tan(long_angle/180.0*3.14156));
	y_pwm = (int)(x_pwm*fabs(long_angle/180.000*3.1415926));
	printf("%d",y_pwm);
}

/*
while(1)
{
	/*key_value = matrix_key_scan();
	if(key_value)
	{
		printf("%d\n",key_value);
	}*/
	
/*	mpu6050_get();
	printf("X  %f Y %f \r\n",angle[0],angle[1]);
	
}*/