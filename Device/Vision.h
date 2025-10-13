#pragma once
#include <stdbool.h>
#include <stdint.h>
#define UART6_DMA_RX_SIZE 4
typedef struct
{
    bool detected;
    int8_t dx;
    int8_t dy;
} vision_rawdata;
void Vision_Uart6_DataHandler(uint8_t *buf);
void Vision_UART6_DMA_Start(void);
