/**
  ******************************************************************************
  * File Name          : LED.c
  * Description        : led灯，蜂鸣器
	* @author            : SuperEgo-郭耀辉   吴树涛（负责改进）
  ******************************************************************************
  * @attention
  *
  * C50C板载上面的LED灯是三合一的，可以显示R,G,B三种颜色，本项目把这个LED灯作为
	* 系统心跳灯，用户可以调用system_led_switch_color函数来改变系统心跳led灯的颜色
	*
	*	除此之外，在LED.h里面还有关于板载蜂鸣器的三个操作宏
  *
  ******************************************************************************
  */

#include "LED.h"

Led_Color led_color = RED;//系统心跳默认是红色

u8 is_chongfu = 0;//重复检测变量

/**************************************************************************
函数功能：更换系统心跳灯的颜色
入口参数：RED, GREEN, BLUE
返回  值：无
**************************************************************************/
void system_led_switch_color(Led_Color color)
{
	while(1){
		if(color == led_color){
			break;
		}else{
			led_color = color;
			LED_B_ON();
			LED_G_ON();
			LED_R_ON();
			break;
		}
	}
}

/**************************************************************************
函数功能：此函数仅在系统软件定时器中调用，不建议用户使用
入口参数：略
返回  值：略
**************************************************************************/
void system_led_heat(void)
{
	switch(led_color)
	{
		case RED:
			LED_B_TRI();
			LED_G_TRI();
//			LED_R_TRI();
			break;
		case GREEN:
			LED_B_TRI();
//			LED_G_TRI();
			LED_R_TRI();
			break;
		case BLUE:
//			LED_B_TRI();
			LED_G_TRI();
			LED_R_TRI();
			break;
	}
}



















