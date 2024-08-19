/**
  ******************************************************************************
  * File Name          : usartx.c
  * Description        : ���ڴ���ͨ��Э����ص�Ӧ��
	* @author            : ��ƴ�-������ʵ����-��ҫ��
  ******************************************************************************
  * @attention
  *
  * ���𴮿ڷ��ͺ�����printf, dma_printf, rtos_printf��,��Ϊ����ģ���ṩ���ڻ�
	* ����ڡ�
	*
	* Ϊʲô���ô���һ���������ߴ�����ڼ���۵ľ��飬����һ��ר���ڳ�����¼��
	* ���㷢���ֽڸ�����һ�����ܻᱻ��Ƭ����bootloder��������Ϊ�ǳ�����¼��ָ��
	* ���µ�Ƭ����������˲������ڳ�����ʹ�ô���һ��ѧϰ��Ƭ���Ĺ����п��ܲ�����
	* ����������⣬��Ϊ������̵�Ƭ��ͨ����һֱ�ϵ�ģ�����ʵ��Ӧ���пɲ���������
  *
  ******************************************************************************
  */

#include "usartx.h"
#include <stdarg.h>

////////////////////////////////////���ͺ������///////////////////////////////////
//printf֧�֣������ض���
//ע��˲���Ҫ����Ч���������ù���targetѡ��֧��Use MicroLIB
int fputc(int ch,FILE *f)
{
	HAL_UART_Transmit(&huart3,(uint8_t *)&ch,1,HAL_MAX_DELAY);
	return ch;
}

//dma_printf֧�֣����������ͣ����ǲ���������Ҫѭ�����͵ĳ��ϣ�
char dma_printf_buf[DMA_PRINTF_MAX];
void dma_printf (char *fmt, ...)
{ 
	va_list arg_ptr;
	va_start(arg_ptr, fmt);  
	vsnprintf(dma_printf_buf, DMA_PRINTF_MAX+1, fmt, arg_ptr);
	HAL_UART_Transmit_DMA(&huart3, (uint8_t *)&dma_printf_buf, strlen(dma_printf_buf)); 
}

//rtos_printf֧�֣�����������ǿ�ƴ�ӡ�������ݣ�
//���ɱ��κ������ϣ��жϳ��⣩
//��Ȼ���Ա�֤��ӡ���������������ģ����ǽ�������ڵ��Ե�
//ʱ��ʹ�ô˺�����ʵ��Ӧ���в�Ҫʹ�ã���Ϊ���ɱ�����ǿ�
//rtos�ٽ�����ʵ�ֵģ���ʱ��ռ���ٽ����ᵼ����������ʱ��ò���ִ��!
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

////////////////////////////////////////////�����ж�/////////////////////////////////////////////////
uint8_t UART3_RX_BUF[1];//����3���ջ�����
uint8_t UART4_RX_BUF[1];//����4���ջ�����
uint8_t UART5_RX_BUF[1];//����5���ջ�����
//�����ж�
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART3){//����3��ʱ��������մ���
		//������...
		
	}
	HAL_UART_Receive_IT(&huart3, (u8 *)UART3_RX_BUF, 1);
	//HAL_UART_Transmit_IT(&huart3, (u8 *)UART3_RX_BUF, 1);
	
	if(huart->Instance == UART4){//����4�������������ͨ��Э��
		robot_uart_rx_one_byte_callback(UART4_RX_BUF[0]);
	}
	HAL_UART_Receive_IT(&huart4, (u8 *)UART4_RX_BUF, 1);
	
	if (huart->Instance == UART5){//����5�������sbusЭ��
		sbus_rec_one_byte_callback(UART5_RX_BUF[0]);
	}
	HAL_UART_Receive_IT(&huart5, (u8 *)UART5_RX_BUF, 1);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART3){
		
	}
	
	
}







