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
// 合成一个函数，分别输出四个翼面角度到四个变量

void DartCore_XWing_Mix(float Mx, float My, float Mz,
                        float *LU, float *RU, float *RD, float *LD);