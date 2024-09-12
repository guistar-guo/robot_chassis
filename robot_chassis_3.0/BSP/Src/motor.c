/**
  ************************************************************************************
  * File Name          : motor.c
  * Description        : Code for motor applications
	* @author            : SuperEgo-��ҫ��
  ************************************************************************************
  * @attention
	* Ϊ�û��ṩ���°˸�api�������ĸ��������Ϊ��
  *
  * �������½ӿ�������A��pwm��
	*	motorA.set_pwm(3000)�����뷶Χ��-16799��16799��ͬʱ���뱣֤motor_taskû�������У�
	*
	*	�������½ӿ�pi�ջ����Ƶ����
	*	motorA.speed = 20�����뷶Χ��-80��80��ͬʱ���뱣֤motor_task����rtos���У�
  *
  ************************************************************************************
  */
#include "motor.h"

Motor motorA;
Motor motorB;
Motor motorC;
Motor motorD;

void motorA_set_pwm(int16_t pwm);
void motorB_set_pwm(int16_t pwm);
void motorC_set_pwm(int16_t pwm);
void motorD_set_pwm(int16_t pwm);

/**************************************************************************
�������ܣ��������󶨺������������Ϊ�������ĺ���ָ��͵������ָ�룬
					�˺������𽫵�������뺯��ָ��󶨣�������C++��ʵ������
��ڲ�������
����  ֵ����
**************************************************************************/
static void motor_object_init(
		Motor* motor, 
		motor_set_pwm set_pwm_func, 
		Get_encoder get_encoder, 
		Clear_encoder clear_encoder)
{
	motor->smooth_speed = 0;
	motor->speed = 0;
	motor->set_pwm = set_pwm_func;				//��pwm��������
	motor->target_speed = 0;							//����Ŀ���ٶ�Ϊ0
	motor->get_encoder = get_encoder;			//�󶨱�������ֵ��ȡ����
	motor->clear_encoder = clear_encoder;	//�󶨱��������㺯��
}

/**************************************************************************
�������ܣ���ʼ�����ڵ���ı�Ҫ���ţ��󶨵������ĳ�Ա����
��ڲ�������
����  ֵ����
**************************************************************************/
void motor_init(void)
{
	//����DIN1�봮��5TX���ų�ͻ(ʵ���ϣ�����5��sbusЭ������ò���tx)��
	//��cubemx���޷����ɴ��룬��������ﵥ����ʼ��DIN1Ϊ�������
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(DIN1_GPIO_Port, DIN1_Pin, GPIO_PIN_RESET);


  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = DIN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DIN1_GPIO_Port, &GPIO_InitStruct);
	
	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, 0);
	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, 0);
	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, 0);
	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, 0);
	
	//����Ե��������Ž��г�ʼ��
  HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
	
  HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
	
  HAL_GPIO_WritePin(CIN1_GPIO_Port, CIN1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CIN2_GPIO_Port, CIN2_Pin, GPIO_PIN_RESET);
	
  HAL_GPIO_WritePin(DIN1_GPIO_Port, DIN1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(DIN2_GPIO_Port, DIN2_Pin, GPIO_PIN_RESET);
	
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
	
	/*��ʼ���ĸ�������󣬰���صĺ���*/
	motor_object_init(&motorA, motorA_set_pwm, GetEncoderA, encoderA_clear);
	motor_object_init(&motorB, motorB_set_pwm, GetEncoderB, encoderB_clear);
	motor_object_init(&motorC, motorC_set_pwm, GetEncoderC, encoderC_clear);
	motor_object_init(&motorD, motorD_set_pwm, GetEncoderD, encoderD_clear);
}

/**************************************************************************
�������ܣ����õ��A��ռ�ձȣ�������Χ��-16799��16799
��ڲ�������
����  ֵ����
**************************************************************************/
static void motorA_set_pwm(int16_t pwm)
{
	pwm *= MOTORA_POLARITY;
	if(pwm>0)
	{
		HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, pwm);
	}
	else
	{
		pwm = -pwm;
		HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, pwm);
	}
}

/**************************************************************************
�������ܣ����õ��B��ռ�ձȣ�������Χ��-16799��16799
��ڲ�������
����  ֵ����
**************************************************************************/
static void motorB_set_pwm(int16_t pwm)
{
	pwm *= MOTORB_POLARITY;
	if(pwm>0)
	{
		HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, pwm);
	}
	else
	{
		pwm = -pwm;
		HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, pwm);
	}
}

