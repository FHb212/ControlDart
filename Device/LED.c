#include "LED.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include "gpio.h"

void LED_Init(void)
{
    // Initialize the LED hardware
    // This function should set up the GPIO pin connected to the LED
}

void LED_On(void)
{
    // Turn on the LED
    // This function should set the GPIO pin high to activate the LED
    HAL_GPIO_WritePin(LED_Control_GPIO_Port, LED_Control_Pin, GPIO_PIN_RESET);
}

void LED_Off(void)
{
    // Turn off the LED
    // This function should set the GPIO pin low to deactivate the LED
    HAL_GPIO_WritePin(LED_Control_GPIO_Port, LED_Control_Pin, GPIO_PIN_SET);
}