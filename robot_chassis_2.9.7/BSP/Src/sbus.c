/**
  ******************************************************************************
  * File Name          : sbus.c
  * Description        : sbus协议，航模遥控
	* @author            : 天科大-机器人实验室-郭耀辉  
  *                      天科大-机器人实验室-吴树涛（负责改进）
  ******************************************************************************
  * @attention
  *
  * 负责sbus协议解析，提供sbus对象供用户随时访问sbus的各个通道的实时数据.
  *
  ******************************************************************************
  */

#include "sbus.h"

uint8_t sbus_rx_buf[200];
uint8_t sbus_rx_cnt;
SBUS_CH_Struct SBUS_CH;

/**************************************************************************
函数功能：sbus数据帧处理，当sbus_rec_one_byte_callback函数成功接收到一帧数
					据，就会进入此函数处理这一帧数据，sbus信号转化为通道值
入口参数：buf 接收到的数据帧头指针
返回  值：略
**************************************************************************/
uint8_t update_sbus(uint8_t *buf)
{
    if (buf[23] == 0)
    {
        SBUS_CH.ConnectState = 1;
        SBUS_CH.CH1 = ((int16_t)buf[ 1] >> 0 | ((int16_t)buf[ 2] << 8 )) & 0x07FF;
        SBUS_CH.CH2 = ((int16_t)buf[ 2] >> 3 | ((int16_t)buf[ 3] << 5 )) & 0x07FF;
        SBUS_CH.CH3 = ((int16_t)buf[ 3] >> 6 | ((int16_t)buf[ 4] << 2 ) | (int16_t)buf[ 5] << 10 ) & 0x07FF;
        SBUS_CH.CH4 = ((int16_t)buf[ 5] >> 1 | ((int16_t)buf[ 6] << 7 )) & 0x07FF;
        SBUS_CH.CH5 = ((int16_t)buf[ 6] >> 4 | ((int16_t)buf[ 7] << 4 )) & 0x07FF;
        SBUS_CH.CH6 = ((int16_t)buf[ 7] >> 7 | ((int16_t)buf[ 8] << 1 ) | (int16_t)buf[9] << 9 ) & 0x07FF;
        SBUS_CH.CH7 = ((int16_t)buf[ 9] >> 2 | ((int16_t)buf[10] << 6 )) & 0x07FF;
        SBUS_CH.CH8 = ((int16_t)buf[10] >> 5 | ((int16_t)buf[11] << 3 )) & 0x07FF;
        SBUS_CH.CH9 = ((int16_t)buf[12] << 0 | ((int16_t)buf[13] << 8 )) & 0x07FF;
        SBUS_CH.CH10 = ((int16_t)buf[13] >> 3 | ((int16_t)buf[14] << 5 )) & 0x07FF;
        SBUS_CH.CH11 = ((int16_t)buf[14] >> 6 | ((int16_t)buf[15] << 2 ) | (int16_t)buf[16] << 10 ) & 0x07FF;
        SBUS_CH.CH12 = ((int16_t)buf[16] >> 1 | ((int16_t)buf[17] << 7 )) & 0x07FF;
        SBUS_CH.CH13 = ((int16_t)buf[17] >> 4 | ((int16_t)buf[18] << 4 )) & 0x07FF;
        SBUS_CH.CH14 = ((int16_t)buf[18] >> 7 | ((int16_t)buf[19] << 1 ) | (int16_t)buf[20] << 9 ) & 0x07FF;
        SBUS_CH.CH15 = ((int16_t)buf[20] >> 2 | ((int16_t)buf[21] << 6 )) & 0x07FF;
        SBUS_CH.CH16 = ((int16_t)buf[21] >> 5 | ((int16_t)buf[22] << 3 )) & 0x07FF;
        return 1;
    }
    else 
    {
        SBUS_CH.ConnectState = 0;
        return 0;
    }
}

/**************************************************************************
函数功能：sbus通信：接收处理回调函数，被串口中断调用，根据协议解析串口收到
					的每一个字节，如果成功接收到一帧数据，则将此时的数据帧交给update
					_sbus函数去翻译为各个通道的实时数据
入口参数：byte 本次接收到的字节
返回  值：略
**************************************************************************/
void sbus_rec_one_byte_callback(uint8_t byte){
	while(1){
		sbus_rx_buf[sbus_rx_cnt] = byte;
		if (sbus_rx_cnt == 0 && sbus_rx_buf[sbus_rx_cnt] != 0x0F) break; //帧头不对，丢掉
		sbus_rx_cnt++;
		if (sbus_rx_cnt == 25){
			if(sbus_rx_buf[24] == 0x00)
				update_sbus(sbus_rx_buf);
			for (int i = 0; i<25; i++)		//清空缓存区
				sbus_rx_buf[i] = 0;
			sbus_rx_cnt = 0;
			break;	
		}
		break;
	} 
}
/**************************************************************************
函数功能：打印出若干个sbus通道的当前值（按需求更改）
入口参数：略
返回  值：略
**************************************************************************/
void sbus_show_ch(void)
{
	if(SBUS_CH.ConnectState == 0)
	{
		SBUS_PRINTF("no connectstate!\r\n");
	}
	else
	{
		SBUS_PRINTF("ch1: %d ch2: %d ch3: %d ch4: %d\r\n",\
		SBUS_CH.CH1, SBUS_CH.CH2, SBUS_CH.CH3, SBUS_CH.CH4);
	}
}



















