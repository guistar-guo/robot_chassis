/**
  ******************************************************************************
  * File Name          : servos.c
  * Description        : �����������
	* @author            : SuperEgo-��ҫ��
  ******************************************************************************
  * @attention
  *
  * ����servos1_set_angle(89); //���ö��1�ĽǶ�Ϊ89��(�������뷶Χ0��180)
  *
  ******************************************************************************
  */

#include "servos.h"

/**************************************************************************
�������ܣ�����ӳ�亯����������[cur_left, cur_right]�ڵ�ĳ����xӳ�䵽����
					[mapping_left, mapping_right]����һ�����������䷵��
��ڲ�������
����  ֵ����
**************************************************************************/
static float Interval_mapping(float x, float cur_left,\
	float cur_right, float mapping_left, float mapping_right)
{
	return mapping_left + (x - cur_left)/(cur_right - cur_left) * \
		(mapping_right - mapping_left);
}

/**************************************************************************
�������ܣ����ö��1�ĽǶ�
��ڲ�����angle��Ҫ���õĽǶȣ���Χ0��180��
����  ֵ����
**************************************************************************/
void servos1_set_angle(float angle)
{
	uint16_t THE_CCR = Interval_mapping(angle, 0, 180, 1000, 2000);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, THE_CCR);
}

/**************************************************************************
�������ܣ����ö��2�ĽǶ�
��ڲ�����angle��Ҫ���õĽǶȣ���Χ0��180��
����  ֵ����
**************************************************************************/
void servos2_set_angle(float angle)
{
	uint16_t THE_CCR = Interval_mapping(angle, 0, 180, 1000, 2000);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, THE_CCR);
}

/**************************************************************************
�������ܣ����ö��3�ĽǶ�
��ڲ�����angle��Ҫ���õĽǶȣ���Χ0��180��
����  ֵ����
**************************************************************************/
void servos3_set_angle(float angle)
{
	uint16_t THE_CCR = Interval_mapping(angle, 0, 180, 1000, 2000);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, THE_CCR);
}

/**************************************************************************
�������ܣ����ö��4�ĽǶ�
��ڲ�����angle��Ҫ���õĽǶȣ���Χ0��180��
����  ֵ����
**************************************************************************/
void servos4_set_angle(float angle)
{
	uint16_t THE_CCR = Interval_mapping(angle, 0, 180, 1000, 2000);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, THE_CCR);
}

/**************************************************************************
�������ܣ����ö��5�ĽǶ�
��ڲ�����angle��Ҫ���õĽǶȣ���Χ0��180��
����  ֵ����
**************************************************************************/
void servos5_set_angle(float angle)
{
	uint16_t THE_CCR = Interval_mapping(angle, 0, 180, 1000, 2000);
	__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, THE_CCR);
}

/**************************************************************************
�������ܣ���ʼ��5��������˺�����system.c�е�system_init�����е���
��ڲ�������
����  ֵ����
**************************************************************************/
void servos_init(void)
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_1);
	
	servos1_set_angle(90);
	servos2_set_angle(90);
	servos3_set_angle(90);
	servos4_set_angle(90);
	servos5_set_angle(90);
}
















