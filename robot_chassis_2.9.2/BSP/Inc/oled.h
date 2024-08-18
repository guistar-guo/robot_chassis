#ifndef __OLED_H
#define __OLED_H			  	 
#include "main.h"

//Oled port macro definition
//OLED�˿ں궨��
#define OLED_RST_Clr() HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_RESET)   //RST
#define OLED_RST_Set() HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_SET)   //RST

#define OLED_RS_Clr()  HAL_GPIO_WritePin(OLED_RS_GPIO_Port, OLED_RS_Pin, GPIO_PIN_RESET)   //DC
#define OLED_RS_Set()  HAL_GPIO_WritePin(OLED_RS_GPIO_Port, OLED_RS_Pin, GPIO_PIN_SET)   //DC

#define OLED_SCLK_Clr()  HAL_GPIO_WritePin(OLED_SCLK_GPIO_Port, OLED_SCLK_Pin, GPIO_PIN_RESET)   //SCL
#define OLED_SCLK_Set()  HAL_GPIO_WritePin(OLED_SCLK_GPIO_Port, OLED_SCLK_Pin, GPIO_PIN_SET)   //SCL

#define OLED_SDIN_Clr()  HAL_GPIO_WritePin(OLED_SDA_GPIO_Port, OLED_SDA_Pin, GPIO_PIN_RESET)   //SDA
#define OLED_SDIN_Set()  HAL_GPIO_WritePin(OLED_SDA_GPIO_Port, OLED_SDA_Pin, GPIO_PIN_SET)   //SDA
#define OLED_CMD  0	//Command //д����
#define OLED_DATA 1	//Data //д����

typedef uint8_t u8;
typedef uint32_t u32;
//Oled control function
//OLED�����ú���
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   				   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowNumber(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y,const u8 *p);

#define CNSizeWidth  16
#define CNSizeHeight 16
//extern char Hzk16[][16];
void OLED_ShowCHinese(u8 x,u8 y,u8 no,u8 font_width,u8 font_height);
void OLED_Set_Pos(unsigned char x, unsigned char y);
int* FenJie_float(const float fudian);
void oled_showfloat(const float needtoshow,u8 show_x,u8 show_y,u8 zs_num,u8 xs_num);
#endif

