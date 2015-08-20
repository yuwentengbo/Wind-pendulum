#include "run.h"
#include "usart.h"
#include "24l01.h"
#include "delay.h"
#include "uart_1602.h"
#include "matrix_key.h"
u8 stop[]= "s"; 
void run1()
{
	u8 show_data[10] = "question1";
	u8 i;
	u8 tmp_buf[10];
	
	printf("client1");
	clearLCD();
	tmp_buf[0] = '1';
	for(i=0;i<9;i++)
	{
			UART_Write(show_data[i]);
	}
	
	while(1)
	{
		if(TX_OK ==NRF24L01_TxPacket(tmp_buf))
		{
				break;
		}
	}
}
void run2()
{
	u8 show_data[10] = "question2";
	u8 rx_buf[2];
	u8 key_value = 0;
	u8 long_data[2];
	u8 i;
	u8 tmp_buf[10];
	
	printf("client2");
	tmp_buf[0] = '2';
	clearLCD();
	for(i=0;i<9;i++)
	{
			UART_Write(show_data[i]);
	}
	while(1)
	{
		if(TX_OK ==NRF24L01_TxPacket(tmp_buf))
		{
				break;
		}
	}
	
	
	i = 0;
	while(1)
	{
		key_value = matrix_key_scan();
		if(key_value)
		{
			if(key_value < 10)
			{
				long_data[i++] = key_value;
				lcdPosition(1,i); 
				UART_Write(key_value+48);
			}
			else if(key_value == 10)
			{
				long_data[i++] = 0;
				lcdPosition(1,i); 
				UART_Write(0+48);
			}
		}
		if(i == 2)
		{
			break;
		}
	}
	
	while(1)
	{
		if(TX_OK ==NRF24L01_TxPacket(long_data))
		{
				break;
		}
	}
}
void run3()
{
	u8 show_data[10] = "question3";
	u8 rx_buf[2];
	u8 key_value = 0;
	u8 long_data[3];
	u8 i;
	u8 tmp_buf[10];
	
	printf("client3");
	tmp_buf[0] = '3';
	clearLCD();
	for(i=0;i<9;i++)
	{
			UART_Write(show_data[i]);
	}
	while(1)
	{
		if(TX_OK ==NRF24L01_TxPacket(tmp_buf))
		{
				break;
		}
	}
	
	i = 0;
	while(1)
	{
		key_value = matrix_key_scan();
		if(key_value)
		{
			if(key_value < 10)
			{
				long_data[i++] = key_value;
				lcdPosition(1,i); 
				UART_Write(key_value+48);
			}
			else if(key_value == 10)
			{
				long_data[i++] = 0;
				lcdPosition(1,i); 
				UART_Write(0+48);
			}
		}
		if(i == 3)
		{
			break;
		}
	}
	
	while(1)
	{
		if(TX_OK ==NRF24L01_TxPacket(long_data))
		{
				break;
		}
	}
}
void run4()
{
	u8 show_data[10] = "question4";
	u8 key_value = 0;
	u8 rx_buf[2];
	u8 i;
	u8 tmp_buf[10];
	
	printf("client4");
	tmp_buf[0] = '4';
	clearLCD();
	for(i=0;i<9;i++)
	{
			UART_Write(show_data[i]);
	}
	while(1)
	{
		if(TX_OK ==NRF24L01_TxPacket(tmp_buf))
		{
				break;
		}
	}
}

void run5()
{
	/*u8 show_data[10] = "question5";
	u8 key_value = 0;
	u8 rx_buf[2];
	u8 i;
	u8 tmp_buf[10];
	printf("client5");
	clearLCD();
	tmp_buf[0] = '5';
	for(i=0;i<9;i++)
	{
			UART_Write(show_data[i]);
	}
	
	while(1)
	{
		if(TX_OK ==NRF24L01_TxPacket(tmp_buf))
		{
				break;
		}
	}
	while(1)
	{
		key_value = matrix_key_scan();
		if(key_value == 16)
		{
			while(1)
			{
				if(TX_OK ==NRF24L01_TxPacket(stop))
				{
						break;
				}
			}
			break; 
		}
	}*/
}

void run6()
{
	/*u8 key_value = 0;
	u8 rx_buf[2];
	u8 show_data[10] = "question6";
	u8 i;
	u8 tmp_buf[10];
	printf("1");
	clearLCD();
	tmp_buf[0] = '6';
	for(i=0;i<9;i++)
	{
			UART_Write(show_data[i]);
	}
	
	while(1)
	{
		if(TX_OK ==NRF24L01_TxPacket(tmp_buf))
		{
				break;
		}
	}
	//delay_ms(3000);
	
	/*NRF24L01_RX_Mode();
	while(1)
	{
		if(0 ==NRF24L01_RxPacket(rx_buf))
		{
				break;
		}
		else 
		{
				delay_ms(10);
		}
	}
	printf("tar1\n");
	while(1)
	{
		if(rx_buf[0]  == 'o')
		break;
	}
	printf("tar2\n");*/
	
	/*while(1)
	{
		key_value = matrix_key_scan();
		if(key_value == 16)
		{
			while(1)
			{
				if(TX_OK ==NRF24L01_TxPacket(stop))
				{
						break;
				}
			}
			break; 
		}
	}*/
}