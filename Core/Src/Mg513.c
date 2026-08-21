#include "tim.h"
#include "Mg513.h"

int left = 0;
int right = 0;

void MG513Set(int pwml, int pwmr)
{
    MG513_Left(pwml);
    MG513_Right(pwmr);
}

void MG513_Left(int pwm)
{
    if(pwm > 800)
    {
        pwm = 800;
        left = pwm;
    }
    else if(pwm < -800)
    {
        pwm = -800;
        left = pwm;
    }
		else{
				left = pwm;
		}
		
		if (left > 0){
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
				__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,left);
				HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
		}
		else if (left < 0){
			  left *= -1;
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
				__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,left);
				HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
		}
		else{
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
		}
}

void MG513_Right(int pwm)
{
    if(pwm > 800)
    {
        pwm = 800;
        right = pwm;
    }
    else if(pwm < -800)
    {
        pwm = -800;
        right = pwm;
    }
		else{
				right = pwm;
		}
		
		if (right > 0){
				HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
				__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_2,right);
				HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
		}
		else if (right < 0){
			  right *= -1;
				HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
				__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_1,right);
				HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
		}
		else{
				HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
				HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
		}
}
