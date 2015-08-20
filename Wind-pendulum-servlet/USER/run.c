#include "run.h"
#include "usart.h"
#include "24l01.h"
#include "delay.h"
#include "dc_moter.h"
#include "led.h"
#include "mpu6050.h"
#include "math.h"

#define KbuChang  300		// 本宏--用于恒定摆幅能量补偿
#define  K30    0.6
#define  K35    0.65		// 30cm 补诚凳
#define  K40    0.70
#define  K45    0.75
#define  K50    0.83
#define  K55    0.88

#define T3MTR_Time     600   // MT Run time ms
#define D45            0.9
#define D30            0.9

extern float angle[3];			//mpu6050得到的角度

void run1()
{
	u8 ack[2];
	float old_angle,new_angle;
	
	//printf("servlet 1");
	LED1 = 0;
	
	dc_moter_setspeed(2,65000);
	dc_moter_setspeed(4,65000);
	dc_cmd(2,1);
	delay_ms(780);
	dc_cmd(2,0);
	
	dc_cmd(4,1);
	delay_ms(780);
	dc_cmd(4,0);
	
	dc_cmd(2,1);
	delay_ms(780);
	dc_cmd(2,0);
	
	dc_cmd(4,1);
	delay_ms(780);
	dc_cmd(4,0);

	mpu6050_get();
	old_angle = angle[1];
	while(1)
	{
		delay_ms(10);			//By QL 20150814
		mpu6050_get();
		new_angle = angle[1];
		if((new_angle - old_angle)>0)
		{
			dc_cmd(2,1);
			dc_cmd(4,0);
		}
		else if((new_angle - old_angle)<0)
		{
			dc_cmd(4,1);
			dc_cmd(2,0);
		}
		if(new_angle > 15.5)
		{
			Beep(1);
			dc_moter_setspeed(3,50000);
			dc_cmd(1,0);
		}
		if(0 ==NRF24L01_RxPacket(ack))
		{
			Beep(0);
			if(ack[0]  == 's')
			{
				PDout(2)=1;
				dc_cmd(2,0);
				dc_cmd(4,0);
				return;
			}
		}
	}
}


void run2()
{
	u8 ack[2];
	float k;
	u8 run_flag = 0;		// nove dir flag
	u8 tar2_flag;
	float tar2_angle[]={9.9,10.54,11.18,11.82,12.46,13.09,13.73,14.30,14.97,15.59,16.22,16.81,17.40,18.08,18.66,19.2};
	u16 pwm_data[]= {10000,10000,10000,12000,12000,12000,13500,13500,13500,14000,14000,14000,14800,14800,14800,14800};
	float tar2_angle_data[100],tar2_angle_data_max;
	float old_angle,new_angle;
	float x_angle;
	u8 rx_buf[10];
	u8 long_data;
	u8 tar2_check = 1;
	int time_value;
	
	dc_moter_setspeed(2,65000);
	dc_moter_setspeed(4,65000);
	while(1)						//rev data
	{
		if(NRF24L01_RxPacket(rx_buf) == 0)
		{
			break;
		}
	}
	LED1 = 0;
	long_data = rx_buf[0]*10+rx_buf[1];
	if(long_data % 2)
	{
		long_data --;
	}
	//printf("long_data %d",long_data);
	x_angle = tar2_angle[(long_data-30)/2];
	
	if(long_data >= 30 && long_data <35)
	{
		k = K30;
	}
	else if(long_data >= 35 && long_data <40)
	{
		k = K35;
	}
	else if(long_data >= 40 && long_data <45)
	{
		k = K40;
	}
	else if(long_data >= 45 && long_data <50)
	{
		k = K45;
	}
	else if(long_data >= 50 && long_data <55)
	{
		k = K50;
	}
	else if(long_data >= 55 && long_data <=60)
	{
		k = K55;
	}
	
	dc_cmd(2,1);
	delay_ms(780);
	dc_cmd(2,0);
	
	dc_cmd(4,1);
	delay_ms(780);
	dc_cmd(4,0);
	
	dc_cmd(2,1);
	delay_ms(780);
	dc_cmd(2,0);
	
	dc_cmd(4,1);
	delay_ms(780);
	dc_cmd(4,0);
	
	mpu6050_get();
	old_angle = angle[1];
	while(1)
	{
		delay_ms(10);			//By QL 20150814
		mpu6050_get();
		new_angle = angle[1];
		if((new_angle - old_angle)>0)
		{
			dc_cmd(2,1);
			dc_cmd(4,0);
		}
		else if((new_angle - old_angle)<0)
		{
			dc_cmd(4,1);
			dc_cmd(2,0);
		}
		if(new_angle > x_angle)
		{
			Beep(1);
			dc_cmd(2,0);
			break;
		}
		if(0 ==NRF24L01_RxPacket(ack))
		{
			Beep(0);
			if(ack[0]  == 's')
			{
				PDout(2)=1;
				dc_cmd(2,0);
				dc_cmd(4,0);
				return;
			}
		}
	}
	
	time_value = (int)(k * KbuChang);
	
	while(1)			// 摆-----补偿循环
	{
		mpu6050_get();
		old_angle = angle[1];
		delay_ms(10);			//By QL 20150814
		mpu6050_get();
		new_angle = angle[1];
		
		if((new_angle - old_angle)>0 && (run_flag == 0))
		{
			dc_cmd(4,1);			// start MT
			delay_ms(time_value);
			dc_cmd(4,0);			// Stop MT
			run_flag = 1;
		}
		if((new_angle - old_angle)<0)
		{
			run_flag = 0;
		}
		if(0 ==NRF24L01_RxPacket(ack))
		{
			Beep(0);
			if(ack[0]  == 's')
			{
				PDout(2)=1;
				dc_cmd(2,0);
				dc_cmd(4,0);
				return;
			}
		}
	}
}

