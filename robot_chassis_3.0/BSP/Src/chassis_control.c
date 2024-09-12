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



/**************************************************************************
函数功能：底盘控制（麦轮混控）
入口参数：x,y,w。底盘运动方向的速度,x前进后退,单位为mm/s，
																		y左右平移，单位为mm/s，
																		w自转角速度,单位为1000rad/s
返回  值：无
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
函数功能：接收ros串口的数据进行底盘控制（麦轮混控）
入口参数：无
返回  值：无
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
		
		osDelay(1);//必须延时
	}
}













