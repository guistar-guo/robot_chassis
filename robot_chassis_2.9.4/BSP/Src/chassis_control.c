/**
  ******************************************************************************
  * File Name          : chassis_control.c
  * Description        : 麦轮底盘控制
	* @author            : 天科大-机器人实验室-吴树涛
  ******************************************************************************
  * @attention
  * ros机器人在xyz三轴的速度由chassis_control来驱动，chassis_ros_control将从上
	* 位机接收到的速度指令作为参数传给chassis_control函数来执行上位机的速度指令
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
		osDelay(1);//必须延时
	}
}













