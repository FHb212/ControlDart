
#pragma once
#include "Flycontrol.h"
#include <math.h>
#define DEG2RAD(x) ((x) * 0.017453292f)
typedef struct
{
    float kp;
    float ki;
    float kd;
    float max_out;
    float max_iout;
} PID_Config_t;
// 左前翼面
float DartCore_XWing_LU(float yaw, float roll, float pitch)
{
    float c45 = cosf(DEG2RAD(45.0f));
    float s45 = sinf(DEG2RAD(45.0f));
    float Ky = 1.0f;
    return pitch * c45 + roll * s45 + yaw * Ky;
}

// 右前翼面
float DartCore_XWing_RU(float yaw, float roll, float pitch)
{
    float c45 = cosf(DEG2RAD(45.0f));
    float s45 = sinf(DEG2RAD(45.0f));
    float Ky = 1.0f;
    return pitch * c45 - roll * s45 - yaw * Ky;
}

// 右后翼面
float DartCore_XWing_RD(float yaw, float roll, float pitch)
{
    float c45 = cosf(DEG2RAD(45.0f));
    float s45 = sinf(DEG2RAD(45.0f));
    float Ky = 1.0f;
    return -pitch * c45 - roll * s45 + yaw * Ky;
}

// 左后翼面L
float DartCore_XWing_LD(float yaw, float roll, float pitch)
{
    float c45 = cosf(DEG2RAD(45.0f));
    float s45 = sinf(DEG2RAD(45.0f));
    float Ky = 1.0f;
    return -pitch * c45 + roll * s45 - yaw * Ky;
}
void DartCore_XWing_Reverse(float A, float B, float C, float D, float *yaw, float *roll, float *pitch)
{
    float c45 = cosf(DEG2RAD(45.0f));
    float s45 = sinf(DEG2RAD(45.0f));
    float Ky = 1.0f;

    *pitch = (A + B - C - D) / (4.0f * c45);
    *roll = (A - B - C + D) / (4.0f * s45);
    *yaw = (A - B + C - D) / (4.0f * Ky);
}