/*
 * Time.c
 *
 *  Created on: Dec 5, 2024
 *      Author: mahdialmarhoon
 */

#include "Time.h"

uint32_t GetElapsedTime(uint32_t start, uint32_t end)
{
	uint32_t milliseconds = end-start;
	uint32_t seconds = milliseconds/1000;
	return seconds;
}



