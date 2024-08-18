#ifndef __MOTOR__H
#define __MOTOR__H

#include "main.h"

//�����ĸ��궨����������4������ļ��ԣ�ֻ�ܸ�-1��1
#define MOTORA_POLARITY 1
#define MOTORB_POLARITY -1
#define MOTORC_POLARITY -1
#define MOTORD_POLARITY 1
#define SMOOTH_STEP 0.8f

typedef void (*motor_set_pwm)(int16_t pwm);
typedef void (*Clear_encoder)(void);
typedef int (*Get_encoder)(void);

typedef struct{
	int16_t								speed;					//�ṩ���û��ıջ��ٶ����ýӿ�
	motor_set_pwm 				set_pwm;				//����ָ�룬���õ����pwm���Ƶ������ת(������Χ��-16799��16799)
	float									smooth_speed;		//ƽ����������ı���������target_speed�������һ��int16_t����ת��
	int16_t								target_speed;		//���PI�ջ�Ŀ���ٶ�
	Get_encoder 					get_encoder;		//����ָ�룬���ر�������ǰ����ֵ
	Clear_encoder 				clear_encoder;	//����ָ�룬�����������ǰ����ֵ
}Motor;


//�ṩ�ĸ�����Ľӿڹ��û�ʹ��
extern Motor motorA;
extern Motor motorB;
extern Motor motorC;
extern Motor motorD;

void motor_init(void);
void motor_task(void);

#endif
