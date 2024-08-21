/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "system.h"
#include "usart.h"
#include "usartx.h"
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

#include "LED.h"
#include "oled.h"
#include "mpu6050.h"
#include "tim.h"
#include "encoder.h"
#include "motor.h"
#include "fsi6_control_motor.h"
#include "servos.h"
#include "robot_communication.h"
#include "sbus.h"
#include "aqmd.h"
#include "chassis_control.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MOTOR_ENABLE_Pin GPIO_PIN_4
#define MOTOR_ENABLE_GPIO_Port GPIOE
#define BIN2_Pin GPIO_PIN_0
#define BIN2_GPIO_Port GPIOC
#define USER_Pin GPIO_PIN_5
#define USER_GPIO_Port GPIOC
#define AIN1_Pin GPIO_PIN_12
#define AIN1_GPIO_Port GPIOB
#define AIN2_Pin GPIO_PIN_13
#define AIN2_GPIO_Port GPIOB
#define BIN1_Pin GPIO_PIN_14
#define BIN1_GPIO_Port GPIOB
#define CIN1_Pin GPIO_PIN_10
#define CIN1_GPIO_Port GPIOD
#define BEEP_Pin GPIO_PIN_11
#define BEEP_GPIO_Port GPIOD
#define CIN2_Pin GPIO_PIN_12
#define CIN2_GPIO_Port GPIOD
#define LED_G_Pin GPIO_PIN_13
#define LED_G_GPIO_Port GPIOD
#define LED_R_Pin GPIO_PIN_14
#define LED_R_GPIO_Port GPIOD
#define LED_B_Pin GPIO_PIN_15
#define LED_B_GPIO_Port GPIOD
#define DIN2_Pin GPIO_PIN_8
#define DIN2_GPIO_Port GPIOA
#define DIN1_Pin GPIO_PIN_12
#define DIN1_GPIO_Port GPIOC
#define MPU6050_AD0_Pin GPIO_PIN_3
#define MPU6050_AD0_GPIO_Port GPIOD
#define OLED_RS_Pin GPIO_PIN_4
#define OLED_RS_GPIO_Port GPIOD
#define OLED_RST_Pin GPIO_PIN_5
#define OLED_RST_GPIO_Port GPIOD
#define OLED_SDA_Pin GPIO_PIN_6
#define OLED_SDA_GPIO_Port GPIOD
#define OLED_SCLK_Pin GPIO_PIN_7
#define OLED_SCLK_GPIO_Port GPIOD
#define IIC_SCL_Pin GPIO_PIN_9
#define IIC_SCL_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
