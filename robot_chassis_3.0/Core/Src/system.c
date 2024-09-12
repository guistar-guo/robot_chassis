#include "system.h"

u32 systick = 0;//由系统软件定时器system_timer产生的系统滴答，每一个系统节拍（1ms）加1

//做一些用户自己的硬件初始化.
//提醒：这个函数里面禁止使用osDelay()函数延时(原因见附录：cubemx_freertos支持参考.txt)
//如果想在此函数中延时，可以使用本.c文件下面的两个延时函数delay_us，delay_ms，或者HAL_Delay
void system_init(void)
{
	motor_init();							//初始化电机
//	my_uart_IT_re_enable();		//开启串口3中断
	HAL_UART_Receive_IT(&huart3, (u8 *)UART3_RX_BUF, 1);//开启串口3接收中断，用以解析ros协议
	HAL_UART_Receive_IT(&huart4, (u8 *)UART4_RX_BUF, 1);
	HAL_UART_Receive_IT(&huart5, (u8 *)UART5_RX_BUF, 1); //开启串口5接收中断，用以解析sbus协议
	
	OLED_Init();							//初始化OLED显示屏
	MPU6050_initialize();			//初始化陀螺仪。提醒：陀螺仪的初始化很耗时，对于上电就需要立即初始化的模块，最好放在这一句的前面
	encoder_init();						//初始化4个编码器
	servos_init();						//初始化舵机
	
	system_led_switch_color(RED);//设置心跳灯为红色
	ros_object_init();
}

//在rtos任务中，如非特殊应用场合，应尽量避免使用如下的延时函数，而是使用osDelay
//以下两个函数的应用场合是一些时序严格的初始化过程，如OLED屏幕初始化，mpu6050的I2C初始化
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


