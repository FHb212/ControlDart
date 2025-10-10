#pragma once
#include "struct_typedef.h"

typedef struct
{
    float Roll;
    float Pitch;
    float Yaw;
    float acc_x;
    float acc_y;
    float acc_z;
    float gyro_x;
    float gyro_y;
    float gyro_z;
} IMU_data;
typedef struct
{
    bool_t is_target;
    int8_t dx;
    int8_t dy;
} Vision_data;
typedef struct
{
    IMU_data imu;
    Vision_data vision;
    float attack_angle;
} Dart_data;

void DataGetInit(void);

void DataGet(void);

IMU_data *IMUtrans(JY901S_data *imu_data);