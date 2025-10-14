#pragma once

#include "stdint.h"
#include "main.h"
#include "usart.h"
#define BYTE0(dwTemp) (*((char *)(&dwTemp)))     /*!< uint32_t 数据拆分 byte0  */
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1)) /*!< uint32_t 数据拆分 byte1  */
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2)) /*!< uint32_t 数据拆分 byte2  */
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3)) /*!< uint32_t 数据拆分 byte3  */
