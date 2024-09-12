/**
  ************************************************************************************
  * File Name          : motor.c
  * Description        : Code for motor applications
	* @author            : SuperEgo-郭耀辉
  ************************************************************************************
  * @attention
	* 为用户提供以下八个api来控制四个电机的行为：
  *
  * 调用以下接口输出电机A的pwm：
	*	motorA.set_pwm(3000)，输入范围：-16799到16799（同时必须保证motor_task没有在运行）
	*
	*	调用以下接口pi闭环控制电机：
	*	motorA.speed = 20，输入范围：-80到80（同时必须保证motor_task任务被rtos运行）
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
函数功能：电机对象绑定函数，输入参数为电机对象的函数指针和电机对象指针，
					此函数负责将电机对象与函数指针绑定（类似于C++的实例化）
入口参数：略
返回  值：略
**************************************************************************/
static void motor_object_init(
		Motor* motor, 
		motor_set_pwm set_pwm_func, 
		Get_encoder get_encoder, 
		Clear_encoder clear_encoder)
{
	motor->smooth_speed = 0;
	motor->speed = 0;
	motor->set_pwm = set_pwm_func;				//绑定pwm驱动函数
	motor->target_speed = 0;							//设置目标速度为0
	motor->get_encoder = get_encoder;			//绑定编码器数值读取函数
	motor->clear_encoder = clear_encoder;	//绑定编码器清零函数
}

/**************************************************************************
函数功能：初始化关于电机的必要引脚，绑定电机对象的成员函数
入口参数：略
返回  值：略
**************************************************************************/
void motor_init(void)
{
	//由于DIN1与串口5TX引脚冲突(实际上，串口5的sbus协议解析用不到tx)。
	//在cubemx里无法生成代码，因此在这里单独初始化DIN1为推挽输出
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
	
	//下面对电机相关引脚进行初始化
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
	
	/*初始化四个电机对象，绑定相关的函数*/
	motor_object_init(&motorA, motorA_set_pwm, GetEncoderA, encoderA_clear);
	motor_object_init(&motorB, motorB_set_pwm, GetEncoderB, encoderB_clear);
	motor_object_init(&motorC, motorC_set_pwm, GetEncoderC, encoderC_clear);
	motor_object_init(&motorD, motorD_set_pwm, GetEncoderD, encoderD_clear);
}

/**************************************************************************
函数功能：设置电机A的占空比，参数范围：-16799到16799
入口参数：略
返回  值：略
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
函数功能：设置电机B的占空比，参数范围：-16799到16799
入口参数：略
返回  值：略
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
函数功能：设置电机C的占空比，参数范围：-16799到16799
入口参数：略
返回  值：略
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
函数功能：设置电机D的占空比，参数范围：-16799到16799
入口参数：略
返回  值：略
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

/////////////////////////////下面是速度闭环的代码///////////////////////////////

int cur_A_speed, cur_B_speed, cur_C_speed, cur_D_speed;

/**************************************************************************
函数功能：获取各个电机的编码器计次值，这样子就可以直接用这些
					值来作为速度了
入口参数：略
返回  值：略
**************************************************************************/
static void get_motor_encoder_speed(void)
{
	cur_A_speed = motorA.get_encoder();
	cur_B_speed = motorB.get_encoder();
	cur_C_speed = motorC.get_encoder();
	cur_D_speed = motorD.get_encoder();
}
/**************************************************************************
函数功能：根据各个电机的编码器计次值，结算底盘实际速度，用于发送给上位机的串口
入口参数：略
返回  值：略
**************************************************************************/
static void get_motor_encoder_speed2ros(void)
{
	*ros_upper_computer.speedx = (cur_A_speed+cur_B_speed+cur_C_speed+cur_D_speed)/4*k_Speed_calibration;
	*ros_upper_computer.speedy = (cur_B_speed-cur_A_speed+cur_D_speed-cur_C_speed)/4*k_Speed_calibration;
	*ros_upper_computer.speedz = (cur_B_speed-cur_A_speed+cur_C_speed-cur_D_speed)/4*k_Speed_calibration/k_rad_calibration;
}
/**************************************************************************
函数功能：清楚各个电机的编码器计次值，下一个周期重新获取编码器的值
					来作为速度
入口参数：略
返回  值：略
**************************************************************************/
static void clear_motor_encoder_speed(void)
{
	motorA.clear_encoder();
	motorB.clear_encoder();
	motorC.clear_encoder();
	motorD.clear_encoder();
}

//各个电机的pi控制器
float Velocity_KP=40,Velocity_KI=20;

