#pragma once
#include "struct_typedef.h"


// 定义一阶滞后滤波器结构体
typedef struct {
    float alpha; // 时间常数
    float previous_output;
} FirstOrderLagFilter;
 

void initializeFilter(FirstOrderLagFilter* filter, float alpha);
float filterValue(FirstOrderLagFilter* filter, float input);
