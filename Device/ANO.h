#pragma once
#include <stdint.h>
#include "ANOBsp.h"

void ANO_DT_send_euler(float roll, float pitch, float yaw);

void ANO_DT_send_gyro(float gyro_x, float gyro_y, float gyro_z);

void ANO_DT_send_acc(float acc_x, float acc_y, float acc_z);

void ANO_DT_send_vision(int16_t dx, int16_t dy, uint8_t detected);

void ANO_DT_send_encoder(uint16_t encoder_count);

void ANO_DT_send_int16(int16_t data1);

void ANO_DT_send_float(float data1);

void ANO_DT_send_int32(int32_t data1);