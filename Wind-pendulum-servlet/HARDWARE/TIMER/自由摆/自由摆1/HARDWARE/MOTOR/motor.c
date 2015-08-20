#include"motor.h"
#include"delay.h"
#include "led.h"
#include "usart.h"
#include "math.h"

static int FLAG = 0,STEP = 0;
int M[8][4] = {1,0,0,1,
			   1,0,0,0,
			   1,1,0,0,
			   0,1,0,0,
			   0,1,1,0,
			   0,0,1,0,
			   0,0,1,1,
			   0,0,0,1,
              };

//���ʹ�ܺ���
void MOTOR_Init(void)
{
	RCC->APB2ENR|=1<<4;        //���Aʹ��PORTAʱ��	 	    	 
	GPIOC->CRH&=0XFFF00FFF; 
	GPIOC->CRH|=0X00033000;    //PA.1~PA.4 �������   	 
    //GPIOA->ODR|=30<<1;   
	GPIOC->CRL&=0XFF00FFFF; 
	GPIOC->CRL|=0X00330000;        
}

//С��ԭ��ת�亯��
//speed:û��֮�����ʱ 
//step: ���һ����ת���Ĳ���



//���ȫ��ֹͣ����
void MOTOR_AllStop(void)
{
	IND1 = 1;
	IND2 = 0;	
	IND3 = 0;
	IND4 = 1;
}

//���D˳ʱ��ת������
//speed: ���ת��ʱÿ��֮�����ʱ  ��λ��ms
void MOTOR_ZMove()	  
{
	 if(STEP == 8)
	 	STEP = 0;
	 IND1 = M[STEP][0];
	 IND2 = M[STEP][1];
	 IND3 = M[STEP][2];
	 IND4 = M[STEP][3];
	 STEP++;
}

void MOTOR_FMove(void)
{
	 if(STEP == -1)
	 	STEP = 7;
	 IND1 = M[STEP][0];
	 IND2 = M[STEP][1];
	 IND3 = M[STEP][2];
	 IND4 = M[STEP][3];
	 STEP--;
}

void MOTOR_Move()
{
	 if(FLAG == 0)
		MOTOR_ZMove();
	 else if(FLAG == 1)
		MOTOR_FMove();
}

void run_step(int n,int dir)
{
	int i;
	if(dir == 0)
	{
		for(i=0;i<n;i++)	
		{	
			MOTOR_ZMove();
			delay_ms(3);
		}
	}
	else if(dir == 1)
	{
		for(i=0;i<n;i++)	
		{	
			MOTOR_FMove();
			delay_ms(3);
		}
	}
}
