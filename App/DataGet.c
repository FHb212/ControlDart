#include "DataGet.h"
#include "ANO.h"
#include "EncoderHal.h"
#include "i2c.h"
Dart_data dart_data = {0};
JY901S_data g_imu_data = {0};
AS5600_TypeDef *sensor;
extern vision_rawdata g_vision_data;
void DataGetInit(void)
{
    JY901S_Init();
    sensor = AS5600_new();
    AS5600_init(sensor);
    Vision_UART6_Init();
}

void DataGet(void)
{
    JY901S_Get_Data(&g_imu_data);
    AS5600_get_rawAngle(sensor, &dart_data.attack_angle);
}

void DataTrans(void)
{
    dart_data.imu = IMUtrans(&g_imu_data);
    dart_data.vision = Visiontrans(&g_vision_data);
}

IMU_data IMUtrans(const JY901S_data *imu_data)
{
    IMU_data result;
    result.Roll = imu_data->fAngle[0];
    result.Pitch = imu_data->fAngle[1];
    result.Yaw = imu_data->fAngle[2];
    result.acc_x = imu_data->fAcc[0];
    result.acc_y = imu_data->fAcc[1];
    result.acc_z = imu_data->fAcc[2];
    result.gyro_x = imu_data->fGyro[0];
    result.gyro_y = imu_data->fGyro[1];
    result.gyro_z = imu_data->fGyro[2];
    return result;
}

Vision_data Visiontrans(const vision_rawdata *vision_rawdata)
{
    Vision_data result;
    result.is_target = vision_rawdata->detected;
    result.dx = vision_rawdata->dx;
    result.dy = vision_rawdata->dy;
    return result;
}