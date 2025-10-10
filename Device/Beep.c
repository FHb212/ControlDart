#include "Beep.h"
#include "main.h"          // Include the GPIO header for hardware control
#include "stm32f4xx_hal.h" // Include HAL for GPIO functions
#include "gpio.h"          // Include the GPIO header for pin definitions
void Beep_Init(void)
{
}

void Beep_On(void)
{
    // Turn on the beep
    // This function should set the GPIO pin high to activate the beep
    HAL_GPIO_WritePin(BEEP_Control_GPIO_Port, BEEP_Control_Pin, GPIO_PIN_RESET);
}

void Beep_Off(void)
{
    // Turn off the beep
    // This function should set the GPIO pin low to deactivate the beep
    HAL_GPIO_WritePin(BEEP_Control_GPIO_Port, BEEP_Control_Pin, GPIO_PIN_SET);
}