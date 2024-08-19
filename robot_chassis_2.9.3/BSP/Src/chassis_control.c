/**
  ******************************************************************************
  * File Name          : chassis_control.c
  * Description        : 麦轮底盘控制
	* @author            : 天科大-机器人实验室-吴树涛
  ******************************************************************************
  * @attention
  * 无
  *
  ******************************************************************************
  */

#include "chassis_control.h"

//	motorA.speed = 20;
//	motorB.speed = 20;
//	motorC.speed = 20;
//	motorD.speed = 20;
void chassis_control(short x,short y,short w)
{
	short va,vb,vc,vd;
	va = x+y+w;
	vb = x-y-w;
	vc = x+y-w;
	vd = x-y+w;
	
	va = va > 80 ? 80 : va;
	va = va < -80 ? -80 : va;
	vb = vb > 80 ? 80 : vb;
	vb = vb < -80 ? -80 : vb;
	vc = vc > 80 ? 80 : vc;
	vc = vc < -80 ? -80 : vc;
	vd = vd > 80 ? 80 : vd;
	vd = vd < -80 ? -80 : vd;
	
	motorA.speed = va;
	motorB.speed = vb;
	motorC.speed = vc;
	motorD.speed = vd;
}

void chassis_ros_control(void)
{
	short va,vb,vc,vd;
	short x = (short)ros_upper_computer.x_target_speed;
	short y = (short)ros_upper_computer.y_target_speed;
	short w = (short)ros_upper_computer.z_target_speed;
	va = x+y+w;
	vb = x-y-w;
	vc = x+y-w;
	vd = x-y+w;
	
	va = va > 80 ? 80 : va;
	va = va < -80 ? -80 : va;
	vb = vb > 80 ? 80 : vb;
	vb = vb < -80 ? -80 : vb;
	vc = vc > 80 ? 80 : vc;
	vc = vc < -80 ? -80 : vc;
	vd = vd > 80 ? 80 : vd;
	vd = vd < -80 ? -80 : vd;
	
	motorA.speed = va;
	motorB.speed = vb;
	motorC.speed = vc;
	motorD.speed = vd;
}

void chassis_control_test(void)
{
	osDelay(3000);
//	chassis_control(0,10,0);
//	osDelay(3000);
//	chassis_control(0,0,0);
//	motorA.set_pwm(3000);
//	motorB.set_pwm(3000);
//	motorC.set_pwm(3000);
//	motorD.set_pwm(3000);
	while(1)
	{
		osDelay(1);//必须延时
	}
}