/**************************************************************************
�������ܣ����õ��C��ռ�ձȣ�������Χ��-16799��16799
��ڲ�������
����  ֵ����
**************************************************************************/
static void motorC_set_pwm(int16_t pwm)
{
	pwm *= MOTORC_POLARITY;
	if(pwm>0)
	{
		HAL_GPIO_WritePin(CIN1_GPIO_Port, CIN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(CIN2_GPIO_Port, CIN2_Pin, GPIO_PIN_SET);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, pwm);
	}
	else
	{
		pwm = -pwm;
		HAL_GPIO_WritePin(CIN1_GPIO_Port, CIN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(CIN2_GPIO_Port, CIN2_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, pwm);
	}
}

/**************************************************************************
�������ܣ����õ��D��ռ�ձȣ�������Χ��-16799��16799
��ڲ�������
����  ֵ����
**************************************************************************/
static void motorD_set_pwm(int16_t pwm)
{
	pwm *= MOTORD_POLARITY;
	if(pwm>0)
	{
		HAL_GPIO_WritePin(DIN1_GPIO_Port, DIN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DIN2_GPIO_Port, DIN2_Pin, GPIO_PIN_SET);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, pwm);
	}
	else
	{
		pwm = -pwm;
		HAL_GPIO_WritePin(DIN1_GPIO_Port, DIN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DIN2_GPIO_Port, DIN2_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, pwm);
	}
}

/////////////////////////////�������ٶȱջ��Ĵ���///////////////////////////////

int cur_A_speed, cur_B_speed, cur_C_speed, cur_D_speed;

/**************************************************************************
�������ܣ���ȡ��������ı������ƴ�ֵ�������ӾͿ���ֱ������Щ
					ֵ����Ϊ�ٶ���
��ڲ�������
����  ֵ����
**************************************************************************/
static void get_motor_encoder_speed(void)
{
	cur_A_speed = motorA.get_encoder();
	cur_B_speed = motorB.get_encoder();
	cur_C_speed = motorC.get_encoder();
	cur_D_speed = motorD.get_encoder();
}
/**************************************************************************
�������ܣ����ݸ�������ı������ƴ�ֵ���������ʵ���ٶȣ����ڷ��͸���λ���Ĵ���
��ڲ�������
����  ֵ����
**************************************************************************/
static void get_motor_encoder_speed2ros(void)
{
	*ros_upper_computer.speedx = (cur_A_speed+cur_B_speed+cur_C_speed+cur_D_speed)/4*k_Speed_calibration;
	*ros_upper_computer.speedy = (cur_B_speed-cur_A_speed+cur_D_speed-cur_C_speed)/4*k_Speed_calibration;
	*ros_upper_computer.speedz = (cur_B_speed-cur_A_speed+cur_C_speed-cur_D_speed)/4*k_Speed_calibration/k_rad_calibration;
}
/**************************************************************************
�������ܣ������������ı������ƴ�ֵ����һ���������»�ȡ��������ֵ
					����Ϊ�ٶ�
��ڲ�������
����  ֵ����
**************************************************************************/
static void clear_motor_encoder_speed(void)
{
	motorA.clear_encoder();
	motorB.clear_encoder();
	motorC.clear_encoder();
	motorD.clear_encoder();
}

//���������pi������
float Velocity_KP=40,Velocity_KI=20;

/**************************************************************************
�������ܣ����A��PI�ٶȻ�
��ڲ�����Encoder �������ĵ�ǰֵ��������Ϊ��ǰ�ٶȣ�
					Target  Ŀ���ٶ�
����  ֵ����
**************************************************************************/
static int Incremental_PI_A (float Encoder,float Target)
{
	 static float Bias,Pwm,Last_bias;
	 Bias=Target-Encoder; //Calculate the deviation //����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias; 
	 if(Pwm>16800)Pwm=16800;
	 if(Pwm<-16800)Pwm=-16800;
	 Last_bias=Bias; //Save the last deviation //������һ��ƫ�� 
	 return Pwm; 
}

/**************************************************************************
�������ܣ����B��PI�ٶȻ�
��ڲ�����Encoder �������ĵ�ǰֵ��������Ϊ��ǰ�ٶȣ�
					Target  Ŀ���ٶ�
����  ֵ����
**************************************************************************/
static int Incremental_PI_B (float Encoder,float Target)
{
	 static float Bias,Pwm,Last_bias;
	 Bias=Target-Encoder; //Calculate the deviation //����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias; 
	 if(Pwm>16800)Pwm=16800;
	 if(Pwm<-16800)Pwm=-16800;
	 Last_bias=Bias; //Save the last deviation //������һ��ƫ�� 
	 return Pwm; 
}

/**************************************************************************
�������ܣ����C��PI�ٶȻ�
��ڲ�����Encoder �������ĵ�ǰֵ��������Ϊ��ǰ�ٶȣ�
					Target  Ŀ���ٶ�
����  ֵ����
**************************************************************************/
static int Incremental_PI_C (float Encoder,float Target)
{
	 static float Bias,Pwm,Last_bias;
	 Bias=Target-Encoder; //Calculate the deviation //����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias; 
	 if(Pwm>16800)Pwm=16800;
	 if(Pwm<-16800)Pwm=-16800;
	 Last_bias=Bias; //Save the last deviation //������һ��ƫ�� 
	 return Pwm; 
}

