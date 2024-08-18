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

void fsi6_control(void)
{
	chassis_control(Interval_mapping(SBUS_CH.CH2, 224, 1824, -80, 80),\
									Interval_mapping(SBUS_CH.CH1, 224, 1824, -80, 80),\
									Interval_mapping(SBUS_CH.CH4, 224, 1824, -80, 80));
}






















