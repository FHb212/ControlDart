#include "Servo.h"
#include "tim.h"
void Servo_Init(servo_data *servo, fp32 angle_set, TIM_HandleTypeDef *htim, uint32_t channel)
{
    int16_t ccr;
    servo->htim = htim;
    servo->channel = channel;
    if (angle_set > 60.0f)
        angle_set = 0.0f;
    else if (angle_set < -60.0f)
        angle_set = -60.0f;
    ccr = (int16_t)(angle_set / 60.0f * 10 + 1500);
    servo->angle_now = angle_set;
    __HAL_TIM_SET_COMPARE(servo->htim, servo->channel, ccr);
}

void Servo_SetAngle(servo_data *servo, fp32 angle_set)
{
    int16_t ccr;
    servo->angle_now = angle_set;
    if (angle_set > 60.0f)
        angle_set = 0.0f;
    else if (angle_set < -60.0f)
        angle_set = -60.0f;
    ccr = (int16_t)(angle_set / 60.0f * 10 + 1500);
    __HAL_TIM_SET_COMPARE(servo->htim, servo->channel, ccr);
}

void Servo_AddAngle(servo_data *servo, fp32 angle_add)
{
    int16_t ccr;
    servo->angle_now += angle_add;
    if (servo->angle_now > 60.0f)
        servo->angle_now = 60.0f;
    else if (servo->angle_now < -60.0f)
        servo->angle_now = -60.0f;
    ccr = (int16_t)(servo->angle_now / 60.0f * 10 + 1500);
    __HAL_TIM_SET_COMPARE(servo->htim, servo->channel, ccr);
}