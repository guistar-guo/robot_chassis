#ifndef __ROBOT_COMMUNICATION__
#define __ROBOT_COMMUNICATION__

#include "main.h"

typedef struct{									//ros��λ���ṹ��
	//�����������������ݰ������ݣ���ros��λ�����͸�stm32�����ݰ���������Ϣ
	uint8_t *data_size;						//��������֡���ֽ���
	uint8_t *uart_receive;				//��������֡������(ֻ������Ч����)
	short *x_target_speed;				//��λ�����͵����µ�x��Ŀ���ٶ�
	short *y_target_speed;				//��λ�����͵����µ�y��Ŀ���ٶ�
	short *z_target_speed;				//��λ�����͵����µ�z��Ŀ���ٶ�
	
	//�����������������ݰ������ݣ���stm32��ros��λ�������ĵ�����Ϣ����Ҫ�ǵ�����̬���ٶ���Ϣ
	short* speedx;		//δʵ�֣�������Ҫstm32����speedx��speedy��speedz������˶�ѧ�����Ƶ��
	short* speedy;		//δʵ�֣�
	short* speedz;		//δʵ�֣�
	
	short* gyrox;
	short* gyroy;
	short* gyroz;
	
	short* accelx;
	short* accely;
	short* accelz;
	
	short* voltage;		//δʵ�֣�Ŀǰ��ʱ����Ϊ��ֵ22
	uint8_t* motor_enable;//δʵ�֣����������������Ҫ��Ҫ���������
}ROS_Upper_computer;

extern ROS_Upper_computer ros_upper_computer;

void ros_object_init(void);
void robot_uart_rx_one_byte_callback(uint8_t rxByte);		//����ros��λ�����͹���������
void robot_send_car_attitude(void);
void robot_communication_test(void);


#endif
