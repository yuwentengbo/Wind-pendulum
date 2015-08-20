#include "mpu.h"
#include "sys.h"
#include "usart.h"		
#include "delay.h"
#include "motor.h"
#include "led.h"
#include "math.h"
#include "timer.h"

float angle[3];	  
extern u8 Temp[11];
extern volatile u8 sign;

void get_mpu()
{
	static int a_flag=0;

	while(1)
	{
		if(sign)
		{
	 		sign=0;
     		if(Temp[0]==0x55)       //���֡ͷ
     		{  
     			switch(Temp[1])
        		{
               		/*case 0x51: //��ʶ������Ǽ��ٶȰ�
                 		a[0] = ((short)(Temp[3]<<8 | Temp[2]))/32768.0*16;      //X����ٶ�
                 		a[1] = ((short)(Temp[5]<<8 | Temp[4]))/32768.0*16;      //Y����ٶ�
                 		a[2] = ((short)(Temp[7]<<8 | Temp[6]))/32768.0*16;      //Z����ٶ�
                 		T    = ((short)(Temp[9]<<8 | Temp[8]))/340.0+36.25;      //�¶�
                 	break;		
                 	case 0x52: //��ʶ������ǽ��ٶȰ�
				    	w_flag++;
                    	w[0] = ((short)(Temp[3]<<8| Temp[2]))/32768.0*2000;      //X����ٶ�
                    	w[1] = ((short)(Temp[5]<<8| Temp[4]))/32768.0*2000;      //Y����ٶ�
                    	w[2] = ((short)(Temp[7]<<8| Temp[6]))/32768.0*2000;      //Z����ٶ�
                    	T    = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;      //�¶�
						break;*/	 
                    case 0x53: //��ʶ������ǽǶȰ� 
				    	a_flag++;
                  		angle[0] = ((short)(Temp[3]<<8| Temp[2]))/32768.0*180;   //X���ת�ǣ�x �ᣩ
                  		angle[1] = ((short)(Temp[5]<<8| Temp[4]))/32768.0*180;   //Y�ḩ���ǣ�y �ᣩ
                  		angle[2] = ((short)(Temp[7]<<8| Temp[6]))/32768.0*180;   //Z��ƫ���ǣ�z �ᣩ
						printf("ƽ̨�Ƕ�:%4.2f\n",angle[1]);
						break;						
            }
		if((a_flag!=0))
		{
		a_flag=0;	
     	break;
		}	
         }	   
      }	  	 		
	}//while����

}//getmpu()


