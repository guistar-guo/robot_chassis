#ifndef _CHASSIS_CONTROL_
#define _CHASSIS_CONTROL_

#include "main.h"

void chassis_control_test(void);
void chassis_control(float vx,float vy,float vw);
void chassis_ros_control(void);

#define PI 3.1415926
#define k_Speed_calibration 22.0f
#define k_rad_calibration (1.02/PI)

#endif



