/**************************************************************************
�������ܣ����D��PI�ٶȻ�
��ڲ�����Encoder �������ĵ�ǰֵ��������Ϊ��ǰ�ٶȣ�
					Target  Ŀ���ٶ�
����  ֵ����
**************************************************************************/
static int Incremental_PI_D (float Encoder,float Target)
{
	 static float Bias,Pwm,Last_bias;
	 Bias=Target-Encoder; //Calculate the deviation //����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias; 
	 if(Pwm>16800)Pwm=16800;
	 if(Pwm<-16800)Pwm=-16800;
	 Last_bias=Bias; //Save the last deviation //������һ��ƫ�� 
	 return Pwm; 
}

/**************************************************************************
�������ܣ��ٵ���get_motor_encoder_speed��ȡ������ٶ�֮������ĸ������
					�ٶȱջ�
��ڲ�������
����  ֵ����
**************************************************************************/
int pwmA, pwmB, pwmC, pwmD;
static void pi_control(void)
{
	pwmA = Incremental_PI_A(cur_A_speed, motorA.target_speed);
	pwmB = Incremental_PI_B(cur_B_speed, motorB.target_speed);
	pwmC = Incremental_PI_C(cur_C_speed, motorC.target_speed);
	pwmD = Incremental_PI_D(cur_D_speed, motorD.target_speed);
	
	motorA.set_pwm(pwmA);
	motorB.set_pwm(pwmB);
	motorC.set_pwm(pwmC);
	motorD.set_pwm(pwmD);
}

/**************************************************************************
�������ܣ�ƽ��speed�ĺ������û�������Ŀ���ٶ�speed���ú�������ƽ������
					��ƽ���������洢�ڵ���ṹ���smooth_speed��Ա��Ȼ�󽫵����
					�����target_speed��Ա��ֵΪsmooth_speed(smooth_speed��float��
					��������漰һ��ǿתint16�Ĺ���)
					
					�����������Ǳ��磺���ڵ�Ŀ���ٶ���0��Ȼ���û�������һ���µ�Ŀ
					���ٶ�20����ô���������ϸ�����ṹ�������target_speedֱ�Ӹ���Ϊ20��
					���ǽ��������Ϊ0.2(SMOOTH_STEP)����һ�ο�����������û����ɼ�ָ�
					20�����ٸı�Ϊ0.4��ֱ���ﵽ20(���ߵ�һ�γ���20)��ά�ֵ���ṹ��
					��Ŀ���ٶ�Ϊ20(ʵ���ϣ�target_speed�����εģ�����0.2����ֵ��С��
					����䣬��������smooth_speedһֱ�����ӣ����target_speed��������s
					peed�ģ���Ҳ��smooth_speed����Ҫ����)
��ڲ���������ṹ��
����  ֵ����
**************************************************************************/
static void to_smooth(Motor* motor)
{
		/*ƽ������*/
		if(motor->speed > motor->target_speed)
    {
        motor->smooth_speed += SMOOTH_STEP;
        if(motor->smooth_speed > motor->speed) motor->smooth_speed = motor->speed;
    }
    else if (motor->speed < motor->target_speed)
    {
        motor->smooth_speed -= SMOOTH_STEP;
        if(motor->smooth_speed < motor->speed) motor->smooth_speed = motor->speed;
    }
		
		/*������ṹ���target_speed��Ա��ֵΪsmooth_speed*/	
		motor->target_speed = (int16_t)motor->smooth_speed;
}

/**************************************************************************
�������ܣ����ĸ������Ŀ���ٶ�ƽ������
��ڲ���������ṹ��
����  ֵ����
**************************************************************************/
static void smooth_control(void)
{
	to_smooth(&motorA);
	to_smooth(&motorB);
	to_smooth(&motorC);
	to_smooth(&motorD);
}


/**************************************************************************
�������ܣ�������Ŀ�������ƽ��Ŀ���ٶȣ���ȡ��������ǰ�ٶȣ�pi�ջ����Ƶ��
��ڲ�������
����  ֵ����
**************************************************************************/
void motor_task(void)
{
		while(systick < 2000)//�����������ִ�д����� (��ֹ��ʼ��һ��ʱ�䣬�����ۼ�)
		{
			osDelay(1);//��ʱ��Ϊ�˷�ֹ�޷������ж� (ԭ��ο�fast_win1.1�汾�ĸ�����־)
		}
		u32 lastWakeTime = systick;
    while(1)
    {	
			vTaskDelayUntil(&lastWakeTime, 10);	//ÿ10��ϵͳ���ĵ���һ�δ����񣨾�����ʱ��
			smooth_control();										//ƽ������target_speed��Ա��ʹ�������ӽ��û����õ�speed
			get_motor_encoder_speed();					//��ȡ��������ĵ�ǰ�ٶ�
			get_motor_encoder_speed2ros();
			clear_motor_encoder_speed();				//���������
			pi_control();												//����pi����
		}
}







