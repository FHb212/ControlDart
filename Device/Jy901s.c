#include "main.h"
#include "usart.h"
#include <string.h>
#include "jy901sHal.h"
#include "jy901s.h"
#include <stdio.h>
#include "Vision.h"
extern uint8_t uart6_dma_rx_buf[4]; // 如果大小不是4，请按实际修改
volatile char s_cDataUpdate = 0, s_cCmd = 0xff;
uint8_t rData1[4];
uint8_t rData2[1];

void SensorUartSend(unsigned char *p_data, unsigned int uiSize)
{
    HAL_UART_Transmit_IT(&huart1, p_data, uiSize);
}

// void CopeCmdData(unsigned char ucData)
//{
//	static unsigned char s_ucData[50], s_ucRxCnt = 0;
//
//	s_ucData[s_ucRxCnt++] = ucData;
//	if(s_ucRxCnt<3)return;										//Less than three data returned
//	if(s_ucRxCnt >= 50) s_ucRxCnt = 0;
//	if(s_ucRxCnt >= 3)
//	{
//		if((s_ucData[1] == '\r') && (s_ucData[2] == '\n'))
//		{
//			s_cCmd = s_ucData[0];
//			memset(s_ucData,0,50);//
//			s_ucRxCnt = 0;
//		}
//		else
//		{
//			s_ucData[0] = s_ucData[1];
//			s_ucData[1] = s_ucData[2];
//			s_ucRxCnt = 2;
//
//		}
//	}

//}

void CopeCmdData(char *ucData) // 用于处理调试命令的函数，这个函数我自己重写了一遍，因为原本的协议老是出问题...
{

    if (strcmp(ucData + 1, "lim") == 0)
    {
        s_cCmd = ucData[0];
    }
    // else
    // {
    //     printf("Command error! Your command is: %s\n", ucData);
    // }
}

void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum) // 数据更新函数
{
    int i;
    for (i = 0; i < uiRegNum; i++)
    {
        switch (uiReg)
        {
            //            case AX:
            //            case AY:
        case AZ:
            s_cDataUpdate |= ACC_UPDATE;
            break;
            //            case GX:
            //            case GY:
        case GZ:
            s_cDataUpdate |= GYRO_UPDATE;
            break;
            //            case HX:
            //            case HY:
        case HZ:
            s_cDataUpdate |= MAG_UPDATE;
            break;
            //            case Roll:
            //            case Pitch:
        case Yaw:
            s_cDataUpdate |= ANGLE_UPDATE;
            break;
        default:
            s_cDataUpdate |= READ_UPDATE;
            break;
        }
        uiReg++;
    }
}

// void ShowHelp(void) // 字面意思，显示帮助信息
// {
//     printf("\r\n************************	 WIT_SDK_DEMO	************************");
//     printf("\r\n************************          HELP           ************************\r\n");
//     printf("UART SEND:alim   Acceleration calibration.\r\n");
//     printf("UART SEND:mlim   Magnetic field calibration,After calibration send:   elim   to indicate the end\r\n");
//     printf("UART SEND:Ulim   Bandwidth increase.\r\n");
//     printf("UART SEND:ulim   Bandwidth reduction.\r\n");
//     printf("UART SEND:Blim   Baud rate increased to 115200.\r\n");
//     printf("UART SEND:blim   Baud rate reduction to 9600.\r\n");
//     printf("UART SEND:Rlim   The return rate increases to 10Hz.\r\n");
//     printf("UART SEND:rlim   The return rate reduction to 1Hz.\r\n");
//     printf("UART SEND:Clim   Basic return content: acceleration, angular velocity, angle, magnetic field.\r\n");
//     printf("UART SEND:clim   Return content: acceleration.\r\n");
//     printf("UART SEND:hlim   help.\r\n");
//     printf("******************************************************************************\r\n");
// }

