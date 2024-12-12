/*
 * hrngom.c
 *
 *  Created on: Dec 5, 2024
 *      Author: mahdialmarhoon
 */

#include "random.h"

RNG_HandleTypeDef hrng;
uint32_t Number_Generator(){

	uint32_t value = 0;
    HAL_RNG_GenerateRandomNumber(&hrng, &value);
    uint32_t num_seven = value%7;

    return num_seven;
}

void initRandom()
{

    __HAL_RCC_RNG_CLK_ENABLE();
    hrng.Instance = RNG;
    HAL_RNG_Init(&hrng);
}
