#ifndef __ENCODER_H
#define __ENCODER_H

#include "main.h"

#define ENCODERA_POLARITY -1
#define ENCODERB_POLARITY 1
#define ENCODERC_POLARITY 1
#define ENCODERD_POLARITY -1

//�û��������º����ӿڻ�ȡ�ĸ���������ǰ�ļƴ�ֵ(�����ɸ�)�������ָ���������ļ���ֵ

int GetEncoderA(void);
int GetEncoderB(void);
int GetEncoderC(void);
int GetEncoderD(void);
void encoderA_clear(void);
void encoderB_clear(void);
void encoderC_clear(void);
void encoderD_clear(void);
void encoder_init(void);//��ʼ����������system_init�����е���
void oled_show_encoder(void);//���ĸ��������ĵ�ǰ�ƴ�ֵ��ʾ�ڰ��ص�oled��Ļ����


#endif














