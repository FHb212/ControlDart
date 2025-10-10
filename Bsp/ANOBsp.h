#pragma once

#include "stdint.h"
#include "main.h"
#include "usart.h"
/*!
 * @brief    向上位机发送发送8个int16_t数据
 *
 * @param    data1 - data8  ： 发送给上位机显示波形
 *
 * @return   无
 *
 * @note     无
 *
 * @see      ANO_DT_send_int16(1, 2, 3, 0, 0, 0, 0, 0);
 *
 * @date     2021/5/28 星期二
 */
void ANO_DT_send_int16(short data1);
