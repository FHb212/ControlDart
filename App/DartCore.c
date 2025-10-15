#include "DartCore.h"
#include "DataGet.h"
#include "arm_math.h"
#include "pid.h"

PID_Config_t pitch_angle_pid = {8.0f, 0.0f, 0.2f, 300.0f, 100.0f};
PID_Config_t yaw_angle_pid = {8.0f, 0.0f, 0.2f, 300.0f, 100.0f};
PID_Config_t pitch_rate_pid = {0.15f, 0.0f, 0.0f, 300.0f, 100.0f};
PID_Config_t yaw_rate_pid = {0.15f, 0.0f, 0.0f, 300.0f, 100.0f};
PID_Config_t roll_angle_pid = {8.0f, 0.0f, 0.2f, 300.0f, 100.0f};
PID_Config_t roll_rate_pid = {0.15f, 0.0f, 0.0f, 300.0f, 100.0f};