#pragma once
#include "struct_typedef.h"


// ����һ���ͺ��˲����ṹ��
typedef struct {
    float alpha; // ʱ�䳣��
    float previous_output;
} FirstOrderLagFilter;
 

void initializeFilter(FirstOrderLagFilter* filter, float alpha);
float filterValue(FirstOrderLagFilter* filter, float input);
