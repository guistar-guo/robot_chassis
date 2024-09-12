/**
  ******************************************************************************
  * File Name          : robot_communication.c
  * Description        : ����������ros��ص�ͨѶ����
	* @author            : ��ƴ�-������ʵ����-��ҫ��
  ******************************************************************************
  * @attention
  *
  * ����������ros��ص�ͨѶ������Э���ʽ�ο�����¼/ͨ��Э��/��Ȥ�Ƽ�-����ͨ��
	*	�����뷴��.pdf
  *
  ******************************************************************************
  */

#include "robot_communication.h"

ROS_Upper_computer ros_upper_computer;

//��������ros_upper_computer�󶨵ı���
uint8_t ros_rx_cnt;
uint8_t ros_rx_buf[200];
short x_target_speed, y_target_speed, z_target_speed;
short speedx, speedy, speedz;
short voltage = 22;
uint8_t motor_enable = 0;
uint8_t data_temp[24];//��������ʱ�Ļ�����

/**************************************************************************
�������ܣ���ʼ��ros_upper_computer���󣬰���ر���
��ڲ�������
����  ֵ����
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
�������ܣ�rosͨ�ţ����մ�����robot_uart_rx_one_byte_callback�ɹ����յ�
					һ֡��Ч�����ݣ������˺���������ros��λ��Ҫ��stm32��λ����x
					,y,z�����Ŀ���ٶ�
��ڲ�������
����  ֵ����
**************************************************************************/
static void ros_dispose_data(uint8_t *data, uint8_t size){
	(*ros_upper_computer.x_target_speed) = (((short)data[4]<<8)|data[3]);
	(*ros_upper_computer.y_target_speed) = (((short)data[6]<<8)|data[5]);
	(*ros_upper_computer.z_target_speed) = (((short)data[8]<<8)|data[7]);
}

/**************************************************************************
�������ܣ�rosͨ�ţ����մ���ص��������������жϵ��ã�����Э����������յ�
					��ÿһ���ֽڣ�����ɹ����յ�һ֡���ݣ��򽫴�ʱ������֡����ros_d
					ispose_data����ȥ����Ϊxyz�����Ŀ���ٶ�
��ڲ�����rxByte ���ν��յ����ֽ�
����  ֵ����
**************************************************************************/
void robot_uart_rx_one_byte_callback(uint8_t rxByte){
	while (1){ //����Ǵ���3
		ros_rx_buf[ros_rx_cnt] = rxByte;
		if (ros_rx_cnt == 0 && ros_rx_buf[ros_rx_cnt] != 0x7B) break; //֡ͷ���ԣ�����
		ros_rx_cnt++;
		if (ros_rx_cnt == 11){	//������һ֡���ݣ������ж�֡β��Ȼ�����У��
			if(ros_rx_buf[10] != 0x7D){//֡β���ԣ����½���
				for (int i = 0; i<11; i++)		//��ջ�����
					ros_rx_buf[i] = 0;
				ros_rx_cnt = 0;
				break;
			}
			
			uint8_t robot_xor_check = 0;
			for (int i = 0; i < 9; i++){//��ǰ9���ֽ����У��
				robot_xor_check ^= ros_rx_buf[i];
			}
			if(robot_xor_check == ros_rx_buf[9]){//�ɹ����յ�ros��λ����������һ֡����
				ros_dispose_data(ros_rx_buf, 11);//��������
			}
			for (int i = 0; i<11; i++)		//��ջ�����
				ros_rx_buf[i] = 0;
			ros_rx_cnt = 0;
			break;
		}
		break;
	}
}

/**************************************************************************
�������ܣ�rosͨ�ţ����ͺ������������ɸ��ֽڸ���λ����������ֲ�����ڣ�����Ҫ
					��д�˺���
��ڲ�����start	���͵���ʼ��ַ��	size Ҫ���͵��ֽ���
����  ֵ����
**************************************************************************/
static void ros_send_bytes(uint8_t * start, uint8_t size){
	HAL_UART_Transmit(&huart3, start, size, HAL_MAX_DELAY);
}

/**************************************************************************
�������ܣ�rosͨ�ţ����ʹ����������ʱ�����ã��������˵ĵ�����Ϣ����Э���
					ʽ���͸�ros��λ����������Ϣ������xyz��ǰʵ���ٶȣ�xyz������ٶȣ�
					xyz���ᵱǰ���ٶȣ���ص�ѹ��������ʹ�ܱ�־λ
��ڲ�������
����  ֵ����
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
	
	//����У��
	uint8_t BBC_check = 0;
	for (int i = 0; i<22; i++){
		BBC_check ^= data_temp[i];
	}
	data_temp[22] = BBC_check;
	data_temp[23] = 0x7d;
	
	ros_send_bytes(data_temp, 24);
}

//���Ժ���
void robot_communication_test(void){
	while(1){
		osDelay(200);
	}
}




















