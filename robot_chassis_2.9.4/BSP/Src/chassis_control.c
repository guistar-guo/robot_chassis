/**
  ******************************************************************************
  * File Name          : chassis_control.c
  * Description        : ���ֵ��̿���
	* @author            : ��ƴ�-������ʵ����-������
  ******************************************************************************
  * @attention
  * ros��������xyz������ٶ���chassis_control��������chassis_ros_control������
	* λ�����յ����ٶ�ָ����Ϊ��������chassis_control������ִ����λ�����ٶ�ָ��
  *
  ******************************************************************************
  */

#include "chassis_control.h"

void chassis_control(short x,short y,short w)
{
	short va,vb,vc,vd;
	va = x+y+w;
	vb = x-y-w;
	vc = x+y-w;
	vd = x-y+w;
	
	va = va > MOTOR_SPEED_MAX ? MOTOR_SPEED_MAX : va;
	va = va < -MOTOR_SPEED_MAX ? -MOTOR_SPEED_MAX : va;
	vb = vb > MOTOR_SPEED_MAX ? MOTOR_SPEED_MAX : vb;
	vb = vb < -MOTOR_SPEED_MAX ? -MOTOR_SPEED_MAX : vb;
	vc = vc > MOTOR_SPEED_MAX ? MOTOR_SPEED_MAX : vc;
	vc = vc < -MOTOR_SPEED_MAX ? -MOTOR_SPEED_MAX : vc;
	vd = vd > MOTOR_SPEED_MAX ? MOTOR_SPEED_MAX : vd;
	vd = vd < -MOTOR_SPEED_MAX ? -MOTOR_SPEED_MAX : vd;
	
	motorA.speed = va;
	motorB.speed = vb;
	motorC.speed = vc;
	motorD.speed = vd;
}

void chassis_ros_control(void){
	chassis_control((short)*ros_upper_computer.x_target_speed,\
									(short)*ros_upper_computer.y_target_speed,\
									(short)*ros_upper_computer.z_target_speed);
}

void chassis_control_test(void)
{
	
	while(1)
	{
		osDelay(1);//������ʱ
	}
}













