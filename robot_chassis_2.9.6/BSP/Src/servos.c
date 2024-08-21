/**
  ******************************************************************************
  * File Name          : servos.c
  * Description        : 舵机驱动代码
	* @author            : SuperEgo-郭耀辉
  ******************************************************************************
  * @attention
  *
  * 例：servos1_set_angle(89); //设置舵机1的角度为89度(参数输入范围0到180)
  *
  ******************************************************************************
  */

#include "servos.h"

/**************************************************************************
函数功能：区间映射函数，将区间[cur_left, cur_right]内的某个数x映射到区间
					[mapping_left, mapping_right]的另一个数，并将其返回
入口参数：无
返回  值：无
**************************************************************************/
static float Interval_mapping(float x, float cur_left,\
	float cur_right, float mapping_left, float mapping_right)
{
	return mapping_left + (x - cur_left)/(cur_right - cur_left) * \
		(mapping_right - mapping_left);
}

/**************************************************************************
函数功能：设置舵机1的角度
入口参数：angle，要设置的角度，范围0到180度
返回  值：无
**************************************************************************/
void servos1_set_angle(float angle)
{
	uint16_t THE_CCR = Interval_mapping(angle, 0, 180, 1000, 2000);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, THE_CCR);
}

/**************************************************************************
函数功能：设置舵机2的角度
入口参数：angle，要设置的角度，范围0到180度
返回  值：无
**************************************************************************/
void servos2_set_angle(float angle)
{
	uint16_t THE_CCR = Interval_mapping(angle, 0, 180, 1000, 2000);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, THE_CCR);
}

/**************************************************************************
函数功能：设置舵机3的角度
入口参数：angle，要设置的角度，范围0到180度
返回  值：无
**************************************************************************/
void servos3_set_angle(float angle)
{
	uint16_t THE_CCR = Interval_mapping(angle, 0, 180, 1000, 2000);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, THE_CCR);
}

/**************************************************************************
函数功能：设置舵机4的角度
入口参数：angle，要设置的角度，范围0到180度
返回  值：无
**************************************************************************/
void servos4_set_angle(float angle)
{
	uint16_t THE_CCR = Interval_mapping(angle, 0, 180, 1000, 2000);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, THE_CCR);
}

/**************************************************************************
函数功能：设置舵机5的角度
入口参数：angle，要设置的角度，范围0到180度
返回  值：无
**************************************************************************/
void servos5_set_angle(float angle)
{
	uint16_t THE_CCR = Interval_mapping(angle, 0, 180, 1000, 2000);
	__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, THE_CCR);
}

/**************************************************************************
函数功能：初始化5个舵机，此函数在system.c中的system_init函数中调用
入口参数：无
返回  值：无
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
















