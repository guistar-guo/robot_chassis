#ifndef __ENCODER_H
#define __ENCODER_H

#include "main.h"

#define ENCODERA_POLARITY -1
#define ENCODERB_POLARITY 1
#define ENCODERC_POLARITY 1
#define ENCODERD_POLARITY -1

//用户调用以下函数接口获取四个编码器当前的计次值(可正可负)或者清除指定编码器的计数值

int GetEncoderA(void);
int GetEncoderB(void);
int GetEncoderC(void);
int GetEncoderD(void);
void encoderA_clear(void);
void encoderB_clear(void);
void encoderC_clear(void);
void encoderD_clear(void);
void encoder_init(void);//初始化函数，在system_init函数中调用
void oled_show_encoder(void);//将四个编码器的当前计次值显示在板载的oled屏幕上面


#endif














