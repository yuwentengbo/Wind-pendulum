#ifndef __MOTOR_H
#define __MOTOR_H	 
#include "sys.h"
 //产生电机脉冲的I/O口的宏定义
#define IND1 PCout(12) //INA1 
#define IND2 PCout(11) //INA2
#define IND3 PCout(4) //INA3
#define IND4 PCout(5) //INA4	


/*************************************************************************
		                控制电机所需的函数
*************************************************************************/

extern int FLAG,STEP;

void MOTOR_Init(void);       //电机初始化函数	
void MOTOR_ZMove(void);         //步进电机顺时钟转动 	
void MOTOR_FMove(void);        //步进电机逆时钟转动 
void MOTOR_AllStop(void);	   //全部停止
void MOTOR_Move(void);             //左右摆动超过60度
void run_step(int n,int dir);
#endif
