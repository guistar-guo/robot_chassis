/**
  ******************************************************************************
  * File Name          : fsi6_control_motor.c
  * Description        : 富斯i6遥控应用
	* @author            : SuperEgo-郭耀辉 
  ******************************************************************************
  * @attention
  *
  * 该文件调用sbus模块的SBUS_CH结构体来获取解析后的sbus的所有通道值，然后通过
	* 区间映射函数将通道值映射到电机结构体的speed成员上，完成遥控控制电机的任务。
  *
  ******************************************************************************
  */
#include "fsi6_control_motor.h"

float fsi6_v_x = 0;
float fsi6_v_y = 0;
float fsi6_v_w = 0;
float fsi6_v_max = 80;

/**************************************************************************
函数功能：区间映射函数，将区间[cur_left, cur_right]内的某个数x映射到区间
					[mapping_left, mapping_right]的另一个数，并将其返回
入口参数：代映射值x，原区间上下限cur_left, cur_right；映射区间上下限mapping_left, mapping_right
返回  值：float类型的映射结果
**************************************************************************/
static float Interval_mapping(float x, float cur_left,\
	float cur_right, float mapping_left, float mapping_right)
{
	return mapping_left + (x - cur_left)/(cur_right - cur_left) * \
		(mapping_right - mapping_left);
}


/**************************************************************************
函数功能：接收sbus协议的数据进行底盘控制（麦轮混控）
					2通道控制前进后退；1通道控制左右平移；4通道控制自转；9通道（拨杆）控制速度档位
入口参数：无
返回  值：无
**************************************************************************/
void fsi6_control(void)
{
	if(SBUS_CH.CH9<624){
		fsi6_v_max = 80;
	}else if((SBUS_CH.CH9<1424)&&(SBUS_CH.CH9>624)){
		fsi6_v_max = 50;
	}else if(SBUS_CH.CH9>1424){
		fsi6_v_max = 20;
	}
	
	fsi6_v_x = Interval_mapping(SBUS_CH.CH2, 224, 1824, -fsi6_v_max, fsi6_v_max)*k_Speed_calibration;
	fsi6_v_y = Interval_mapping(SBUS_CH.CH1, 224, 1824, -fsi6_v_max, fsi6_v_max)*k_Speed_calibration;
	fsi6_v_w = Interval_mapping(SBUS_CH.CH4, 224, 1824, -fsi6_v_max, fsi6_v_max)*k_Speed_calibration/k_rad_calibration;
	
	chassis_control(fsi6_v_x,fsi6_v_y*POLARITY_CHANGE,fsi6_v_w*POLARITY_CHANGE);
}






















