#ifndef __SBUS_H
#define __SBUS_H

#include "main.h"
//#include "usart.h"

#define DMA_PRINTF_MAX 100


extern uint8_t UART3_RX_BUF[1];//��system.c�������ʣ�����ʼ�������ж�
extern uint8_t UART4_RX_BUF[1];//��system.c�������ʣ�����ʼ�������ж�
extern uint8_t UART5_RX_BUF[1];//��system.c�������ʣ�����ʼ�������ж�
void dma_printf (char *fmt, ...);
void rtos_printf(char *fmt, ...);

#endif




















