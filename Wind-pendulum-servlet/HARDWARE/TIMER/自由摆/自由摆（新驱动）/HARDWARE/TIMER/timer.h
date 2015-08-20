#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
extern s16 CNT_PERIOD;
void TIMER_init(u16,u16);
s16 GET_cnt(void);
float GET_angle(void);
void TIMER3_start(void);
void Timer4_Init(u16 arr,u16 psc);

#endif