void CmdProcess(void) // 通过串口操作jy901s的参数
{
    switch (s_cCmd)
    {
    case 'a':
        if (WitStartAccCali() != WIT_HAL_OK)
            printf("\r\nSet AccCali Error\r\n");
        break;
    case 'm':
        if (WitStartMagCali() != WIT_HAL_OK)
            printf("\r\nSet MagCali Error\r\n");
        break;
    case 'e':
        if (WitStopMagCali() != WIT_HAL_OK)
            printf("\r\nSet MagCali Error\r\n");
        break;
    case 'u':
        if (WitSetBandwidth(BANDWIDTH_5HZ) != WIT_HAL_OK)
            printf("\r\nSet Bandwidth Error\r\n");
        break;
    case 'U':
        if (WitSetBandwidth(BANDWIDTH_256HZ) != WIT_HAL_OK)
            printf("\r\nSet Bandwidth Error\r\n");
        break;
    case 'B':
        if (WitSetUartBaud(WIT_BAUD_115200) != WIT_HAL_OK)
            printf("\r\nSet Baud Error\r\n");
        //			else
        //				Usart2Init(c_uiBaud[WIT_BAUD_115200]);
        else
        {
            printf("\r\nWit Baud set, please change baud rate of you uart.r\r\n");
        }
        break;
    case 'b':
        if (WitSetUartBaud(WIT_BAUD_9600) != WIT_HAL_OK)
            printf("\r\nSet Baud Error\r\n");
        //			else
        //				Usart2Init(c_uiBaud[WIT_BAUD_9600]);
        else
        {
            printf("\r\nWit Baud set, please change baud rate of you uart.r\r\n");
        }
        break;
    case 'R':
        if (WitSetOutputRate(RRATE_10HZ) != WIT_HAL_OK)
            printf("\r\nSet Rate Error\r\n");
        break;
    case 'r':
        if (WitSetOutputRate(RRATE_1HZ) != WIT_HAL_OK)
            printf("\r\nSet Rate Error\r\n");
        break;
    case 'C':
        if (WitSetContent(RSW_ACC | RSW_GYRO | RSW_ANGLE | RSW_MAG) != WIT_HAL_OK)
            printf("\r\nSet RSW Error\r\n");
        break;
    case 'c':
        if (WitSetContent(RSW_ACC) != WIT_HAL_OK)
            printf("\r\nSet RSW Error\r\n");
        break;
    case 'h':
        // ShowHelp();
        break;
    }
    s_cCmd = 0xff;
}

void Delayms(uint16_t ucMs) // sdk要用到这么一个函数，我懒得去改sdk了，就重新封装了一个（
{
    HAL_Delay(ucMs);
}

void JY901S_Init()
{
    WitInit(WIT_PROTOCOL_NORMAL, 0x50);
    WitSerialWriteRegister(SensorUartSend);
    // printf("return = %d\n", WitRegisterCallBack(SensorDataUpdata));
    WitRegisterCallBack(SensorDataUpdata);
    WitDelayMsRegister(Delayms);

    HAL_UART_Receive_IT(&huart2, rData1, 4);
    HAL_UART_Receive_IT(&huart1, rData2, 1);
}

void JY901S_Get_Data(JY901S_data *data)
{
    uint8_t i = 0;

    if (s_cDataUpdate) // 一下是获取陀螺仪数据的代码，可以单独封装
    {
        if (s_cDataUpdate & ACC_UPDATE)
        {
            for (i = 0; i < 3; i++)
            {
                data->fAcc[i] = sReg[AX + i] / 32768.0f * 16.0f;
            }
            s_cDataUpdate &= ~ACC_UPDATE;
        }
        if (s_cDataUpdate & GYRO_UPDATE)
        {
            for (i = 0; i < 3; i++)
            {
                data->fGyro[i] = sReg[GX + i] / 32768.0f * 2000.0f;
            }
            s_cDataUpdate &= ~GYRO_UPDATE;
        }
        if (s_cDataUpdate & ANGLE_UPDATE)
        {
            for (i = 0; i < 3; i++)
            {
                data->fAngle[i] = sReg[Roll + i] / 32768.0f * 180.0f;
            }
            s_cDataUpdate &= ~ANGLE_UPDATE;
        }
        if (s_cDataUpdate & MAG_UPDATE)
        {
            for (i = 0; i < 3; i++)
            {
                data->fMag[i] = sReg[HX + i];
            }
            s_cDataUpdate &= ~MAG_UPDATE;
        }
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) // 中断函数
{
    uint8_t temp2;
    char temp1[5];
    uint8_t i = 0;
    // if (huart == &huart2)
    // {
    //     for (i = 0; i < 4; i++)
    //     {
    //         temp1[i] = rData1[i];
    //     }
    //     temp1[4] = '\0';
    //     CopeCmdData(temp1);
    //     HAL_UART_Receive_IT(&huart2, rData1, 4);
    // }
    if (huart == &huart1)
    {
        temp2 = rData2[0];
        WitSerialDataIn(temp2);
        HAL_UART_Receive_IT(&huart1, rData2, 1);
    }
    else if (huart == &huart6)
    {
        Vision_Uart6_DataHandler(uart6_dma_rx_buf);
    }
}