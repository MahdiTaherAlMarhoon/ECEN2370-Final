/*
 * Button_Driver.c
 *
 *  Created on: Sep 26, 2024
 *      Author: mahdialmarhoon
 */


#include "Button_Driver.h"

void Button_EnableClock(void) {
	__HAL_RCC_GPIOA_CLK_ENABLE();
}

void Button_Init(void) {
	GPIO_InitTypeDef ButtonHandle;

    Button_EnableClock();

    ButtonHandle.Speed = GPIO_SPEED_FREQ_HIGH;
    ButtonHandle.Mode = GPIO_MODE_INPUT;
    ButtonHandle.Pin = BUTTON_PIN_NUMBER;
    ButtonHandle.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(GPIOA, &ButtonHandle);
}

void Button_InterruptInit(void) {
	GPIO_InitTypeDef ButtonHandle;

    Button_EnableClock();

	ButtonHandle.Speed = GPIO_SPEED_FREQ_HIGH;
	ButtonHandle.Mode = GPIO_MODE_IT_FALLING;
	ButtonHandle.Pin = BUTTON_PIN_NUMBER;
	ButtonHandle.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(GPIOA, &ButtonHandle);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

bool Button_IsPressed(void) {
    if (HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN_NUMBER) == BUTTON_PRESSED) {
        return true;
    } else {
        return false;
    }
}
