#include "dc_moter.h"


void dc_moter_init()
{
	MY_GPIO_Init();
	TIM3_Config(); 
	TIM4_Config();
}


void MY_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure; 
 
  /* GPIOA and GPIOB clock enable */ 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  
 
  /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */ 
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           // ?????? 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
	

  /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */ 
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5 | GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_4; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;           // ?????? 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
  GPIO_SetBits(GPIOB,GPIO_Pin_5 | GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_4);
	
	 /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */ 
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           // ?????? 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
	

  /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */ 
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12 | GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;           // ?????? 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
  GPIO_SetBits(GPIOB,GPIO_Pin_12 | GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
}	

/*
	last 500
*/
void dc_moter_setspeed(int flag,int speed)
{
	switch(flag)
	{
		case 1:	TIM_SetCompare3(TIM3,speed); break;
		case 2:	TIM_SetCompare4(TIM3,speed); break;
		case 3:	TIM_SetCompare3(TIM4,speed); break;
		case 4:	TIM_SetCompare4(TIM4,speed); break;
	}
}

void TIM3_Config(void)  
{  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
    TIM_OCInitTypeDef  TIM_OCInitStructure;  
    /* PWM??????? */  
    u16 CCR1= 36000;          
    u16 CCR2= 36000;  
    /*PCLK1??2?????TIM3??????72MHz*/  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  
    /* Time base configuration */                                            
    TIM_TimeBaseStructure.TIM_Period =0xEA5F;  
    TIM_TimeBaseStructure.TIM_Prescaler = 2;                                    //?????:???=2,??72/3=24MHz  
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;                                //????????:???  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                 //????????  
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  
    /* PWM1 Mode configuration: Channel1 */  
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                           //???PWM??1  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                
    TIM_OCInitStructure.TIM_Pulse = CCR1;                                       //?????,???????????,??????  
    TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;                    //?????????CCR1?????  
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);                                    //????1      
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  
    /* PWM1 Mode configuration: Channel2 */  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
    TIM_OCInitStructure.TIM_Pulse = CCR2;                                       //????2??????,??????????PWM  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;                    //?????????CCR2????? 
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);                                    //????2  
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  
    TIM_ARRPreloadConfig(TIM3, ENABLE);                                         //??TIM3?????ARR  
    /* TIM3 enable counter */                                                       //??TIM3   
} 

void TIM4_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
    TIM_OCInitTypeDef  TIM_OCInitStructure;  
    /* PWM??????? */  
    u16 CCR1= 36000;          
    u16 CCR2= 36000;  
    /*PCLK1??2?????TIM3??????72MHz*/  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  
    /* Time base configuration */                                            
    TIM_TimeBaseStructure.TIM_Period =0xEA5F;  
    TIM_TimeBaseStructure.TIM_Prescaler = 2;                                    //?????:???=2,??72/3=24MHz  
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;                                //????????:???  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                 //????????  
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);  
    /* PWM1 Mode configuration: Channel1 */  
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                           //???PWM??1  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                
    TIM_OCInitStructure.TIM_Pulse = CCR1;                                       //?????,???????????,??????  
    TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;                    //?????????CCR1?????  
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);                                    //????1      
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  
    /* PWM1 Mode configuration: Channel2 */  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
    TIM_OCInitStructure.TIM_Pulse = CCR2;                                       //????2??????,??????????PWM  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;                    //?????????CCR2????? 
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);                                    //????2  
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  
    TIM_ARRPreloadConfig(TIM4, ENABLE);                                         //??TIM3?????ARR  
    /* TIM3 enable counter */                      
}


void dc_cmd(int num,int cmd)
{
	if(cmd == 1)		//start
	{
		switch(num)
		{
			case 1:	PBout(4) = 1;  PBout(5) = 0;	break;
			case 2:	PBout(6) = 1;  PBout(7) = 0;	break;
			case 3:	PBout(12) = 1;  PBout(13) = 0;	break;
			case 4:	PBout(14) = 1;  PBout(15) = 0;	break;
			default:								break;
		}
	}
	else if(cmd == 0)	//stop
	{
		switch(num)
		{
			case 1:	PBout(4) = 1;  PBout(5) = 1;	break;
			case 2:	PBout(6) = 1;  PBout(7) = 1;	break;
			case 3:	PBout(12) = 1;  PBout(13) = 1;	break;
			case 4:	PBout(14) = 1;  PBout(15) = 1;	break;
			default:								break;
		}
	}
}

