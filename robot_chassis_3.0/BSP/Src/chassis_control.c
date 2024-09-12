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



/**************************************************************************
�������ܣ����̿��ƣ����ֻ�أ�
��ڲ�����x,y,w�������˶�������ٶ�,xǰ������,��λΪmm/s��
																		y����ƽ�ƣ���λΪmm/s��
																		w��ת���ٶ�,��λΪ1000rad/s
����  ֵ����
**************************************************************************/
void chassis_control(float vx,float vy,float vw)
{
	vx = vx/k_Speed_calibration;
	vy = vy/k_Speed_calibration;
	vw = vw/k_Speed_calibration*k_rad_calibration;
	short va,vb,vc,vd;
	va = vx-vy-vw;
	vb = vx+vy+vw;
	vc = vx-vy+vw;
	vd = vx+vy-vw;
	
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

/**************************************************************************
�������ܣ�����ros���ڵ����ݽ��е��̿��ƣ����ֻ�أ�
��ڲ�������
����  ֵ����
**************************************************************************/


void chassis_ros_control(void){
	chassis_control(*ros_upper_computer.x_target_speed,\
									*ros_upper_computer.y_target_speed,\
									*ros_upper_computer.z_target_speed);
}

void chassis_control_test(void)
{
	osDelay(3000);
	chassis_control(0,0,1570);
	osDelay(2000);
	chassis_control(0,0,0);
	while(1)
	{
		
		osDelay(1);//������ʱ
	}
}













