#ifndef __UART_1602_H
#define __UART_1602_H
#include "sys.h"

void UART_Write(u8 value);
void UART_1602_Init();
void backlightOn();
void backlightOff();
void clearLCD();
void lcdPosition(int row, int col);
#endif