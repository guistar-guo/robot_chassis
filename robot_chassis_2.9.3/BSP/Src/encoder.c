/**
  ******************************************************************************
  * File Name          : encoder.c
  * Description        : 编码器驱动代码
	* @author            : SuperEgo-郭耀辉
  ******************************************************************************
  * @attention
  *
  * motor.c中的电机对象，其成员中有两个与编码器有关的函数指针，其最终都指向
	*	这个文件里面定义的函数
	*	用户可调用oled_show_encoder来打印出四个编码器的当前计次值
  *
  ******************************************************************************
  */

#include "encoder.h"

void encoder_init(void)
{
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);//开启TIM2的编码器接口模式
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);//开启TIM3的编码器接口模式
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);//开启TIM4的编码器接口模式
	HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);//开启TIM5的编码器接口模式
}

int iTim2Encoder;
int GetEncoderA(void)
{
    iTim2Encoder = (short)(__HAL_TIM_GET_COUNTER(&htim2));//先读取脉冲数
    //__HAL_TIM_SET_COUNTER(&htim2,0);//再计数器清零
	
    return ENCODERA_POLARITY*iTim2Encoder;//返回脉冲数
}

int iTim3Encoder;
int GetEncoderB(void)
{
    iTim3Encoder = (short)(__HAL_TIM_GET_COUNTER(&htim3));//先读取脉冲数
    //__HAL_TIM_SET_COUNTER(&htim3,0);//再计数器清零
    return ENCODERB_POLARITY*iTim3Encoder;//返回脉冲数
}

int iTim4Encoder;
int GetEncoderC(void)
{
    iTim4Encoder = (short)(__HAL_TIM_GET_COUNTER(&htim4));//先读取脉冲数
    //__HAL_TIM_SET_COUNTER(&htim4,0);//再计数器清零
    return ENCODERC_POLARITY*iTim4Encoder;//返回脉冲数
}

int iTim5Encoder;
int GetEncoderD(void)
{
    iTim5Encoder = (short)(__HAL_TIM_GET_COUNTER(&htim5));//先读取脉冲数
    //__HAL_TIM_SET_COUNTER(&htim5,0);//再计数器清零
    return ENCODERD_POLARITY*iTim5Encoder;//返回脉冲数
}

void encoderA_clear(void)
{
	__HAL_TIM_SET_COUNTER(&htim2,0);//再计数器清零
}

void encoderB_clear(void)
{
	__HAL_TIM_SET_COUNTER(&htim3,0);//再计数器清零
}

void encoderC_clear(void)
{
	__HAL_TIM_SET_COUNTER(&htim4,0);//再计数器清零
}

void encoderD_clear(void)
{
	__HAL_TIM_SET_COUNTER(&htim5,0);//再计数器清零
}

extern int cur_D_speed;
char oled_str[100];
//以下函数将四个编码器的值全部显示在oled屏幕上面
void oled_show_encoder(void)
{
	sprintf(oled_str,"%5d", motorA.get_encoder());
	OLED_ShowString(30, 12, (u8*)oled_str);
	OLED_ShowString(0, 12, (u8*)"EA:");
	
	sprintf(oled_str,"%5d", motorB.get_encoder());
	OLED_ShowString(30, 24, (u8*)oled_str);
	OLED_ShowString(0, 24, (u8*)"EB:");
	
	sprintf(oled_str,"%5d", motorC.get_encoder());
	OLED_ShowString(30, 36, (u8*)oled_str);
	OLED_ShowString(0, 36, (u8*)"EC:");
	
	sprintf(oled_str,"%5d", motorD.get_encoder());
	OLED_ShowString(30, 48, (u8*)oled_str);
	OLED_ShowString(0, 48, (u8*)"ED:");
	
	OLED_Refresh_Gram();
}












