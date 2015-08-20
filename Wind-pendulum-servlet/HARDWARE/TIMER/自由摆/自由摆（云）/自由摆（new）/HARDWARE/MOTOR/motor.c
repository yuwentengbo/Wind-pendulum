#include"motor.h"
#include"delay.h"

void MOTOR_Init(void)
{
	RCC->APB2ENR|=1<<2;        //电机A使能PORTA时钟	 	    	 
	GPIOA->CRL&=0XFFF0F000; 
	GPIOA->CRL|=0X00030333;    //PA.1,PA.0 推挽输出  
	GPIOA->ODR|=7<<0; 	         
}

void MOTOR_ZMove()	
{
	DIR = 0;
	RUN = 0;
	delay_us(300);
    RUN = 1;
	delay_us(300);
}

void MOTOR_FMove()	
{
	DIR = 1;
	RUN = 0;
	delay_us(300);
    RUN = 1;
	delay_us(300);
}

void run_step(int n,int dir)
{
	int i;
	if(dir == 1)
	{
		for(i=0;i<n*200;i++)
			MOTOR_ZMove();	
	}
	else if(dir == 0)
	{
		for(i=0;i<n*200;i++)
			MOTOR_FMove();
	}
}
