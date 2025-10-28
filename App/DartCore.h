#pragma once
#include "Flycontrol.h"
#include <math.h>
#include "pid.h"
static float g2 = 1.414;
typedef struct
{
    float kp;
    float ki;
    float kd;
    float max_out;
    float max_iout;
} PID_Config_t;

// 角度控制
typedef struct
{
    pid_type_def yaw_angle_pid;
    pid_type_def pitch_angle_pid;
    pid_type_def roll_angle_pid;
    pid_type_def yaw_rate_pid;
    pid_type_def pitch_rate_pid;
    pid_type_def roll_rate_pid;
} Dart_Core_PID_t;

static void PidInitAdapter(pid_type_def *pid, uint8_t mode, const PID_Config_t pidConfigs);
void DartCore_Init();
void DartCore_XWing_Mix(float Mx, float My, float Mz,
                        float *LU, float *RU, float *RD, float *LD);

void DartCore_XWing_Reverse(float A, float B, float C, float D, float *yaw, float *roll, float *pitch);
void Dart_control_yaw_roll(float dyaw, float istarget, float roll_angle_now);
void Dart_control_roll(float roll_angle_now);
void Dart_control_loop();
