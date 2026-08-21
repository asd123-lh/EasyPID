#ifndef __PID_H__
#define __PID_H__
#include "main.h"
extern float error0, error1, error2;
extern float actual, out;
extern float Ki, Kp, Kd;
extern float target;
extern int pid_left, pid_right;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
