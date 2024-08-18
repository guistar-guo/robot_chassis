/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
  .name = "myTask02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for myTask03 */
osThreadId_t myTask03Handle;
const osThreadAttr_t myTask03_attributes = {
  .name = "myTask03",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for system_timer */
osTimerId_t system_timerHandle;
const osTimerAttr_t system_timer_attributes = {
  .name = "system_timer"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);
void system_timer_callback(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of system_timer */
  system_timerHandle = osTimerNew(system_timer_callback, osTimerPeriodic, NULL, &system_timer_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of myTask02 */
  myTask02Handle = osThreadNew(StartTask02, NULL, &myTask02_attributes);

  /* creation of myTask03 */
  myTask03Handle = osThreadNew(StartTask03, NULL, &myTask03_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	uint8_t str[] = "SuperEgo";
	OLED_ShowString(30, 0, str);
	OLED_Refresh_Gram();
	
	osTimerStart(system_timerHandle, 1);//����ϵͳ�����ʱ������������Ϊ1��ϵͳ����(1ms)
  /* Infinite loop */
  for(;;)
  {
		fsi6_control();
    osDelay(20);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
//	motorA.set_pwm(3000);
//	motorB.set_pwm(3000);
//	motorA.speed = 20;
//	motorB.speed = 20;
//	motorC.speed = 20;
//	motorD.speed = 20;
	motor_task();
	
	//�¾���ʾ����StartTask02��������У���һ���Ժ�д���κδ��붼��Ч(motor_task����ѭ��)
  /* Infinite loop */
  for(;;)
  {
		osDelay(200);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
	char oled_str[100];
	extern int cur_A_speed;
	extern int cur_B_speed;
	extern int cur_C_speed;
	extern int cur_D_speed;
	extern int pwmD;
	
  /* Infinite loop */
  for(;;)
  {
		//����������ʾpwmD�����ֵ����pid��ʱ��ʹ�ã����鿴����Ŀ����Ƿ��㹻ƽ��
//		sprintf(oled_str,"%5d", pwmD);
//		OLED_ShowString(30, 48, (u8*)oled_str);
//		OLED_ShowString(0, 48, (u8*)"pwmD:");
		
		//����������ʾ������D�ĵ�ǰ�ۼ�ֵ����175�����ʹ�����жϼ����Ƿ���ȷ��ע�⣡�������뱣֤������ȷ�ſ��Խӵ��
		//���ȡ��ע��175�У�Ȼ����ʾ�������е���Ļ�ϣ����ֵ��ת��ʱ�򣬱������ƴ�ֵ�����ӵģ�������ȷ
		//������Դ��������ʵ���������motor.h��encoder.h����ĵ���ͱ������ļ���
//	sprintf(oled_str,"%5d", motorA.get_encoder());
//	OLED_ShowString(30, 30, (u8*)oled_str);
//	OLED_ShowString(0, 30, (u8*)"EA:");
//		
//	sprintf(oled_str,"%5d", motorB.get_encoder());
//	OLED_ShowString(30, 48, (u8*)oled_str);
//	OLED_ShowString(0, 48, (u8*)"EB:");
		
		//��ʾ����ٶȣ��������е����õ������֮�󣬷�����ʾ����ٶ�
		
		sprintf(oled_str,"%5d", cur_A_speed);
		OLED_ShowString(30, 12, (u8*)oled_str);
		OLED_ShowString(0, 12, (u8*)"EA:");
			
		sprintf(oled_str,"%5d", cur_B_speed);
		OLED_ShowString(30, 24, (u8*)oled_str);
		OLED_ShowString(0, 24, (u8*)"EB:");
		
		sprintf(oled_str,"%5d", cur_C_speed);
		OLED_ShowString(30, 36, (u8*)oled_str);
		OLED_ShowString(0, 36, (u8*)"EA:");
			
		sprintf(oled_str,"%5d", cur_D_speed);
		OLED_ShowString(30, 48, (u8*)oled_str);
		OLED_ShowString(0, 48, (u8*)"EB:");
		
		OLED_Refresh_Gram();
		
		osDelay(20);
  }
  /* USER CODE END StartTask03 */
}

/* system_timer_callback function */
void system_timer_callback(void *argument)
{
  /* USER CODE BEGIN system_timer_callback */
	if(!(++systick%200))//ϵͳled��ÿ��200��������˸һ��
	{
		system_led_heat();
	}
	if(!(systick % 500)){
//		MPU_Get_Gyroscope();
//		MPU_Get_Accelscope();
//		robot_send_car_attitude();
	}
  /* USER CODE END system_timer_callback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

