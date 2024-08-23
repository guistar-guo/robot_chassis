#ifndef __ROBOT_COMMUNICATION__
#define __ROBOT_COMMUNICATION__

#include "main.h"

typedef struct{									//ros上位机结构体
	//以下数据是下行数据包的内容，即ros上位机发送给stm32的数据包的最新信息
	uint8_t *data_size;						//最新数据帧的字节数
	uint8_t *uart_receive;				//最新数据帧的内容(只包含有效数据)
	short *x_target_speed;				//上位机发送的最新的x轴目标速度
	short *y_target_speed;				//上位机发送的最新的y轴目标速度
	short *z_target_speed;				//上位机发送的最新的z轴目标速度
	
	//以下数据是上行数据包的内容，即stm32给ros上位机反馈的底盘信息，主要是底盘姿态和速度信息
	short* speedx;		//未实现！后续需要stm32根据speedx，speedy，speedz来完成运动学逆解控制电机
	short* speedy;		//未实现！
	short* speedz;		//未实现！
	
	short* gyrox;
	short* gyroy;
	short* gyroz;
	
	short* accelx;
	short* accely;
	short* accelz;
	
	short* voltage;		//未实现！目前暂时设置为定值22
	uint8_t* motor_enable;//未实现，后续根据情况考虑要不要加这个功能
}ROS_Upper_computer;

extern ROS_Upper_computer ros_upper_computer;

void ros_object_init(void);
void robot_uart_rx_one_byte_callback(uint8_t rxByte);		//解析ros上位机发送过来的数据
void robot_send_car_attitude(void);
void robot_communication_test(void);


#endif
