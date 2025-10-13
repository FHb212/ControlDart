#include "stdint.h"
#include "Vision.h"
#include "usart.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include "stdint.h"

uint8_t uart6_dma_rx_buf[UART6_DMA_RX_SIZE];
vision_rawdata g_vision_data = {0};
// 视觉数据处理函数
void Vision_Uart6_DataHandler(uint8_t *buf)
{
    if (buf[0] == 0x10)
    {
        g_vision_data.detected = buf[1];
        g_vision_data.dx = (int8_t)buf[2];
        g_vision_data.dy = (int8_t)buf[3];
    }
}

void Vision_UART6_DMA_Start(void)
{
    HAL_UART_Receive_DMA(&huart6, uart6_dma_rx_buf, UART6_DMA_RX_SIZE);
}
