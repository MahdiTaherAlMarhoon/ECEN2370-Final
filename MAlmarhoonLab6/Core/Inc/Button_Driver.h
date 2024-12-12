/*
 * Button_Driver.h
 *
 *  Created on: Sep 26, 2024
 *      Author: mahdialmarhoon
 */

#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_

#include <stdbool.h>
#include "stm32f4xx_hal.h"

#define BUTTON_PORT             GPIOA
#define BUTTON_PIN_NUMBER       GPIO_PIN_0
#define BUTTON_PRESSED          1       // Active low or high
#define BUTTON_NOT_PRESSED      0

void Button_Init();
void Button_EnableClock();
bool Button_IsPressed();
void Button_InterruptInit();

#endif /* BUTTON_DRIVER_H_ */
