#pragma once
#include "usart.h"
#include <stdint.h>

/**
 * @brief  通过串口二发送数据
 * @param  pData: 数据指针
 * @param  size: 数据长度
 */
void TransmitHal_Send(uint8_t *pData, uint16_t size);
