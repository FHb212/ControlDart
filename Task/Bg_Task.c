#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include "Beep.h"
#include "LED.h"
#include "Jy901s.h"
#include <stdio.h>
#include "ANOBsp.h"
#include "vision.h"
void bg_task(void const *argument)
{
    /* USER CODE BEGIN bg_task */
    JY901S_data imu_data;
    JY901S_Init();
    Vision_UART6_DMA_Start();

    /* Infinite loop */
    for (;;)
    {
        JY901S_Get_Data(&imu_data);
        // ANO_DT_send_int16((short)(imu_data.fAcc[0] * 1000)); // 发送加速度数据，放大1000倍
        // ANO_DT_send_int16((short)(imu_data.fAcc[1] * 1000));
        ANO_DT_send_int16((short)(imu_data.fAngle[2] * 100)); // 发送角度数据，放大100倍

        osDelay(5); // Delay for 5 ms
    }

    /* USER CODE END bg_task */
}