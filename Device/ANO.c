#include "ANO.h"
#include "ANOBsp.h"

unsigned char data_to_send[50];     // 用于绘图
unsigned char data_to_send_out[50]; // 用于传输
unsigned char data_to_get[50];      // 接收数据缓存
void ANO_DT_send_int16(int16_t data1)
{
    unsigned char _cnt = 0;
    unsigned char i = 0;
    unsigned char sumcheck = 0;
    unsigned char addcheck = 0;

    data_to_send[_cnt++] = 0xAA; // 匿名协议帧头  0xAA
    data_to_send[_cnt++] = 0xFF;
    data_to_send[_cnt++] = 0xF1; // 使用用户协议帧0xF1

    data_to_send[_cnt++] = 0x02; // 1个int16_t 长度 2个字节

    data_to_send[_cnt++] = BYTE0(data1);
    data_to_send[_cnt++] = BYTE1(data1);

    data_to_send_out[3] = _cnt - 4;

    for (i = 0; i < (data_to_send[3] + 4); i++) // 数据校验
    {

        sumcheck += data_to_send[i]; // 从帧头开始，对每一字节进行求和，直到DATA区结束
        addcheck += sumcheck;        // 每一字节的求和操作，进行一次sumcheck的累加
    };

    data_to_send[_cnt++] = sumcheck;
    data_to_send[_cnt++] = addcheck;
    ANO_DT_Send_Data(data_to_send, _cnt);
}
void ANO_DT_send_float(float data1)
{
    unsigned char _cnt = 0;
    unsigned char i = 0;
    unsigned char sumcheck = 0;
    unsigned char addcheck = 0;

    data_to_send[_cnt++] = 0xAA; // 匿名协议帧头  0xAA
    data_to_send[_cnt++] = 0xFF;
    data_to_send[_cnt++] = 0xF1; // 使用用户协议帧0xF1

    data_to_send[_cnt++] = 0x04; // 1个float 长度 4个字节

    data_to_send[_cnt++] = BYTE0(data1);
    data_to_send[_cnt++] = BYTE1(data1);
    data_to_send[_cnt++] = BYTE2(data1);
    data_to_send[_cnt++] = BYTE3(data1);

    data_to_send_out[3] = _cnt - 4;

    for (i = 0; i < (data_to_send[3] + 4); i++) // 数据校验
    {

        sumcheck += data_to_send[i]; // 从帧头开始，对每一字节进行求和，直到DATA区结束
        addcheck += sumcheck;        // 每一字节的求和操作，进行一次sumcheck的累加
    };

    data_to_send[_cnt++] = sumcheck;
    data_to_send[_cnt++] = addcheck;
    ANO_DT_Send_Data(data_to_send, _cnt);
}

void ANO_DT_send_int32(int32_t data1)
{
    unsigned char _cnt = 0;
    unsigned char i = 0;
    unsigned char sumcheck = 0;
    unsigned char addcheck = 0;

    data_to_send[_cnt++] = 0xAA; // 匿名协议帧头  0xAA
    data_to_send[_cnt++] = 0xFF;
    data_to_send[_cnt++] = 0xF1; // 使用用户协议帧0xF1

    data_to_send[_cnt++] = 0x04; // 1个int32_t 长度 4个字节

    data_to_send[_cnt++] = BYTE0(data1);
    data_to_send[_cnt++] = BYTE1(data1);
    data_to_send[_cnt++] = BYTE2(data1);
    data_to_send[_cnt++] = BYTE3(data1);

    data_to_send_out[3] = _cnt - 4;

    for (i = 0; i < (data_to_send[3] + 4); i++) // 数据校验
    {

        sumcheck += data_to_send[i]; // 从帧头开始，对每一字节进行求和，直到DATA区结束
        addcheck += sumcheck;        // 每一字节的求和操作，进行一次sumcheck的累加
    };

    data_to_send[_cnt++] = sumcheck;
    data_to_send[_cnt++] = addcheck;
    ANO_DT_Send_Data(data_to_send, _cnt);
}

