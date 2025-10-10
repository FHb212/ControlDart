#ifndef __JY901S_DEVICE_H
#define __JY901S_DEVICE_H

#include "struct_typedef.h"
#include "Jy901sBsp.h"
#define ACC_UPDATE 0x01
#define GYRO_UPDATE 0x02
#define ANGLE_UPDATE 0x04
#define MAG_UPDATE 0x08
#define READ_UPDATE 0x80

typedef struct
{
    float fAcc[3], fGyro[3], fAngle[3];
    int fMag[3];
} JY901S_data;

void SensorUartSend(unsigned char *p_data, unsigned int uiSize);
void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum);
void Delayms(uint16_t ucMs);
void JY901S_Init(void);
void JY901S_Get_Data(JY901S_data *data);

#endif
