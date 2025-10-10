#include "Fly_Task.h"
#include "main.h"
#include "cmsis_os.h"
#include "Jy901s.h"
#include "EncoderHal.h"
#include "i2c.h"
extern TIM_HandleTypeDef htim2;
uint16_t angle;
HAL_StatusTypeDef status;
void fly_task(void const *argument)
{
    /* USER CODE BEGIN Start_Fly */
    /* Infinite loop */
    // AS5600_TypeDef *sensor = AS5600_new();
    // sensor->i2c_handle = &hi2c2;
    // sensor->i2c_timeout = 50;
    // sensor->dir_port = dir_GPIO_Port;
    // sensor->dir_pin = dir_Pin;
    // AS5600_init(sensor);
    for (;;)
    {

        // AS5600_get_rawAngle(sensor, &angle);
        // 1. 启动 PWM
        HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

        // 2. 设置占空比（如 50%）
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 1500);
        osDelay(1);
    }
    /* USER CODE END Start_Fly */
}
