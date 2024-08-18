#ifndef __LED_H_
#define __LED_H_

#include "main.h"

#define LED_B_ON()	HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET)
#define LED_B_OFF()	HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET)
#define LED_B_TRI()	HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin)

#define LED_R_ON()	HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET)
#define LED_R_OFF()	HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET)
#define LED_R_TRI()	HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin)

#define LED_G_ON()	HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_SET)
#define LED_G_OFF()	HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_RESET)
#define LED_G_TRI()	HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin)

#define BEEP_ON()		HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET)
#define BEEP_OFF()	HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET)
#define BEEP_TRI()	HAL_GPIO_TogglePin(BEEP_GPIO_Port, BEEP_Pin)

typedef enum
{
	RED,
	GREEN,
	BLUE
}Led_Color;

void system_led_heat(void);
void system_led_switch_color(Led_Color color);

#endif
