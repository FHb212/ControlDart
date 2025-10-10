#include "ANOBsp.h"
// 数据拆分宏定义，在发送大于1字节的数据类型时，比如int16、float等，需要把数据拆分成单独字节进行发送
#define BYTE0(dwTemp) (*((char *)(&dwTemp)))     /*!< uint32_t 数据拆分 byte0  */
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1)) /*!< uint32_t 数据拆分 byte1  */
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2)) /*!< uint32_t 数据拆分 byte2  */
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3)) /*!< uint32_t 数据拆分 byte3  */
/**  发送数据缓存 */
unsigned char data_to_send[50]; // 用于绘图

unsigned char data_to_send_out[50]; // 用于传输

unsigned char data_to_get[50]; // 接收数据缓存

// 上面三个数组只是我个人定义的可根据自己需求进行修改

extern UART_HandleTypeDef huart2; // 外部申明 此处需要根据开启的串口进行修改
/*!
 * @brief    Send_Data函数是协议中所有发送数据功能使用到的发送函数
 *
 * @param    dataToSend   :   要发送的数据首地址
 * @param    length       :   要发送的数据长度
 *
 * @return   无
 *
 * @note     移植时，用户应根据自身应用的情况，根据使用的通信方式，实现此函数
 *
 * @see      内部调用
 *
 * @date     2021/5/28 星期二
 */
void ANO_DT_Send_Data(unsigned char *dataToSend, unsigned short length)
{

    /**使用串口正常发送数据，大概需要1.5ms*/
    // UART_PutBuff(UART0, dataToSend, length);     //可以修改不同的串口发送数据
    HAL_UART_Transmit(&huart2, (uint8_t *)dataToSend, length, 0xFFFF); //(uint8_t*)aRxBuffer为字符串地址，length为字符串长度，0xFFFF为超时时间 （需要根据开启的串口进行修改）
}
/*!
 * @brief    向上位机发送发送1个int16_t数据
 *
 * @param    data1： 发送给上位机显示波形 (可以自己加)
 *
 * @return   无
 *
 * @note     无
 *
 * @see      ANO_DT_send_int16 ( 1 );
 *
 * @date     2021/5/28 星期二
 */
void ANO_DT_send_int16(short data1)
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
