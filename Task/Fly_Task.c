#include "Fly_Task.h"
#include "main.h"
#include "cmsis_os.h"
#include "Jy901s.h"
#include "EncoderHal.h"
#include "i2c.h"
#include "FlyControl.h"
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
    FlyControl_Init();
    for (;;)
    {

        // AS5600_get_rawAngle(sensor, &angle);
        FlyControl_SetAngle(0, 0, 0, 0);
        osDelay(1);
    }
    /* USER CODE END Start_Fly */
}
