/**
  ******************************************************************************
  * File Name          : robot_communication.c
  * Description        : 负责所有与ros相关的通讯工作
	* @author            : 天科大-机器人实验室-郭耀辉
  ******************************************************************************
  * @attention
  *
  * 负责所有与ros相关的通讯工作，协议格式参考：附录/通信协议/轮趣科技-串口通信
	*	控制与反馈.pdf
  *
  ******************************************************************************
  */

#include "robot_communication.h"

ROS_Upper_computer ros_upper_computer;

//以下是与ros_upper_computer绑定的变量
uint8_t ros_rx_cnt;
uint8_t ros_rx_buf[200];
short x_target_speed, y_target_speed, z_target_speed;
short speedx, speedy, speedz;
short voltage = 22;
uint8_t motor_enable = 0;
uint8_t data_temp[24];//发送数据时的缓冲区

/**************************************************************************
函数功能：初始化ros_upper_computer对象，绑定相关变量
入口参数：略
返回  值：略
**************************************************************************/
void ros_object_init(void){
	ros_upper_computer.data_size = &ros_rx_cnt;
	ros_upper_computer.uart_receive = ros_rx_buf;
	ros_upper_computer.x_target_speed = &x_target_speed;
	ros_upper_computer.y_target_speed = &y_target_speed;
	ros_upper_computer.z_target_speed = &z_target_speed;
	
	ros_upper_computer.speedx = &speedx;
	ros_upper_computer.speedy = &speedy;
	ros_upper_computer.speedz = &speedz;
	
	ros_upper_computer.gyrox = &gyro[0];
	ros_upper_computer.gyroy = &gyro[1];
	ros_upper_computer.gyroz = &gyro[2];
	
	ros_upper_computer.accelx = &accel[0];
	ros_upper_computer.accely = &accel[1];
	ros_upper_computer.accelz = &accel[2];
	
	ros_upper_computer.voltage = &voltage;
	ros_upper_computer.motor_enable = &motor_enable;
}

/**************************************************************************
函数功能：ros通信：接收处理，当robot_uart_rx_one_byte_callback成功接收到
					一帧有效的数据，会进入此函数，解析ros上位机要求stm32下位机在x
					,y,z三轴的目标速度
入口参数：略
返回  值：略
**************************************************************************/
static void ros_dispose_data(uint8_t *data, uint8_t size){
	(*ros_upper_computer.x_target_speed) = (((short)data[4]<<8)|data[3]);
	(*ros_upper_computer.y_target_speed) = (((short)data[6]<<8)|data[5]);
	(*ros_upper_computer.z_target_speed) = (((short)data[8]<<8)|data[7]);
}

/**************************************************************************
函数功能：ros通信：接收处理回调函数，被串口中断调用，根据协议解析串口收到
					的每一个字节，如果成功接收到一帧数据，则将此时的数据帧交给ros_d
					ispose_data函数去翻译为xyz三轴的目标速度
入口参数：rxByte 本次接收到的字节
返回  值：略
**************************************************************************/
void robot_uart_rx_one_byte_callback(uint8_t rxByte){
	while (1){ //如果是串口3
		ros_rx_buf[ros_rx_cnt] = rxByte;
		if (ros_rx_cnt == 0 && ros_rx_buf[ros_rx_cnt] != 0x7B) break; //帧头不对，丢掉
		ros_rx_cnt++;
		if (ros_rx_cnt == 11){	//接受完一帧数据，首先判断帧尾，然后异或校验
			if(ros_rx_buf[10] != 0x7D){//帧尾不对，重新接收
				for (int i = 0; i<11; i++)		//清空缓存区
					ros_rx_buf[i] = 0;
				ros_rx_cnt = 0;
				break;
			}
			
			uint8_t robot_xor_check = 0;
			for (int i = 0; i < 9; i++){//对前9个字节异或校验
				robot_xor_check ^= ros_rx_buf[i];
			}
			if(robot_xor_check == ros_rx_buf[9]){//成功接收到ros上位机发过来的一帧数据
				ros_dispose_data(ros_rx_buf, 11);//处理数据
			}
			for (int i = 0; i<11; i++)		//清空缓存区
				ros_rx_buf[i] = 0;
			ros_rx_cnt = 0;
			break;
		}
		break;
	}
}

/**************************************************************************
函数功能：ros通信：发送函数，发送若干个字节给上位机，如需移植到串口，则需要
					重写此函数
入口参数：start	发送的起始地址；	size 要发送的字节数
返回  值：略
**************************************************************************/
static void ros_send_bytes(uint8_t * start, uint8_t size){
	HAL_UART_Transmit(&huart3, start, size, HAL_MAX_DELAY);
}

/**************************************************************************
函数功能：ros通信：发送处理，由软件定时器调用，将机器人的底盘信息按照协议格
					式发送给ros上位机，具体信息包括：xyz当前实际速度，xyz三轴角速度，
					xyz三轴当前加速度，电池电压情况，电机使能标志位
入口参数：略
返回  值：略
**************************************************************************/
void robot_send_car_attitude(void){
	data_temp[0] = 0x7b;
	data_temp[1] = motor_enable;
	data_temp[2] = ((*ros_upper_computer.speedx)&0xff00)>>8;
	data_temp[3] = (*ros_upper_computer.speedx)&0xff;
	data_temp[4] = ((*ros_upper_computer.speedy)&0xff00)>>8;
	data_temp[5] = (*ros_upper_computer.speedy)&0xff;
	data_temp[6] = ((*ros_upper_computer.speedz)&0xff00)>>8;
	data_temp[7] = (*ros_upper_computer.speedz)&0xff;
	data_temp[8] = ((*ros_upper_computer.accelx)&0xff00)>>8;
	data_temp[9] = (*ros_upper_computer.accelx)&0xff;
	data_temp[10] = ((*ros_upper_computer.accely)&0xff00)>>8;
	data_temp[11] = (*ros_upper_computer.accely)&0xff;
	data_temp[12] = ((*ros_upper_computer.accelz)&0xff00)>>8;
	data_temp[13] = (*ros_upper_computer.accelz)&0xff;
	data_temp[14] = ((*ros_upper_computer.gyrox)&0xff00)>>8;
	data_temp[15] = (*ros_upper_computer.gyrox)&0xff;
	data_temp[16] = ((*ros_upper_computer.gyroy)&0xff00)>>8;
	data_temp[17] = (*ros_upper_computer.gyroy)&0xff;
	data_temp[18] = ((*ros_upper_computer.gyroz)&0xff00)>>8;
	data_temp[19] = (*ros_upper_computer.gyroz)&0xff;
	data_temp[20] = ((*ros_upper_computer.voltage)&0xff00)>>8;
	data_temp[21] = (*ros_upper_computer.voltage)&0xff;
	
	//数据校验
	uint8_t BBC_check = 0;
	for (int i = 0; i<22; i++){
		BBC_check ^= data_temp[i];
	}
	data_temp[22] = BBC_check;
	data_temp[23] = 0x7d;
	
	ros_send_bytes(data_temp, 24);
}

//测试函数
void robot_communication_test(void){
	while(1){
		osDelay(200);
	}
}




















