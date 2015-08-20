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
     		if(Temp[0]==0x55)       //检查帧头
     		{  
     			switch(Temp[1])
        		{
               		/*case 0x51: //标识这个包是加速度包
                 		a[0] = ((short)(Temp[3]<<8 | Temp[2]))/32768.0*16;      //X轴加速度
                 		a[1] = ((short)(Temp[5]<<8 | Temp[4]))/32768.0*16;      //Y轴加速度
                 		a[2] = ((short)(Temp[7]<<8 | Temp[6]))/32768.0*16;      //Z轴加速度
                 		T    = ((short)(Temp[9]<<8 | Temp[8]))/340.0+36.25;      //温度
                 	break;		
                 	case 0x52: //标识这个包是角速度包
				    	w_flag++;
                    	w[0] = ((short)(Temp[3]<<8| Temp[2]))/32768.0*2000;      //X轴角速度
                    	w[1] = ((short)(Temp[5]<<8| Temp[4]))/32768.0*2000;      //Y轴角速度
                    	w[2] = ((short)(Temp[7]<<8| Temp[6]))/32768.0*2000;      //Z轴角速度
                    	T    = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;      //温度
						break;*/	 
                    case 0x53: //标识这个包是角度包 
				    	a_flag++;
                  		angle[0] = ((short)(Temp[3]<<8| Temp[2]))/32768.0*180;   //X轴滚转角（x 轴）
                  		angle[1] = ((short)(Temp[5]<<8| Temp[4]))/32768.0*180;   //Y轴俯仰角（y 轴）
                  		angle[2] = ((short)(Temp[7]<<8| Temp[6]))/32768.0*180;   //Z轴偏航角（z 轴）
						printf("平台角度:%4.2f\n",angle[1]);
						break;						
            }
		if((a_flag!=0))
		{
		a_flag=0;	
     	break;
		}	
         }	   
      }	  	 		
	}//while结束

}//getmpu()


