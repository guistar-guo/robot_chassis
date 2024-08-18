#ifndef __SBUS_H
#define __SBUS_H

#include "main.h"
//#include "usart.h"

#define DMA_PRINTF_MAX 100


extern uint8_t UART3_RX_BUF[1];//供system.c函数访问，来初始化串口中断
extern uint8_t UART4_RX_BUF[1];//供system.c函数访问，来初始化串口中断
extern uint8_t UART5_RX_BUF[1];//供system.c函数访问，来初始化串口中断
void dma_printf (char *fmt, ...);
void rtos_printf(char *fmt, ...);

#endif




















