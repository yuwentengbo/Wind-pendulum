#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "timer.h"
#include "motor.h"	
#include "function.h" 
#include "math.h"
#include "mpu.h"
	 
//Mini STM32�����巶������2
//��������ʵ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com	
extern float angle[3];
extern float now_angle; 
extern int R_step ; 
int angle_list[63] = {  0, -1, 2, 4, 6, 8, 10, 12, 14, 16,
					   18, 20, 22, 24, 26,  28,  30, 32, 34, 35,
					   36, 38, 40, 42, 44,  46 , 48, 50, 52, 54,
					   55, 57, 59, 61, 63,  65,  67, 69, 70, 71,
					   72, 73, 72, 74, 76,  78,  80, 82, 84, 88,
					   90, 92, 94, 96, 100, 104,106,110,112,114,
					   116,116, 116}; 
int angle_list2[63] = {  0, -1, 2, 4, 6, 8, 10, 12, 14, 16,
					   18, 20, 22, 24, 26,  28,  30, 32, 34, 35,
					   36, 38, 40, 42, 44,  46 , 48, 50, 52, 54,
					   44, 45, 46, 47, 48,  49,  50, 51, 52, 53,
					   54, 70, 72, 74, 76,  78,  80, 82, 84, 88,
					   90, 92, 94, 96, 100, 104,106,110,112,114,
					   116,116, 116};  

int anti_angle_list[63] = { 0, 0, 2, 3, 4, 5, 6, 7, 8, 9,
					  	   9,10,11,12,13,14,15,16,17,18,
					       19,20,21,22,23,24,25,26,27,28,
					  	   30,30,32,32,34,34,34,36,36,38,
					       40,40,40,42,42,42,42,44,44,44,
					       46,46,46,48,48,48,50,50,52,52,
					       52,52}; 
int anti_angle_list2[63] = { 0,0,0, 2, 3, 4, 5, 6, 7, 8, 9,
					  	   9,10,11,12,13,14,15,16,17, 18,
					       19,20,21,22,23,24,25,26,27,28,
					  	   30,30,32,32,34,34,34,36,36,38,
					       40,40,40,42,42,42,42,44,44,44,
					       46,46,46,48,48,48,50,50,52,52,
					       52};


int col_angle1 = 0,col_angle2 = 0, anti_col_angle1 = 0, anti_col_angle2 = 0, diff_angle = 0;
int diff_step = 0;
int main(void)
{								  
	u8 i;
float zero_mpu = -12.0;
	//u8 t,sg=0,i,yun,n,j,dir = 0;
//	int flag_first=0;  
//	int flag;
	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);
	uart1_init(72,9600); 
	uart2_init(36,115200);
		     
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
	MOTOR_Init(); 
	TIMER_init(CNT_PERIOD,0);
	//Timer4_Init(4000,7199);
	TIMER3_start();
	
	while(1)
	{	
//	    col_angle1 = (int)GET_angle();
//		if(col_angle1 >=1)
//			R_focus();
//		else if(col_angle1 <= -1) 
//			L_focus();
//
//		col_angle2 = col_angle1;
 		
		   get_mpu();
		 //col_angle1 = (int)GET_angle();
//		 if(col_angle1 ==0)
//		  { 
//				   get_mpu();
//				   if((int)(angle[1] - zero_mpu)  <0)
//		            {
//						 for(i=0;i<(int)fabs((angle[1] - zero_mpu)/0.9);i++)
//						  { MOTOR_FMove();
//						   delay_ms(2);
//						   }
//					}
//				   else if((int)(angle[1] - zero_mpu)  >0)
//					{
//					   for(i=0;i<(int)((angle[1] - zero_mpu)/0.9);i++)
//						   {
//						    MOTOR_ZMove();
//						    delay_ms(2);
//							}
//					}
//           }
//		if(col_angle1 > 0 && col_angle2 > 0)
//		{	if(col_angle1 >= col_angle2)				
//			    diff_step = angle_list[col_angle1] - angle_list[col_angle2];
//			else if(col_angle1 < col_angle2)
//			    diff_step =angle_list2[col_angle1] - angle_list2[col_angle2];
//		 }
//		else if(col_angle1 < 0 && col_angle2 < 0)
//		{	
//		   if(col_angle1 <= col_angle2)				
//			{
//			anti_col_angle1 = fabs(col_angle1);
//			anti_col_angle2 = fabs(col_angle2);
//			diff_step = anti_angle_list[anti_col_angle1] - anti_angle_list[anti_col_angle2];
//		    }
//	       else if(col_angle1 > col_angle2)
//		   {
//			 anti_col_angle1 = fabs(col_angle1);
//			 anti_col_angle2 = fabs(col_angle2);
//			diff_step = anti_angle_list2[anti_col_angle1] - anti_angle_list2[anti_col_angle2];
//
//		   }
//    
//
//		}
//		else
//				diff_step = 0;
//				
//		if(col_angle1 > 0)
//		{    
//			if(diff_step > 0)			
//			for(i = 0; i< diff_step; i++)
//			{
//				MOTOR_ZMove();
//				delay_ms(2);
//			}
//			
//			else			
//			for(i = 0; i< fabs(diff_step); i++)
//			{
//				MOTOR_FMove();
//				delay_ms(2);
//			}
//			//R_adjust_mpu();
//		}
//		else if(col_angle1 < 0)
//		{
//			if(diff_step > 0)			
//			for(i = 0; i< diff_step; i++)
//			{
//				MOTOR_FMove();
//				delay_ms(2);
//			}
//			else			
//			for(i = 0; i< fabs(diff_step); i++)
//			{
//				MOTOR_ZMove();
//				delay_ms(2);
//			}
//		
//		} 
//
//		
//		col_angle2 = col_angle1;
//
//		
		
		/*if( j>0)
		{			
			R_step = angle_list[j];
		}
		else 
		{
			yun = fabs(now_angle);
			temp = atan((103-103*cos(yun*0.0175))/(150+103*sin(yun*0.0175)))*57.3;			
			R_step =(int)((yun-temp)/1.8);
		
		}
		t=KEY_Scan();//�õ���ֵ
	   	if(t)
		{						   
			switch(t)
			{				 
				case 1:
					LED0=!LED0;	
		       		function1();
					break;
				case 2:
					 sg=1;

			     	break;
				case 3:	
					if(now_angle > 0)
					{			
						for( i = 0;i<R_step;i++)
						{
							MOTOR_ZMove();
							delay_ms(3);
						}
					}
					else
					{
						
						for( i = 0;i< R_step+2;i++)
						{
							MOTOR_FMove();
							delay_ms(3);
						}
					}
					break;
			}
		}else delay_ms(10); 
		
	flag = KEY3;
	if(flag == 1) 
		LED1=0;
		else
		LED1=1;
	if((!flag)&&(sg==1))
	  {
	  	function2();
	    sg=0;
	  }	*/ 

	}	 
}

























