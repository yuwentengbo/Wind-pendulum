#ifndef __MOTOR_H
#define __MOTOR_H	 
#include "sys.h"
 //产生电机脉冲的I/O口的宏定义
#define DIR PAout(4)// PA1	
#define RUN PAout(11)// PA11


/*************************************************************************
		                控制电机所需的函数
*************************************************************************/

void MOTOR_Init(void);           //电机初始化函数	
void MOTOR_ZMove(void);         //步进电机顺时钟转动 	
void MOTOR_FMove(void);        //步进电机逆时钟转动 
void run_step(int n,int dir);
#endif