void run3()
{
	u8 tar3_time;
	int i;
	float old_angle,new_angle;
	int x1_pwm_data[20] = {65000,65000,60000,60000,65000,48000,45000,40000,30000,0};
	int y1_pwm_data[20] = {0,35000,40000,55000,65000,60000,60000,60000,60000,60000};
	int x2_pwm_data[20] = {45000,48000,65000,60000,60000,65000,65000,65000};
	int y2_pwm_data[20] = {60000,60000,65000,55000,40000,35000,32000,30000};
	u8 dir = 0;
    float x_max_angle,y_max_angle;
	float x_angle;
	float x_old_angle,x_new_angle,y_old_angle,y_new_angle;
	u8 tar3_flag = 0;
	int k = 0;
	int x_pwm,y_pwm;
	u8 rx_buf[10];
	int long_angle;
	//printf("servlet3");
	while(1)
	{
		if(NRF24L01_RxPacket(rx_buf) == 0)
		{
			break;
		}
	}
	LED1 = 0;
	long_angle = rx_buf[0]*100+rx_buf[1]*10+rx_buf[2];
	
	if(long_angle > 180)
	{
		long_angle = 360 -long_angle;
	}
	printf("long_angle %d",long_angle);
	
	if(long_angle <= 90)
	{
		tar3_flag = 0;			// xiang xian 1
	}
	else if(long_angle > 90)
	{
		tar3_flag = 1;			// xiang xian 2
	}
	tar3_time = 12;
	if(long_angle > 45 && long_angle < 135)
	{
		tar3_time = 6;
	}

	if(tar3_flag == 0)			// area 1 process
	{
	
		x_pwm = x1_pwm_data[(long_angle)/10];
		y_pwm = y1_pwm_data[(long_angle)/10];
		//printf("x_pwm %d y_pwm %d",x_pwm,y_pwm);
		
		dc_moter_setspeed(1,x_pwm);
		dc_moter_setspeed(2,y_pwm);
		dc_moter_setspeed(3,x_pwm);
		dc_moter_setspeed(4,y_pwm);
		i = 0;
		while(1)
		{
			i++;
			dc_cmd(1,0);	// move to XX_1
			dc_cmd(2,0);
			dc_cmd(3,1);	
			dc_cmd(4,1);
			delay_ms(800);
			
			dc_cmd(3,0);	// move to XX_3
			dc_cmd(4,0);
			dc_cmd(1,1);
			dc_cmd(2,1);
			delay_ms(800);
			if((i*1.6)>tar3_time)
			{
				dc_cmd(3,0);	// move to XX_3
				dc_cmd(4,0);
				dc_cmd(1,0);
				dc_cmd(2,0);
				PCout(0) = 1;
				return ;
			}
		}
		
	}
	else if(tar3_flag == 1)
	{
		x_pwm = x2_pwm_data[(long_angle-100)/10];
		y_pwm = y2_pwm_data[(long_angle-100)/10];
		printf("x_pwm %d y_pwm %d",x_pwm,y_pwm);
		
		dc_moter_setspeed(1,x_pwm);
		dc_moter_setspeed(2,y_pwm);
		dc_moter_setspeed(3,x_pwm);
		dc_moter_setspeed(4,y_pwm);
		
		i = 0;
		while(1)
		{
			i++;
			dc_cmd(1,0);	// move to XX_1
			dc_cmd(4,0);
			dc_cmd(2,1);	
			dc_cmd(3,1);
			delay_ms(800);
			
			dc_cmd(2,0);	// move to XX_3
			dc_cmd(3,0);
			dc_cmd(1,1);
			dc_cmd(4,1);
			delay_ms(800);
			
			if((i*1.6)>tar3_time)
			{
				dc_cmd(3,0);	// move to XX_3
				dc_cmd(4,0);
				dc_cmd(1,0);
				dc_cmd(2,0);
				PCout(0) = 1;
				//tar3_time_flag = 0;
				return ;
			}
		}
	}
	
}
void run4()
{
	u8 run4_flag = 0 ,run4_flag1 = 0;
	int x_count = 0,y_count = 0;
	u8 i = 0;
	float x_old_angle,x_new_angle,y_old_angle,y_new_angle;
	//printf("servlet 4");
	LED1 = 0;
	dc_moter_setspeed(1,65000);
	dc_moter_setspeed(2,65000);
	dc_moter_setspeed(3,65000);
	dc_moter_setspeed(4,65000);
	


	for(i = 0; i < 20; i++)
	{
		mpu6050_get();
		x_old_angle += angle[0];
		y_old_angle += angle[1];
		delay_ms(20);
	}
	x_old_angle = x_old_angle / i;
	y_old_angle = y_old_angle / i;
	
	while(1)
	{
		mpu6050_get();
		delay_ms(25);			//By QL 20150814
		x_new_angle = angle[0];
		y_new_angle = angle[1];
		if((x_new_angle -x_old_angle)> 3)
		{
			x_count = 0;
			dc_cmd(3,1);
			dc_cmd(1,0);
		}
		else if((x_new_angle -x_old_angle)<-3)
		{
			x_count = 0;
			dc_cmd(3,0);
			dc_cmd(1,1);
		}
		if((y_new_angle-y_old_angle)> 3)
		{
			y_count = 0;
			dc_cmd(4,1);
			dc_cmd(2,0);
		}
		if((y_new_angle-y_old_angle) < -3)
		{
			y_count = 0;
			dc_cmd(4,0);
			dc_cmd(2,1);
		}
		if(((x_new_angle -x_old_angle)<=3) && (x_new_angle -x_old_angle)>=-3)
		{
			x_count ++;
			if(x_count == 20)
			{
				run4_flag ++;
				dc_cmd(3,0);
				dc_cmd(1,0);
			}
		}
		if(((y_new_angle -y_old_angle)<=3) && (y_new_angle -y_old_angle)>=-3)
		{
			y_count ++;
			if(y_count == 20)
			{
				run4_flag1 ++;
				dc_cmd(2,0);
				dc_cmd(4,0);
			}
		}
		if((run4_flag1 > 5)&&(run4_flag > 5))
		{
			PCout(0) = 1;
			return ;
		}
	}
	LED1 = 1;
}

