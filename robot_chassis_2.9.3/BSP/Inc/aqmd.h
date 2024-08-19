#ifndef __AQMD_H_
#define __AQMD_H_

#include "main.h"

#define READ_HOLD_REGISTER				0x03			//�����ּĴ���
#define WRITE_SINGLE_REGISTER			0x06			//д�����Ĵ���
#define REG_SET_PWM								0x0042		//ռ�ձ����üĴ���

typedef enum{
	undecided, 	//��ȡ����δ��
	dataError, 	//��ȡ���ݴ���
	correct,			//��ȡ������ȷ
}AqmdDataStateTypeDef;

extern AqmdDataStateTypeDef aqmdDataState;

void aqmd_receive_one_byte_callback(uint8_t recByte);
void aqmd_debug_log(void);
void aqmd_test(void);





















#endif
