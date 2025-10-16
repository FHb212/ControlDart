#include "DartCore.h"
#include "DataGet.h"
#include "arm_math.h"
#include "pid.h"
#include "flycontrol.h"

extern Dart_data dart_data;
float yaw_setpoint = 0.0f;
float roll_setpoint = 0.0f;
float pitch_setpoint = 0.0f;
float LU_angle, RU_angle, RD_angle, LD_angle;
PID_Config_t pitch_angle_pid = {8.0f, 0.0f, 0.2f, 300.0f, 100.0f};
PID_Config_t yaw_angle_pid = {8.0f, 0.0f, 0.2f, 300.0f, 100.0f};
PID_Config_t pitch_rate_pid = {0.15f, 0.0f, 0.0f, 300.0f, 100.0f};
PID_Config_t yaw_rate_pid = {0.15f, 0.0f, 0.0f, 300.0f, 100.0f};
PID_Config_t roll_angle_pid = {8.0f, 0.0f, 0.2f, 300.0f, 100.0f};
PID_Config_t roll_rate_pid = {0.15f, 0.0f, 0.0f, 300.0f, 100.0f};

void DartCore_XWing_Mix(float Mx, float My, float Mz,
                        float *LU, float *RU, float *RD, float *LD)
{
    float theta = DEG2RAD(45.0f);
    float c = cosf(theta);
    float s = sinf(theta);
    // RU: +cosθ *Mx  -sinθ *My  +sinθ *Mz
    if (RU)
        *RU = Mx * c - My * s + Mz * s;
    // RD: +cosθ *Mx  +sinθ *My  -sinθ *Mz
    if (RD)
        *RD = Mx * c + My * s - Mz * s;
    // LU: -cosθ *Mx  -sinθ *My  -sinθ *Mz
    if (LU)
        *LU = -Mx * c - My * s - Mz * s;
    // LD: -cosθ *Mx  +sinθ *My  +sinθ *Mz
    if (LD)
        *LD = -Mx * c + My * s + Mz * s;
}

void Dart_control_loop()
{
    Dart_control_roll(dart_data.imu.Roll, dart_data.imu.gyro_z);
}

void Dart_control_roll(float roll_angle_now, float roll_rate_now)
{
    float roll_set_rate;
    roll_set_rate = PID_calculate(&roll_angle_pid, roll_angle_now, roll_setpoint);
    roll_setpoint = PID_calculate(&roll_rate_pid, roll_rate_now, roll_set_rate);
    DartCore_XWing_Mix(0.0f, roll_setpoint, 0.0f, &LU_angle, &RU_angle, &RD_angle, &LD_angle);
    FlyControl_SetAngle(LU_angle, RU_angle, RD_angle, LD_angle);
}