#pragma once
#include "struct_typedef.h"
typedef struct
{
    fp32 angle_now;
    TIM_HandleTypeDef *htim;
    uint32_t channel;

} servo_data;

void Servo_Init(servo_data *servo, fp32 angle_set, TIM_HandleTypeDef *htim, uint32_t channel);

void Servo_Set_Angle(servo_data *servo, fp32 angle_set);

void Servo_Add_Angle(servo_data *servo, fp32 angle_add);