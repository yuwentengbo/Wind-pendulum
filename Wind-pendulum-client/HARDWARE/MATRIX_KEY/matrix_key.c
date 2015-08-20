#include "matrix_key.h"
#include "delay.h"
#include "usart.h"

void matrix_key_init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin = IO1|IO2|IO3|IO4;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
    GPIO_Init(GPIOB, &GPIO_InitStructure);					 
	GPIO_SetBits(GPIOB,IO1|IO2|IO3|IO4);

	
	GPIO_InitStructure.GPIO_Pin = IO5|IO6|IO7|IO8;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		  
    GPIO_Init(GPIOB, &GPIO_InitStructure);					 
	GPIO_SetBits(GPIOB,IO5|IO6|IO7|IO8);


}
int matrix_key_scan()
{
	u8 key_value = 0;
	static u8 key_up = 1;
	u8 value1 = 1,value2 = 1,value3 = 1,value4 = 1;
	
	OUT1 = 0; OUT2 = 1; OUT3 = 1; OUT4 = 1;
	value1 = IN1;
	value2 = IN2;
	value3 = IN3;
	value4 = IN4;
	//printf("%d  value1 %d value2 %d value3 %d value4\n",value1,value2,value3,value4);
	//while(1);
	if(key_up &&(!(value1 && value2 && value3 && value4)))
	{
		key_up = 0;
		delay_ms(80);
		if(value1 == 0)			return 1;
		else if(value2 == 0)	return 2;
		else if(value3 == 0)	return 3;
		else if(value4 == 0)	return 4;
	}
	value1 = 1; value2 = 1;  value3 = 1;  value4 = 1;
	
	OUT1 = 1; OUT2 = 0; OUT3 = 1; OUT4 = 1;
	value1 = IN1;
	value2 = IN2;
	value3 = IN3;
	value4 = IN4;
	if(key_up &&(!(value1 && value2 && value3 && value4)))
	{
		key_up = 0;
		delay_ms(80);
		if(value1 == 0)			return 5;
		else if(value2 == 0)	return 6;
		else if(value3 == 0)	return 7;
		else if(value4 == 0)	return 8;
	}
	value1 = 1; value2 = 1;  value3 = 1;  value4 = 1;
	
	OUT1 = 1; OUT2 = 1; OUT3 = 0; OUT4 = 1;
	value1 = IN1;
	value2 = IN2;
	value3 = IN3;
	value4 = IN4;
	if(key_up &&(!(value1 && value2 && value3 && value4)))
	{
		key_up = 0;
		delay_ms(80);
		if(value1 == 0)			return 9;
		else if(value2 == 0)	return 10;
		else if(value3 == 0)	return 11;
		else if(value4 == 0)	return 12;
	}
	value1 = 1; value2 = 1;  value3 = 1;  value4 = 1;
	
	OUT1 = 1; OUT2 = 1; OUT3 = 1; OUT4 = 0;
	value1 = IN1;
	value2 = IN2;
	value3 = IN3;
	value4 = IN4;
	if(key_up &&(!(value1 && value2 && value3 && value4)))
	{
		key_up = 0;
		delay_ms(80);
		if(value1 == 0)			return 13;
		else if(value2 == 0)	return 14;
		else if(value3 == 0)	return 15;
		else if(value4 == 0)	return 16;
	}
	delay_ms(80);
	if((key_up == 0)&&IN1 ==1 &&IN2 == 1 &&  IN3 == 1 &&  IN4 == 1)
	{
		key_up = 1;
	}
	
	return 0;
}

