#include"motor.h"
#include"delay.h"

void MOTOR_Init(void)
{
	RCC->APB2ENR|=1<<2;        //电机A使能PORTA时钟	 	    	 
	GPIOA->CRL&=0XFF00FFFF; 
	GPIOA->CRL|=0X00330000;    //PA.1,PA.0 推挽输出  
	GPIOA->ODR|=48<<5; 	
	
	GPIOA->CRH&=0XFFFF0FFF; 
	GPIOA->CRH|=0X00003000;         
}

void MOTOR_ZMove()	
{
	DIR = 0;
	RUN = 1;
	delay_us(300);
    RUN = 0;
	delay_us(300);
}

void MOTOR_FMove()	
{
	DIR = 1;
	RUN = 1;
	delay_us(300);
    RUN = 0;
	delay_us(300);
}

void run_step(int n,int dir)
{
	int i;
	if(dir == 1)
	{
		for(i=0;i<n*1600;i++)
			MOTOR_ZMove();	
	}
	else if(dir == 0)
	{
		for(i=0;i<n*1600;i++)
			MOTOR_FMove();
	}
}