/**************************************************************************
函数功能：电机A的PI速度环
入口参数：Encoder 编码器的当前值（近似认为当前速度）
					Target  目标速度
返回  值：略
**************************************************************************/
static int Incremental_PI_A (float Encoder,float Target)
{
	 static float Bias,Pwm,Last_bias;
	 Bias=Target-Encoder; //Calculate the deviation //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias; 
	 if(Pwm>16800)Pwm=16800;
	 if(Pwm<-16800)Pwm=-16800;
	 Last_bias=Bias; //Save the last deviation //保存上一次偏差 
	 return Pwm; 
}

/**************************************************************************
函数功能：电机B的PI速度环
入口参数：Encoder 编码器的当前值（近似认为当前速度）
					Target  目标速度
返回  值：略
**************************************************************************/
static int Incremental_PI_B (float Encoder,float Target)
{
	 static float Bias,Pwm,Last_bias;
	 Bias=Target-Encoder; //Calculate the deviation //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias; 
	 if(Pwm>16800)Pwm=16800;
	 if(Pwm<-16800)Pwm=-16800;
	 Last_bias=Bias; //Save the last deviation //保存上一次偏差 
	 return Pwm; 
}

/**************************************************************************
函数功能：电机C的PI速度环
入口参数：Encoder 编码器的当前值（近似认为当前速度）
					Target  目标速度
返回  值：略
**************************************************************************/
static int Incremental_PI_C (float Encoder,float Target)
{
	 static float Bias,Pwm,Last_bias;
	 Bias=Target-Encoder; //Calculate the deviation //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias; 
	 if(Pwm>16800)Pwm=16800;
	 if(Pwm<-16800)Pwm=-16800;
	 Last_bias=Bias; //Save the last deviation //保存上一次偏差 
	 return Pwm; 
}

/**************************************************************************
函数功能：电机D的PI速度环
入口参数：Encoder 编码器的当前值（近似认为当前速度）
					Target  目标速度
返回  值：略
**************************************************************************/
static int Incremental_PI_D (float Encoder,float Target)
{
	 static float Bias,Pwm,Last_bias;
	 Bias=Target-Encoder; //Calculate the deviation //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias; 
	 if(Pwm>16800)Pwm=16800;
	 if(Pwm<-16800)Pwm=-16800;
	 Last_bias=Bias; //Save the last deviation //保存上一次偏差 
	 return Pwm; 
}

/**************************************************************************
函数功能：再调用get_motor_encoder_speed读取到电机速度之后，完成四个电机的
					速度闭环
入口参数：略
返回  值：略
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
函数功能：平滑speed的函数，用户传入电机目标速度speed，该函数进行平滑处理
					将平滑处理结果存储在电机结构体的smooth_speed成员，然后将电机结
					构体的target_speed成员赋值为smooth_speed(smooth_speed是float，
					因此这里涉及一次强转int16的过程)
					
					简单来讲，就是比如：现在的目标速度是0，然后用户给定了一个新的目
					标速度20，那么并不会马上给电机结构体里面的target_speed直接更改为20，
					而是仅仅将其变为0.2(SMOOTH_STEP)，下一次控制周期如果用户依旧坚持给
					20，则再改变为0.4，直到达到20(或者第一次超过20)则维持电机结构体
					的目标速度为20(实际上，target_speed是整形的，加上0.2其数值大小并
					不会变，但是由于smooth_speed一直在增加，因此target_speed总能趋于s
					peed的，这也是smooth_speed的主要作用)
入口参数：电机结构体
返回  值：无
**************************************************************************/
static void to_smooth(Motor* motor)
{
		/*平滑处理*/
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
		
		/*将电机结构体的target_speed成员赋值为smooth_speed*/	
		motor->target_speed = (int16_t)motor->smooth_speed;
}

/**************************************************************************
函数功能：将四个电机的目标速度平滑处理
入口参数：电机结构体
返回  值：无
**************************************************************************/
static void smooth_control(void)
{
	to_smooth(&motorA);
	to_smooth(&motorB);
	to_smooth(&motorC);
	to_smooth(&motorD);
}


/**************************************************************************
函数功能：电机核心控制任务，平滑目标速度，读取编码器当前速度，pi闭环控制电机
入口参数：无
返回  值：无
**************************************************************************/
void motor_task(void)
{
		while(systick < 2000)//开机两秒后再执行此任务 (防止初始的一段时间，积分累计)
		{
			osDelay(1);//延时是为了防止无法进入中断 (原因参考fast_win1.1版本的更新日志)
		}
		u32 lastWakeTime = systick;
    while(1)
    {	
			vTaskDelayUntil(&lastWakeTime, 10);	//每10个系统节拍调用一次此任务（绝对延时）
			smooth_control();										//平滑处理target_speed成员，使其愈发接近用户设置的speed
			get_motor_encoder_speed();					//获取各个电机的当前速度
			get_motor_encoder_speed2ros();
			clear_motor_encoder_speed();				//清除编码器
			pi_control();												//进行pi控制
		}
}







