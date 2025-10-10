#include "RoundRobin.h"

// 更新优先级
static void RoundRobinUpdatePriority(RoundRobinNode_t rr[], uint32_t selectedIndex, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
    {
        if (rr[i].pr > rr[selectedIndex].pr)
        {
            rr[i].pr--;
        }
    }
    rr[selectedIndex].req = false;
    rr[selectedIndex].pr = len - 1;
}

// 公平轮询函数
int32_t RoundRobinScheduler(RoundRobinNode_t rr[], uint32_t len)
{
    int32_t selected = -1;
    uint8_t highestPriority = len;

    for (uint32_t i = 0; i < len; i++)
    {
        if (rr[i].req == true && rr[i].pr < highestPriority)
        {
            highestPriority = rr[i].pr;
            selected = i;
        }
    }

    if (selected != -1)
        RoundRobinUpdatePriority(rr, selected, len);

    return selected;
}
