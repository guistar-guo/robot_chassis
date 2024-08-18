#ifndef __MOTOR__H
#define __MOTOR__H

#include "main.h"

//以下四个宏定义用来设置4个电机的极性，只能给-1或1
#define MOTORA_POLARITY 1
#define MOTORB_POLARITY -1
#define MOTORC_POLARITY -1
#define MOTORD_POLARITY 1
#define SMOOTH_STEP 0.8f

typedef void (*motor_set_pwm)(int16_t pwm);
typedef void (*Clear_encoder)(void);
typedef int (*Get_encoder)(void);

typedef struct{
	int16_t								speed;					//提供给用户的闭环速度设置接口
	motor_set_pwm 				set_pwm;				//函数指针，设置电机的pwm控制电机正反转(参数范围：-16799到16799)
	float									smooth_speed;		//平滑函数处理的变量，它与target_speed仅仅相差一个int16_t类型转换
	int16_t								target_speed;		//电机PI闭环目标速度
	Get_encoder 					get_encoder;		//函数指针，返回编码器当前计数值
	Clear_encoder 				clear_encoder;	//函数指针，清零编码器当前计数值
}Motor;


//提供四个电机的接口供用户使用
extern Motor motorA;
extern Motor motorB;
extern Motor motorC;
extern Motor motorD;

void motor_init(void);
void motor_task(void);

#endif
