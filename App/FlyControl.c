#include "FlyControl.h"
#include "Servo.h"
#include "tim.h"
servo_data servo_LU;
servo_data servo_RU;
servo_data servo_RD;
servo_data servo_LD;

void FlyControl_Init(void)
{
    Servo_Init(&servo_LU, LU_init_angle, &htim2, TIM_CHANNEL_1);
    Servo_Init(&servo_RU, RU_init_angle, &htim2, TIM_CHANNEL_2);
    Servo_Init(&servo_RD, RD_init_angle, &htim3, TIM_CHANNEL_3);
    Servo_Init(&servo_LD, LD_init_angle, &htim3, TIM_CHANNEL_4);
}

void FlyControl_SetAngle(float LU_angle, float RU_angle, float RD_angle, float LD_angle)
{
    Servo_SetAngle(&servo_LU, LU_angle);
    Servo_SetAngle(&servo_RU, RU_angle);
    Servo_SetAngle(&servo_RD, RD_angle);
    Servo_SetAngle(&servo_LD, LD_angle);
}