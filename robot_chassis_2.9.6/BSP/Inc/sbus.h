#ifndef __SBUS__H__
#define __SBUS__H__

#include "main.h"

typedef struct
{
		uint16_t CH1;//ͨ��1��ֵ
		uint16_t CH2;//ͨ��2��ֵ
		uint16_t CH3;//ͨ��3��ֵ
		uint16_t CH4;//ͨ��4��ֵ
		uint16_t CH5;//ͨ��5��ֵ
		uint16_t CH6;//ͨ��6��ֵ
    uint16_t CH7;//ͨ��7��ֵ
    uint16_t CH8;//ͨ��8��ֵ
    uint16_t CH9;//ͨ��9��ֵ
    uint16_t CH10;//ͨ��10��ֵ
    uint16_t CH11;//ͨ��11��ֵ
    uint16_t CH12;//ͨ��12��ֵ
    uint16_t CH13;//ͨ��13��ֵ
    uint16_t CH14;//ͨ��14��ֵ
    uint16_t CH15;//ͨ��15��ֵ
    uint16_t CH16;//ͨ��16��ֵ
		uint8_t ConnectState;//ң���������������״̬ 0=δ���ӣ�1=��������
}SBUS_CH_Struct;

extern SBUS_CH_Struct SBUS_CH;
void sbus_rec_one_byte_callback(uint8_t byte);	//sbus���ڽ��յ��ֽڻص�����
#define SBUS_PRINTF			rtos_printf							//�˺�����ָ��sbus_show_ch����ʹ���ĸ����ڵ�printf
void sbus_show_ch(void);												//���û�ʹ�ã���ӡsbus����ͨ����ʵʱ����

#endif










