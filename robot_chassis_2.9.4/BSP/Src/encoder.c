/**
  ******************************************************************************
  * File Name          : encoder.c
  * Description        : ��������������
	* @author            : SuperEgo-��ҫ��
  ******************************************************************************
  * @attention
  *
  * motor.c�еĵ���������Ա����������������йصĺ���ָ�룬�����ն�ָ��
	*	����ļ����涨��ĺ���
	*	�û��ɵ���oled_show_encoder����ӡ���ĸ��������ĵ�ǰ�ƴ�ֵ
  *
  ******************************************************************************
  */

#include "encoder.h"

void encoder_init(void)
{
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);//����TIM2�ı������ӿ�ģʽ
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);//����TIM3�ı������ӿ�ģʽ
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);//����TIM4�ı������ӿ�ģʽ
	HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);//����TIM5�ı������ӿ�ģʽ
}

int iTim2Encoder;
int GetEncoderA(void)
{
    iTim2Encoder = (short)(__HAL_TIM_GET_COUNTER(&htim2));//�ȶ�ȡ������
    //__HAL_TIM_SET_COUNTER(&htim2,0);//�ټ���������
	
    return ENCODERA_POLARITY*iTim2Encoder;//����������
}

int iTim3Encoder;
int GetEncoderB(void)
{
    iTim3Encoder = (short)(__HAL_TIM_GET_COUNTER(&htim3));//�ȶ�ȡ������
    //__HAL_TIM_SET_COUNTER(&htim3,0);//�ټ���������
    return ENCODERB_POLARITY*iTim3Encoder;//����������
}

int iTim4Encoder;
int GetEncoderC(void)
{
    iTim4Encoder = (short)(__HAL_TIM_GET_COUNTER(&htim4));//�ȶ�ȡ������
    //__HAL_TIM_SET_COUNTER(&htim4,0);//�ټ���������
    return ENCODERC_POLARITY*iTim4Encoder;//����������
}

int iTim5Encoder;
int GetEncoderD(void)
{
    iTim5Encoder = (short)(__HAL_TIM_GET_COUNTER(&htim5));//�ȶ�ȡ������
    //__HAL_TIM_SET_COUNTER(&htim5,0);//�ټ���������
    return ENCODERD_POLARITY*iTim5Encoder;//����������
}

void encoderA_clear(void)
{
	__HAL_TIM_SET_COUNTER(&htim2,0);//�ټ���������
}

void encoderB_clear(void)
{
	__HAL_TIM_SET_COUNTER(&htim3,0);//�ټ���������
}

void encoderC_clear(void)
{
	__HAL_TIM_SET_COUNTER(&htim4,0);//�ټ���������
}

void encoderD_clear(void)
{
	__HAL_TIM_SET_COUNTER(&htim5,0);//�ټ���������
}

extern int cur_D_speed;
char oled_str[100];
//���º������ĸ���������ֵȫ����ʾ��oled��Ļ����
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












