#include "DartCore.h"
#include "DataGet.h"
#include "arm_math.h"
#include "flycontrol.h"

extern Dart_data dart_data;
float yaw_setpoint = 0.0f;
float roll_setpoint = 0.0f;
float pitch_setpoint = 0.0f;
float LU_angle, RU_angle, RD_angle, LD_angle;

Dart_Core_PID_t Dart_Core;

PID_Config_t pitch_angle_pid = {8.0f, 0.0f, 0.2f, 300.0f, 100.0f};
PID_Config_t yaw_angle_pid = {8.0f, 0.0f, 0.2f, 300.0f, 100.0f};
PID_Config_t pitch_rate_pid = {0.15f, 0.0f, 0.0f, 300.0f, 100.0f};
PID_Config_t yaw_rate_pid = {0.15f, 0.0f, 0.0f, 300.0f, 100.0f};
PID_Config_t roll_angle_pid = {8.0f, 0.0f, 0.2f, 300.0f, 100.0f};
PID_Config_t roll_rate_pid = {0.15f, 0.0f, 0.0f, 300.0f, 100.0f};

static void PidInitAdapter(pid_type_def *pid, uint8_t mode, const PID_Config_t pidConfigs)
{
    float _pid[3] = {pidConfigs.kp, pidConfigs.ki, pidConfigs.kd};
    PID_init(pid, mode, _pid, pidConfigs.max_out, pidConfigs.max_iout);
}

void DartCore_Init()
{
    PidInitAdapter(&Dart_Core.yaw_angle_pid, PID_POSITION, yaw_angle_pid);
    PidInitAdapter(&Dart_Core.pitch_rate_pid, PID_POSITION, pitch_rate_pid);
    PidInitAdapter(&Dart_Core.roll_angle_pid, PID_POSITION, roll_angle_pid);
    PidInitAdapter(&Dart_Core.yaw_rate_pid, PID_POSITION, yaw_rate_pid);
    PidInitAdapter(&Dart_Core.roll_rate_pid, PID_POSITION, roll_rate_pid);
    PidInitAdapter(&Dart_Core.pitch_rate_pid, PID_POSITION, pitch_rate_pid);
}

void DartCore_XWing_Mix(float Mx, float My, float Mz,
                        float *LU, float *RU, float *RD, float *LD)
{
    // RU: +cosθ *Mx  -sinθ *My  +sinθ *Mz
    if (RU)
        *RU = Mx / 4 - My * g2 / 4 - Mz * g2 / 4;
    // RD: +cosθ *Mx  +sinθ *My  -sinθ *Mz
    if (RD)
        *RD = Mx / 4 + My * g2 / 4 - Mz * g2 / 4;
    // LU: -cosθ *Mx  -sinθ *My  -sinθ *Mz
    if (LU)
        *LU = Mx / 4 + My * g2 / 4 + Mz * g2 / 4;
    // LD: -cosθ *Mx  +sinθ *My  +sinθ *Mz
    if (LD)
        *LD = Mx / 4 - My * g2 / 4 + Mz * g2 / 4;
}

void Dart_control_loop()
{
    Dart_control_roll(dart_data.imu.Roll, dart_data.imu.gyro_z);
}

void Dart_control_roll(float roll_angle_now, float roll_rate_now)
{
    float roll_set_rate;
    roll_set_rate = PID_calc(&Dart_Core.roll_angle_pid, roll_angle_now, roll_setpoint);
    roll_setpoint = PID_calc(&Dart_Core.roll_rate_pid, roll_rate_now, roll_set_rate);
    DartCore_XWing_Mix(0.0f, roll_setpoint, 0.0f, &LU_angle, &RU_angle, &RD_angle, &LD_angle);
    FlyControl_SetAngle(LU_angle, RU_angle, RD_angle, LD_angle);
}