/************************************************************************************************
**功能说明：风力摆画圆----T5
** 入口: void , 默认进来时，all fan ---- STOP
** 出口: void
**
** 风扇方向约定: 此约定相关与 mpu6050 角度测试的---度数(x,y)
**										FS_YZ
**						FS_XF             FS_XZ
**                    FS_YF
**
** MPU6050方向标定：
**                    Y+ 度数
**             X- 度数        X+ 度数
**                    Y- 度数
************************************************************************************************/
//风扇描述----1,2,3,4 好风扇应依据实际位置---标定
#define FS_XZ   1
#define FS_YZ   2
#define FS_XF   3
#define FS_YF   4

#define Cycle_T 1600			// 1600ms
#define NUM     100				// 画圆一周---风扇动力改变分辨率
#define CKN			3					// 角度采样次数----用于求均值
#define MT_T   Cycle_T/NUM		// 风扇动力修改周期

#define TYC_DR	1					// 投影园 的----半径与最大园半径比率,取值范围: 0~1

void run5()
{

//	u8 zql_ctrl=0;			// By ZqL
	u8 dr = 0;					// 画圆的半径
	int i;
	
	int zql_x_pwm,zql_y_pwm;
	int x_pwm,y_pwm;
	
	float old_x_angle=0;  		//次角度值----X 方向
	float old_y_angle=0;  		// 次角度值----y 方向
	float new_x_angle,new_y_angle;		// 次角度值 ---- 均值
	
	int long_angle;
	
	// Start
	dc_moter_setspeed(1,MAX_PWM);
	dc_moter_setspeed(2,MAX_PWM);
	dc_moter_setspeed(3,MAX_PWM);
	dc_moter_setspeed(4,MAX_PWM);
	
//	y_pwm = MAX_PWM;
//	x_pwm = MAX_PWM;
	
	dc_cmd(FS_XZ,1);			// STR Fan FS_XZ
	dc_cmd(FS_YZ,0);			// STR Fan FS_yZ
	dc_cmd(FS_XF,0);			// STp Fan FS_XF
	dc_cmd(FS_YF,0);			// STR Fan FS_YF
	delay_ms(800);
	dc_cmd(FS_XZ,0);			// STR Fan FS_XZ
	dc_cmd(FS_YZ,0);			// STR Fan FS_yZ
	dc_cmd(FS_XF,0);			// STp Fan FS_XF
	dc_cmd(FS_YF,0);			// STR Fan FS_YF
	
	dc_cmd(FS_XZ,0);			// STR Fan FS_XZ
	dc_cmd(FS_YZ,0);			// STR Fan FS_yZ
	dc_cmd(FS_XF,1);			// STp Fan FS_XF
	dc_cmd(FS_YF,0);			// STR Fan FS_YF
	delay_ms(800);
	dc_cmd(FS_XZ,0);			// STR Fan FS_XZ
	dc_cmd(FS_YZ,0);			// STR Fan FS_yZ
	dc_cmd(FS_XF,0);			// STp Fan FS_XF
	dc_cmd(FS_YF,0);			// STR Fan FS_YF
	
	mpu6050_get();
	old_x_angle = angle[0];		// x角度值
	old_y_angle = angle[1];		// y角度值
	delay_ms(10);	
	
	while (1)
	{
		mpu6050_get();
		new_x_angle = angle[0];		// x角度值
		new_y_angle = angle[1];		// y角度值
		if((new_x_angle >= 0) && (new_y_angle >= 0))		// 第1相限,FS_XZ & FS_YF
		{
			dc_cmd(FS_XZ,1);			// STR Fan FS_XZ
			dc_cmd(FS_YZ,0);			// STR Fan FS_yZ
			dc_cmd(FS_XF,0);			// STp Fan FS_XF
			dc_cmd(FS_YF,1);			// STR Fan FS_YF
			//delay_ms(150);
		}
		else if((new_x_angle <= 0) && (new_y_angle >= 0))		// 第2相限,FS_XZ & FS_YZ
		{
			dc_cmd(FS_XZ,1);			// STR Fan FS_XZ
			dc_cmd(FS_YZ,1);			// STR Fan FS_yZ
			dc_cmd(FS_XF,0);			// STp Fan FS_XF
			dc_cmd(FS_YF,0);			// STR Fan FS_YF
			//delay_ms(150);
		}
		else if((new_x_angle <= 0) && (new_y_angle <= 0))		// 第3相限,FS_XF & FS_YZ
		{
			dc_cmd(FS_XZ,0);			// STR Fan FS_XZ
			dc_cmd(FS_YZ,1);			// STR Fan FS_yZ
			dc_cmd(FS_XF,1);			// STp Fan FS_XF
			dc_cmd(FS_YF,0);			// STR Fan FS_YF
			//delay_ms(150);
		}
		else if((new_x_angle >= 0) && (new_y_angle <= 0))   // 第4相限,FS_XF & FS_YF
		{
			dc_cmd(FS_XZ,0);			// STR Fan FS_XZ
			dc_cmd(FS_YZ,0);			// STR Fan FS_yZ
			dc_cmd(FS_XF,1);			// STp Fan FS_XF
			dc_cmd(FS_YF,1);			// STR Fan FS_YF
			//delay_ms(150);
		}		
			
	}
}


