#include "led.h"
#include "delay.h"
#include "usart.h"
#include "matrix_key.h"
#include "24l01.h"
#include "run.h"
#include "uart_1602.h"
/*
	usart PA9,10 PB10,11
	LED PD2
	key PA0 PA1 PA2 PA3  PA6 PA7 PA12 PA11
*/
//extern float  angle[3];
void System_init()
{
	delay_init();	    	 //��ʱ������ʼ��
	uart_init(9600);
	UART_1602_Init();
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	matrix_key_init();
	NRF24L01_Init();    	//��ʼ��NRF24L01  
	  
 	while(NRF24L01_Check())	//���NRF24L01�Ƿ���λ.	
	{
		delay_ms(200);
		printf("nrf error\n");
	}								   
	NRF24L01_TX_Mode();
}

 int main(void)
 {	
	u8 key_value = 0; 
	System_init();
	
	while(1)
	{
		key_value = matrix_key_scan();
		if(key_value)
		{
			switch(key_value)
			{
				case 1:	run1();  break;
				case 2:	run2();	 break;
				case 3:	run3();  break;
				case 4:	run4();  break;
				case 5:	run5();  break;
				case 6: run6();	 break;
				default:		break;
			}
		}
		key_value = 0;
		
	}
	return 0;
 }

