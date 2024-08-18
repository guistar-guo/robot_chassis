#ifndef __SBUS__H__
#define __SBUS__H__

#include "main.h"

typedef struct
{
		uint16_t CH1;//通道1数值
		uint16_t CH2;//通道2数值
		uint16_t CH3;//通道3数值
		uint16_t CH4;//通道4数值
		uint16_t CH5;//通道5数值
		uint16_t CH6;//通道6数值
    uint16_t CH7;//通道7数值
    uint16_t CH8;//通道8数值
    uint16_t CH9;//通道9数值
    uint16_t CH10;//通道10数值
    uint16_t CH11;//通道11数值
    uint16_t CH12;//通道12数值
    uint16_t CH13;//通道13数值
    uint16_t CH14;//通道14数值
    uint16_t CH15;//通道15数值
    uint16_t CH16;//通道16数值
		uint8_t ConnectState;//遥控器与接收器连接状态 0=未连接，1=正常连接
}SBUS_CH_Struct;

extern SBUS_CH_Struct SBUS_CH;
void sbus_rec_one_byte_callback(uint8_t byte);	//sbus串口接收单字节回调函数
#define SBUS_PRINTF			rtos_printf							//此宏用来指定sbus_show_ch函数使用哪个串口的printf
void sbus_show_ch(void);												//供用户使用，打印sbus所有通道的实时数据

#endif