void ANO_DT_send_vision(int16_t dx, int16_t dy, uint8_t detected)
{
    unsigned char _cnt = 0;
    unsigned char i = 0;
    unsigned char sumcheck = 0;
    unsigned char addcheck = 0;

    data_to_send[_cnt++] = 0xAA; // 匿名协议帧头  0xAA
    data_to_send[_cnt++] = 0xFF;
    data_to_send[_cnt++] = 0xF2; // 使用用户协议帧0xF2

    data_to_send[_cnt++] = 0x05; // 2个int16_t + 1个uint8_t 长度 5个字节

    data_to_send[_cnt++] = BYTE0(dx);
    data_to_send[_cnt++] = BYTE1(dx);

    data_to_send[_cnt++] = BYTE0(dy);
    data_to_send[_cnt++] = BYTE1(dy);

    data_to_send[_cnt++] = detected;

    data_to_send_out[3] = _cnt - 4;

    for (i = 0; i < (data_to_send[3] + 4); i++) // 数据校验
    {

        sumcheck += data_to_send[i]; // 从帧头开始，对每一字节进行求和，直到DATA区结束
        addcheck += sumcheck;        // 每一字节的求和操作，进行一次sumcheck的累加
    };

    data_to_send[_cnt++] = sumcheck;
    data_to_send[_cnt++] = addcheck;
    ANO_DT_Send_Data(data_to_send, _cnt);
}

void ANO_DT_send_encoder(uint16_t encoder_count)
{
    unsigned char _cnt = 0;
    unsigned char i = 0;
    unsigned char sumcheck = 0;
    unsigned char addcheck = 0;

    data_to_send[_cnt++] = 0xAA; // 匿名协议帧头  0xAA
    data_to_send[_cnt++] = 0xFF;
    data_to_send[_cnt++] = 0xF3; // 使用用户协议帧0xF3

    data_to_send[_cnt++] = 0x04; // 1个int32_t 长度 4个字节

    data_to_send[_cnt++] = BYTE0(encoder_count);
    data_to_send[_cnt++] = BYTE1(encoder_count);

    data_to_send_out[3] = _cnt - 4;

    for (i = 0; i < (data_to_send[3] + 4); i++) // 数据校验
    {

        sumcheck += data_to_send[i]; // 从帧头开始，对每一字节进行求和，直到DATA区结束
        addcheck += sumcheck;        // 每一字节的求和操作，进行一次sumcheck的累加
    };

    data_to_send[_cnt++] = sumcheck;
    data_to_send[_cnt++] = addcheck;
    ANO_DT_Send_Data(data_to_send, _cnt);
}

