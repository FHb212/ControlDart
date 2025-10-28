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
PID_Config_t roll_angle_pid = {1.0f, 0.0f, 0.0f, 50.0f, 100.0f};
PID_Config_t roll_rate_pid = {0.15f, 0.0f, 0.0f, 300.0f, 100.0f};

static void PidInitAdapter(pid_type_def *pid, uint8_t mode, const PID_Config_t pidConfigs)
{
    float _pid[3] = {pidConfigs.kp, pidConfigs.ki, pidConfigs.kd};
    PID_init(pid, mode, _pid, pidConfigs.max_out, pidConfigs.max_iout);
}

void DartCore_Init()
{
    PidInitAdapter(&Dart_Core.yaw_angle_pid, PID_DELTA, yaw_angle_pid);
    PidInitAdapter(&Dart_Core.pitch_rate_pid, PID_DELTA, pitch_rate_pid);
    PidInitAdapter(&Dart_Core.roll_angle_pid, PID_POSITION, roll_angle_pid);
    PidInitAdapter(&Dart_Core.yaw_rate_pid, PID_DELTA, yaw_rate_pid);
    PidInitAdapter(&Dart_Core.roll_rate_pid, PID_DELTA, roll_rate_pid);
    PidInitAdapter(&Dart_Core.pitch_rate_pid, PID_DELTA, pitch_rate_pid);
}

void DartCore_XWing_Mix(float Mx, float My, float Mz,
                        float *LU, float *RU, float *RD, float *LD)
{
    // RU: +cosθ *Mx  -sinθ *My  +sinθ *Mz
    if (RU)
        *RU = Mx / 4 + My + Mz * g2 / 2;
    // RD: +cosθ *Mx  +sinθ *My  -sinθ *Mz
    if (RD)
        *RD = Mx / 4 + My - Mz * g2 / 2;
    // LU: -cosθ *Mx  -sinθ *My  -sinθ *Mz
    if (LU)
        *LU = Mx / 4 + My + Mz * g2 / 2;
    // LD: -cosθ *Mx  +sinθ *My  +sinθ *Mz
    if (LD)
        *LD = Mx / 4 + My - Mz * g2 / 2;
}

void Dart_control_loop()
{
     Dart_control_roll(dart_data.imu.Roll);
    //Dart_control_yaw_roll(dart_data.vision.dx, dart_data.vision.is_target, dart_data.imu.Roll);
}

void Dart_control_roll(float roll_angle_now)
{
    float roll_set_rate;
    roll_set_rate = PID_calc(&Dart_Core.roll_angle_pid, roll_angle_now, roll_setpoint);
    // roll_setpoint = PID_calc(&Dart_Core.roll_rate_pid, roll_rate_now, roll_set_rate);
    DartCore_XWing_Mix(0.0f, roll_set_rate, 0.0f, &LU_angle, &RU_angle, &RD_angle, &LD_angle);
    FlyControl_SetAngle(LU_angle, RU_angle, RD_angle, LD_angle);
}

void Dart_control_yaw_roll(float dyaw, float istarget, float roll_angle_now)
{
    float yaw_set_rate;
    float roll_set_rate;
    if (istarget == 1)
    {
        yaw_set_rate = PID_calc(&Dart_Core.yaw_angle_pid, dyaw, yaw_setpoint);
        roll_set_rate = PID_calc(&Dart_Core.roll_angle_pid, roll_angle_now, roll_setpoint);
        DartCore_XWing_Mix(0.0f, roll_set_rate, yaw_set_rate, &LU_angle, &RU_angle, &RD_angle, &LD_angle);
        FlyControl_SetAngle(LU_angle, RU_angle, RD_angle, LD_angle);
    }
    else
    {
        roll_set_rate = PID_calc(&Dart_Core.roll_angle_pid, roll_angle_now, roll_setpoint);
        // yaw_setpoint = PID_calc(&Dart_Core.yaw_rate_pid, yaw_rate_now, yaw_set_rate);
        // roll_setpoint = PID_calc(&Dart_Core.roll_rate_pid, roll_rate_now, roll_set_rate);
        DartCore_XWing_Mix(0.0f, roll_set_rate, 0, &LU_angle, &RU_angle, &RD_angle, &LD_angle);
        FlyControl_SetAngle(LU_angle, RU_angle, RD_angle, LD_angle);
    }
}
