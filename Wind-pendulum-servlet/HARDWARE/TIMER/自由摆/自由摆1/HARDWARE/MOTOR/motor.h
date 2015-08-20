#ifndef __MOTOR_H
#define __MOTOR_H	 
#include "sys.h"
 //������������I/O�ڵĺ궨��
#define IND1 PCout(12) //INA1 
#define IND2 PCout(11) //INA2
#define IND3 PCout(4) //INA3
#define IND4 PCout(5) //INA4	


/*************************************************************************
		                ���Ƶ������ĺ���
*************************************************************************/

extern int FLAG,STEP;

void MOTOR_Init(void);       //�����ʼ������	
void MOTOR_ZMove(void);         //�������˳ʱ��ת�� 	
void MOTOR_FMove(void);        //���������ʱ��ת�� 
void MOTOR_AllStop(void);	   //ȫ��ֹͣ
void MOTOR_Move(void);             //���Ұڶ�����60��
void run_step(int n,int dir);
#endif