void ANO_DT_send_euler(float roll, float pitch, float yaw)
{
    unsigned char _cnt = 0;
    unsigned char i = 0;
    unsigned char sumcheck = 0;
    unsigned char addcheck = 0;

    data_to_send[_cnt++] = 0xAA; // 匿名协议帧头  0xAA
    data_to_send[_cnt++] = 0xFF;
    data_to_send[_cnt++] = 0xF4; // 使用用户协议帧0xF4

    data_to_send[_cnt++] = 0x0C; // 3个float 长度 12个字节

    data_to_send[_cnt++] = BYTE0(roll);
    data_to_send[_cnt++] = BYTE1(roll);
    data_to_send[_cnt++] = BYTE2(roll);
    data_to_send[_cnt++] = BYTE3(roll);

    data_to_send[_cnt++] = BYTE0(pitch);
    data_to_send[_cnt++] = BYTE1(pitch);
    data_to_send[_cnt++] = BYTE2(pitch);
    data_to_send[_cnt++] = BYTE3(pitch);

    data_to_send[_cnt++] = BYTE0(yaw);
    data_to_send[_cnt++] = BYTE1(yaw);
    data_to_send[_cnt++] = BYTE2(yaw);
    data_to_send[_cnt++] = BYTE3(yaw);

    data_to_send_out[3] = _cnt - 4;

    for (i = 0; i < (data_to_send[3] + 4); i++) // 数据校验
    {

        sumcheck += data_to_send[i]; // 从帧头开始，对每一字节进行求和，直到DATA区结束
        addcheck += sumcheck;        // 每一字节的求和操作，进行一次sumcheck的累加
    };

    data_to_send[_cnt++] = sumcheck;
    data_to_send[_cnt++] = addcheck;
    ANO_DT_Send_Data(data_to_send, _cnt);
}
void ANO_DT_send_gyro(float gyro_x, float gyro_y, float gyro_z)
{
    unsigned char _cnt = 0;
    unsigned char i = 0;
    unsigned char sumcheck = 0;
    unsigned char addcheck = 0;

    data_to_send[_cnt++] = 0xAA; // 匿名协议帧头  0xAA
    data_to_send[_cnt++] = 0xFF;
    data_to_send[_cnt++] = 0xF5; // 使用用户协议帧0xF5

    data_to_send[_cnt++] = 0x0C; // 3个float 长度 12个字节

    data_to_send[_cnt++] = BYTE0(gyro_x);
    data_to_send[_cnt++] = BYTE1(gyro_x);
    data_to_send[_cnt++] = BYTE2(gyro_x);
    data_to_send[_cnt++] = BYTE3(gyro_x);

    data_to_send[_cnt++] = BYTE0(gyro_y);
    data_to_send[_cnt++] = BYTE1(gyro_y);
    data_to_send[_cnt++] = BYTE2(gyro_y);
    data_to_send[_cnt++] = BYTE3(gyro_y);

    data_to_send[_cnt++] = BYTE0(gyro_z);
    data_to_send[_cnt++] = BYTE1(gyro_z);
    data_to_send[_cnt++] = BYTE2(gyro_z);
    data_to_send[_cnt++] = BYTE3(gyro_z);

    data_to_send_out[3] = _cnt - 4;

    for (i = 0; i < (data_to_send[3] + 4); i++) // 数据校验
    {

        sumcheck += data_to_send[i]; // 从帧头开始，对每一字节进行求和，直到DATA区结束
        addcheck += sumcheck;        // 每一字节的求和操作，进行一次sumcheck的累加
    };

    data_to_send[_cnt++] = sumcheck;
    data_to_send[_cnt++] = addcheck;
    ANO_DT_Send_Data(data_to_send, _cnt);
}
void ANO_DT_send_acc(float acc_x, float acc_y, float acc_z)
{
    unsigned char _cnt = 0;
    unsigned char i = 0;
    unsigned char sumcheck = 0;
    unsigned char addcheck = 0;

    data_to_send[_cnt++] = 0xAA; // 匿名协议帧头  0xAA
    data_to_send[_cnt++] = 0xFF;
    data_to_send[_cnt++] = 0xF6; // 使用用户协议帧0xF6

    data_to_send[_cnt++] = 0x0C; // 3个float 长度 12个字节

    data_to_send[_cnt++] = BYTE0(acc_x);
    data_to_send[_cnt++] = BYTE1(acc_x);
    data_to_send[_cnt++] = BYTE2(acc_x);
    data_to_send[_cnt++] = BYTE3(acc_x);

    data_to_send[_cnt++] = BYTE0(acc_y);
    data_to_send[_cnt++] = BYTE1(acc_y);
    data_to_send[_cnt++] = BYTE2(acc_y);
    data_to_send[_cnt++] = BYTE3(acc_y);

    data_to_send[_cnt++] = BYTE0(acc_z);
    data_to_send[_cnt++] = BYTE1(acc_z);
    data_to_send[_cnt++] = BYTE2(acc_z);
    data_to_send[_cnt++] = BYTE3(acc_z);

    data_to_send_out[3] = _cnt - 4;

    for (i = 0; i < (data_to_send[3] + 4); i++) // 数据校验
    {

        sumcheck += data_to_send[i]; // 从帧头开始，对每一字节进行求和，直到DATA区结束
        addcheck += sumcheck;        // 每一字节的求和操作，进行一次sumcheck的累加
    };

    data_to_send[_cnt++] = sumcheck;
    data_to_send[_cnt++] = addcheck;
    ANO_DT_Send_Data(data_to_send, _cnt);
}
