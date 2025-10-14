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
    Vision_UART6_DMA_Start();
    sensor = AS5600_new();
    AS5600_init(sensor);
}

void DataGet(void)
{
    JY901S_Get_Data(&g_imu_data);
    AS5600_get_rawAngle(sensor, &dart_data.attack_angle);
}

void DataTrans(void)
{
    dart_data.imu = *IMUtrans(&g_imu_data);
    dart_data.vision = *Visiontrans(&g_vision_data);
}

IMU_data *IMUtrans(JY901S_data *imu_data)
{
    IMU_data *p = (IMU_data *)malloc(sizeof(IMU_data));
    if (p == NULL)
    {
        // Handle memory allocation failure
        return NULL;
    }
    p->Roll = imu_data->fAngle[0];
    p->Pitch = imu_data->fAngle[1];
    p->Yaw = imu_data->fAngle[2];
    p->acc_x = imu_data->fAcc[0];
    p->acc_y = imu_data->fAcc[1];
    p->acc_z = imu_data->fAcc[2];
    p->gyro_x = imu_data->fGyro[0];
    p->gyro_y = imu_data->fGyro[1];
    p->gyro_z = imu_data->fGyro[2];
    return p;
}
Vision_data *Visiontrans(vision_rawdata *vision_rawdata)
{
    Vision_data *p = (Vision_data *)malloc(sizeof(Vision_data));
    if (p == NULL)
    {
        // Handle memory allocation failure
        return NULL;
    }
    p->is_target = vision_rawdata->detected;
    p->dx = vision_rawdata->dx;
    p->dy = vision_rawdata->dy;
    return p;
}