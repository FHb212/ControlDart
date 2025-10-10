#pragma once
#include "struct_typedef.h"

typedef struct
{
    uint32_t pr; // 优先级
    bool req;    // 请求
} RoundRobinNode_t;

int32_t RoundRobinScheduler(RoundRobinNode_t rr[], uint32_t len);