#include "FlyControl.h"
#include "Servo.h"
#include "tim.h"
servo_data servo_LU;
servo_data servo_RU;
servo_data servo_RD;
servo_data servo_LD;

void FlyControl_Init(void)
{
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
    Servo_Init(&servo_LU, LU_init_angle, &htim3, TIM_CHANNEL_3);
    Servo_Init(&servo_RU, RU_init_angle, &htim2, TIM_CHANNEL_2);
    Servo_Init(&servo_RD, RD_init_angle, &htim3, TIM_CHANNEL_4);
    Servo_Init(&servo_LD, LD_init_angle, &htim2, TIM_CHANNEL_1);
}

void FlyControl_SetAngle(float LU_angle, float RU_angle, float RD_angle, float LD_angle)
{
    LU_angle += LU_init_angle;
    RU_angle += RU_init_angle;
    RD_angle += RD_init_angle;
    LD_angle += LD_init_angle;
    Servo_SetAngle(&servo_LU, LU_angle);
    Servo_SetAngle(&servo_RU, RU_angle);
    Servo_SetAngle(&servo_RD, RD_angle);
    Servo_SetAngle(&servo_LD, LD_angle);
}