#include "mpu6050.h"
#include "string.h"

extern unsigned char Re_buf[11],sign;
float angle[3],a[3],w[3];
float T;
float mpu6050_get(void)
{
	unsigned char Temp[11];
	if(sign)
	{
		memcpy(Temp,Re_buf,11);
		sign=0;
		if(Re_buf[0]==0x55)       //检查帧头
		{  
			 switch(Re_buf[1])
			 {
			   case 0x51: //标识这个包是加速度包
				  a[0] = ((short)(Temp[3]<<8 | Temp[2]))/32768.0*16;      //X轴加速度
				  a[1] = ((short)(Temp[5]<<8 | Temp[4]))/32768.0*16;      //Y轴加速度
				  a[2] = ((short)(Temp[7]<<8 | Temp[6]))/32768.0*16;      //Z轴加速度
				  T    = ((short)(Temp[9]<<8 | Temp[8]))/340.0+36.25;      //温度
				  break;
			   case 0x52: //标识这个包是角速度包
				  w[0] = ((short)(Temp[3]<<8| Temp[2]))/32768.0*2000;      //X轴角速度
				  w[1] = ((short)(Temp[5]<<8| Temp[4]))/32768.0*2000;      //Y轴角速度
				  w[2] = ((short)(Temp[7]<<8| Temp[6]))/32768.0*2000;      //Z轴角速度
				  T    = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;      //温度
				  break;
			   case 0x53: //标识这个包是角度包
				  angle[0] = ((short)(Temp[3]<<8| Temp[2]))/32768.0*180;   //X轴滚转角（x 轴）
				  angle[1] = ((short)(Temp[5]<<8| Temp[4]))/32768.0*180;   //Y轴俯仰角（y 轴）
				  angle[2] = ((short)(Temp[7]<<8| Temp[6]))/32768.0*180;   //Z轴偏航角（z 轴）
				  //T        = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;   //温度
					break;
			   default:  break;
			  }
			//printf("X角度：%.2f  Y角度：%.2f  Z角度：%.2f  X速度：%.2f  Y速度：%.2f  Z速度：%.2f\r\n",angle[0],angle[1],angle[2],w[0],w[1],w[2]);
			return angle[0];
		}
        
	 }
     return 0;
 }
