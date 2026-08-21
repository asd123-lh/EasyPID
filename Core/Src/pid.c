#include "main.h"
#include "MG513.h"
#include "pid.h"
#include "sevenway.h"
#include "tim.h"

float target = 120U;
extern volatile int error;

float error0, error1, error2;
float actual, out;
float Ki = 0.0f, Kp = 0.2f, Kd = 0.02f;
int pid_left = 0;
int pid_right = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM6)
    {
        __disable_irq();
        int err_raw = error;
        __enable_irq();

        error2 = error1;
        error1 = error0;
        error0 = err_raw; 

        if(error0 == 0.0f)
        {
            out = 0.0f;
            error1 = 0.0f;
            error2 = 0.0f;
        }
        else
        {
            float delta = Kp*(error0 - error1) + Ki*error0 + Kd*(error0 - 2*error1 + error2);
            out += delta;
        }

        if(out > 60)  out = 60;
        if(out < -60) out = -60;

        int left  = (int)target + (int)out;
        int right = (int)target - (int)out;

        if(left > 800)  left = 800;
        if(left < -800) left = -800;
        if(right > 800) right = 800;
        if(right < -800) right = -800;

        pid_left = left;
        pid_right = right;

        MG513Set(left, right);
    }
}
