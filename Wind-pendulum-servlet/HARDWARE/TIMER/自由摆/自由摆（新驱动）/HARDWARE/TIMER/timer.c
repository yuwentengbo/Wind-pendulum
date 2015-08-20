#include "timer.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "motor.h"
#include "math.h"
//#include "function.h"

s16 CNT_PERIOD=4094;
float angle_last = 0;
float now_angle ;
int last_step=0;
int R_step = 0;
void TIMER_init(u16 arr,u16 psc)
{
	
	
	RCC->APB1ENR|=1<<1;       
	RCC->APB2ENR|=1<<2;   

	
  	TIM3->ARR=arr;  //设定计数器自动重装值//刚好1ms    
 	TIM3->PSC=psc;  //预分频器7200,得到10Khz的计数时钟
	
	GPIOA->CRL&=0X00FFFFFF;
	GPIOA->CRL|=0X44000000;


	TIM3->CR1 &=~(3<<8);
	TIM3->CR1 &=~(3<<5);
		
	TIM3->CCMR1 |= 1<<0;
	TIM3->CCMR1 |= 1<<8; 
	TIM3->CCER &= ~(1<<1);	 
	TIM3->CCER &= ~(1<<5);	
	TIM3->CCMR1 |= 3<<4; 
	TIM3->SMCR |= 1<<0;	
	
}



void TIMER3_start(void)
{
	TIM3->CR1 |= 0x01;   
}
s16 GET_cnt(void)
{
 	if(TIM3->CNT<2046)
		return TIM3->CNT;
 	else
		return (TIM3->CNT-CNT_PERIOD);
}

float GET_angle(void)
{
	printf("//////////////////////////////%4.2f\n",(GET_cnt()/2048.0)*360);
	return ((GET_cnt()/2048.0)*360);
}


void TIM4_IRQHandler(void)
{ 	
	int i,step=0;

	if(TIM4->SR&0X0001)//溢出中断
	{	
		LED1 = !LED1;
		step =R_step - last_step; 
		last_step =R_step; 
		//printf("motor step ：%d\n",step);
		if(step > 1)
		{
			for(i=0;i<step;i++)	
			{	
				MOTOR_ZMove();
				delay_ms(2);
			}
		}
		else if(step < -1)
		{
			for(i=0;i<fabs(step);i++)	
			{	
				MOTOR_FMove();
				delay_ms(2);
			}
		}		    				   				     	    	
	}			   
	TIM4->SR&=~(1<<0);//清除中断标志位 	    
}  

/*void TIM4_IRQHandler(void)
{ 	
	int i;
	int step;
	float temp;
	if(TIM4->SR&0X0001)//溢出中断
	{	  
		LED1 = !LED1;
	    temp = atan((150-103*sin(now_angle*3.1416/180))/(103-103*cos(now_angle*3.1416/180)))*180/3.1416;
		R_step=(int)(90+now_angle-temp)/1.8; 		
		step =R_step - last_step; 
		last_step =R_step;
		if(fabs(step) > 1)
		{                		
			if(step > 0)
			{
				for(i=0;i<step;i++)	
				{	
					MOTOR_ZMove();
					delay_ms(3);
				}
			}
			else if(step < 0)
			{
				for(i=0;i<fabs(step);i++)	
				{	
					MOTOR_FMove();
					delay_ms(3);
				}
			}
		}
		else 
		{
			MOTOR_AllStop();
		}		    				   				     	    	
	}	  
	TIM4->SR&=~(1<<0);//清除中断标志位 	    
}  
 */

void Timer4_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<2;//TIM3时钟使能    
 	TIM4->ARR=arr;  //设定计数器自动重装值//刚好1ms    
	TIM4->PSC=psc;  
	TIM4->DIER|=1<<0;   //允许更新中断				
//	TIM4->DIER|=1<<6;   //允许触发中断	   
	TIM4->CR1|=0x01;    //使能定时器3
  	MY_NVIC_Init(1,3,TIM4_IRQChannel,2);//抢占1，子优先级3，组2									 
} 











