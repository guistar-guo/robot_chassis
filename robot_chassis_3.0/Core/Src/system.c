#include "system.h"

u32 systick = 0;//��ϵͳ�����ʱ��system_timer������ϵͳ�δ�ÿһ��ϵͳ���ģ�1ms����1

//��һЩ�û��Լ���Ӳ����ʼ��.
//���ѣ�������������ֹʹ��osDelay()������ʱ(ԭ�����¼��cubemx_freertos֧�ֲο�.txt)
//������ڴ˺�������ʱ������ʹ�ñ�.c�ļ������������ʱ����delay_us��delay_ms������HAL_Delay
void system_init(void)
{
	motor_init();							//��ʼ�����
//	my_uart_IT_re_enable();		//��������3�ж�
	HAL_UART_Receive_IT(&huart3, (u8 *)UART3_RX_BUF, 1);//��������3�����жϣ����Խ���rosЭ��
	HAL_UART_Receive_IT(&huart4, (u8 *)UART4_RX_BUF, 1);
	HAL_UART_Receive_IT(&huart5, (u8 *)UART5_RX_BUF, 1); //��������5�����жϣ����Խ���sbusЭ��
	
	OLED_Init();							//��ʼ��OLED��ʾ��
	MPU6050_initialize();			//��ʼ�������ǡ����ѣ������ǵĳ�ʼ���ܺ�ʱ�������ϵ����Ҫ������ʼ����ģ�飬��÷�����һ���ǰ��
	encoder_init();						//��ʼ��4��������
	servos_init();						//��ʼ�����
	
	system_led_switch_color(RED);//����������Ϊ��ɫ
	ros_object_init();
}

//��rtos�����У��������Ӧ�ó��ϣ�Ӧ��������ʹ�����µ���ʱ����������ʹ��osDelay
//��������������Ӧ�ó�����һЩʱ���ϸ�ĳ�ʼ�����̣���OLED��Ļ��ʼ����mpu6050��I2C��ʼ��
void delay_us(uint32_t us)
{
  __IO uint32_t Delay = us * 168 / 8;//(SystemCoreClock / 8U / 1000000U)
  do
  {
    __NOP();
  }
  while (Delay --);
}

void delay_ms(uint32_t ms)
{
	uint16_t i;
	for (i = 0; i<1000; i++)
	{
		delay_us(ms);
	}
}


