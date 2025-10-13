#pragma once

static const float LU_init_angle = .0f; // 初始角度
static const float RU_init_angle = .0f; // 初始角度
static const float RD_init_angle = .0f; // 初始角度
static const float LD_init_angle = .0f; // 初始角度

void FlyControl_Init(void);

void FlyControl_SetAngle(float LU_angle, float RU_angle, float RD_angle, float LD_angle);