#ifndef __MATRIX_H
#define __MATRIX_H
#include "sys.h"

#define IO1  GPIO_Pin_0
#define IO2  GPIO_Pin_1
#define IO3  GPIO_Pin_2
#define IO4  GPIO_Pin_8
#define IO5  GPIO_Pin_4
#define IO6  GPIO_Pin_5
#define IO7  GPIO_Pin_6
#define IO8  GPIO_Pin_7

#define OUT1 PBout(0)
#define OUT2 PBout(1)
#define OUT3 PBout(2)
#define OUT4 PBout(8)
#define IN1  PBin(4)
#define IN2  PBin(5)
#define IN3  PBin(6)
#define IN4  PBin(7)
void matrix_key_init();
int matrix_key_scan();

#endif