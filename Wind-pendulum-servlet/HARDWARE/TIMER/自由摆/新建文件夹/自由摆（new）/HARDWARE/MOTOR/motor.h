#ifndef __MOTOR_H
#define __MOTOR_H	 
#include "sys.h"
 //������������I/O�ڵĺ궨��
#define DIR PAout(4)// PA1	
#define RUN PAout(11)// PA11


/*************************************************************************
		                ���Ƶ������ĺ���
*************************************************************************/

void MOTOR_Init(void);           //�����ʼ������	
void MOTOR_ZMove(void);         //�������˳ʱ��ת�� 	
void MOTOR_FMove(void);        //���������ʱ��ת�� 
void run_step(int n,int dir);
#endif

