#include "uart_1602.h"
#include "usart.h"
#include "delay.h"


void UART_1602_Init()
{
	UART3_Init(9600);
	backlightOn() ;
	clearLCD();
    lcdPosition(0,0);
}
void UART_Write(u8 value)	//uart2 send data
{
	while((USART3->SR&0X40)==0);
	USART3->DR =value;
}

void lcdPosition(int row, int col) 
{
	UART_Write(0xFE);   //command flag
	UART_Write((col + row*64 + 128));    //position 
    delay_ms(10);
}

void backlightOn() 	 //turns on the backlight
{ 
	UART_Write(0x7C);   //command flag for backlight stuff
	UART_Write(157);    //light level.
	delay_ms(10);
}

void backlightOff()  //turns off the backlight
{
	UART_Write(0x7C);   //command flag for backlight stuff
	UART_Write(128);     //light level for off.
	delay_ms(10);
}

void clearLCD()	//clear lcd
{
	UART_Write(0xFE);   //command flag
	UART_Write(0x01);   //clear command.
	delay_ms(10);
}