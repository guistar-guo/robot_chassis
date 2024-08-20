/**
  ******************************************************************************
  * File Name          : usartx.c
  * Description        : 用于串口通信协议相关的应用
	* @author            : 天科大-机器人实验室-郭耀辉
  ******************************************************************************
  * @attention
  *
  * 负责串口发送函数（printf, dma_printf, rtos_printf）,和为其他模块提供串口回
	* 调入口。
	*
	* 为什么不用串口一？这是作者打电赛期间积累的经验，串口一是专用于程序烧录的
	* 当你发送字节给串口一，可能会被单片机的bootloder程序误认为是程序烧录的指令
	* 导致单片机卡死，因此不建议在程序中使用串口一，学习单片机的过程中可能并不会
	* 发现这个问题，因为这个过程单片机通常是一直上电的，而在实际应用中可不是这样！
  *
  ******************************************************************************
  */

#include "usartx.h"
#include <stdarg.h>

////////////////////////////////////发送函数相关///////////////////////////////////
//printf支持（串口重定向）
//注意此步骤要想生效，必须配置工程target选项支持Use MicroLIB
int fputc(int ch,FILE *f)
{
	HAL_UART_Transmit(&huart3,(uint8_t *)&ch,1,HAL_MAX_DELAY);
	return ch;
}

//dma_printf支持（非阻塞发送，但是不适用于需要循环发送的场合）
char dma_printf_buf[DMA_PRINTF_MAX];
void dma_printf (char *fmt, ...)
{ 
	va_list arg_ptr;
	va_start(arg_ptr, fmt);  
	vsnprintf(dma_printf_buf, DMA_PRINTF_MAX+1, fmt, arg_ptr);
	HAL_UART_Transmit_DMA(&huart3, (uint8_t *)&dma_printf_buf, strlen(dma_printf_buf)); 
}

//rtos_printf支持，调试神器，强制打印完整内容，
//不可被任何任务打断（中断除外）
//虽然可以保证打印出的内容是完整的，但是建议仅仅在调试的
//时候使用此函数，实际应用中不要使用！因为不可被打断是靠
//rtos临界区来实现的，长时间占用临界区会导致其他任务长时间得不到执行!
#define RTOS_PRINTF_MAX 100
char rtos_printf_buf[RTOS_PRINTF_MAX];
void rtos_printf(char *fmt, ...)
{
	taskENTER_CRITICAL();
	va_list arg_ptr;
	va_start(arg_ptr, fmt);  
	vsnprintf(rtos_printf_buf, RTOS_PRINTF_MAX+1, fmt, arg_ptr);
	printf("%s", rtos_printf_buf);	
	taskEXIT_CRITICAL();
}

////////////////////////////////////////////串口中断/////////////////////////////////////////////////
uint8_t UART3_RX_BUF[1];//串口3接收缓冲区
uint8_t UART4_RX_BUF[1];//串口4接收缓冲区
uint8_t UART5_RX_BUF[1];//串口5接收缓冲区
//串口中断
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART3){//串口3暂时不负责接收处理
		//待开发...
		
	}
	HAL_UART_Receive_IT(&huart3, (u8 *)UART3_RX_BUF, 1);
	//HAL_UART_Transmit_IT(&huart3, (u8 *)UART3_RX_BUF, 1);
	
	if(huart->Instance == UART4){//串口4负责解析机器人通信协议
		robot_uart_rx_one_byte_callback(UART4_RX_BUF[0]);
	}
	HAL_UART_Receive_IT(&huart4, (u8 *)UART4_RX_BUF, 1);
	
	if (huart->Instance == UART5){//串口5负责解析sbus协议
		sbus_rec_one_byte_callback(UART5_RX_BUF[0]);
	}
	HAL_UART_Receive_IT(&huart5, (u8 *)UART5_RX_BUF, 1);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART3){
		
	}
	
	
}







