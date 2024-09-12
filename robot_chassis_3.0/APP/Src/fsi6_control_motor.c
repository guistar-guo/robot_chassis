/**
  ******************************************************************************
  * File Name          : fsi6_control_motor.c
  * Description        : ��˹i6ң��Ӧ��
	* @author            : SuperEgo-��ҫ�� 
  ******************************************************************************
  * @attention
  *
  * ���ļ�����sbusģ���SBUS_CH�ṹ������ȡ�������sbus������ͨ��ֵ��Ȼ��ͨ��
	* ����ӳ�亯����ͨ��ֵӳ�䵽����ṹ���speed��Ա�ϣ����ң�ؿ��Ƶ��������
  *
  ******************************************************************************
  */
#include "fsi6_control_motor.h"

float fsi6_v_x = 0;
float fsi6_v_y = 0;
float fsi6_v_w = 0;
float fsi6_v_max = 80;

/**************************************************************************
�������ܣ�����ӳ�亯����������[cur_left, cur_right]�ڵ�ĳ����xӳ�䵽����
					[mapping_left, mapping_right]����һ�����������䷵��
��ڲ�������ӳ��ֵx��ԭ����������cur_left, cur_right��ӳ������������mapping_left, mapping_right
����  ֵ��float���͵�ӳ����
**************************************************************************/
static float Interval_mapping(float x, float cur_left,\
	float cur_right, float mapping_left, float mapping_right)
{
	return mapping_left + (x - cur_left)/(cur_right - cur_left) * \
		(mapping_right - mapping_left);
}


/**************************************************************************
�������ܣ�����sbusЭ������ݽ��е��̿��ƣ����ֻ�أ�
					2ͨ������ǰ�����ˣ�1ͨ����������ƽ�ƣ�4ͨ��������ת��9ͨ�������ˣ������ٶȵ�λ
��ڲ�������
����  ֵ����
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






















