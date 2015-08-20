#ifndef __DC_MOTER_H
#define __DC_MOTER_H
#include "sys.h"

void dc_cmd(int num,int cmd);
void dc_moter_init();
void dc_moter_setspeed(int flag,int speed);
void TIM3_Config(void);
void TIM4_Config(void);
void MY_GPIO_Init();

#endif