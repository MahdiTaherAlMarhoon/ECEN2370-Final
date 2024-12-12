/*
 * Tetris_Game.c
 *
 *  Created on: Dec 5, 2024
 *      Author: mahdialmarhoon
 */

#include "Tetris_Game.h"
#include "string.h"

uint32_t TetrisNewBoard[30][20] ={0};
uint32_t TetrisTemporaryBoard[30][20] ={0};
uint8_t row = 4;
uint8_t column = 0;
uint8_t angle = 0;
uint32_t CurrentShape[4][4];
uint32_t RandomShape;

uint32_t c[30][20] = {0};
uint32_t f[4][4] = {0};

void Add_Shape(uint32_t TetrisBoard[30][20]) {
    for (uint8_t y = 0; y < 4; y++) {
        for (uint8_t x = 0; x < 4; x++)
        {
            if (CurrentShape[y][x] == 1)
            {
                uint8_t pos1 = row + x;
                uint8_t pos2 = column + y;
                if (pos1 < 20)
                	if(pos2 < 30) {
                	TetrisBoard[pos2][pos1] = 1;
                }
            }
        }
    }
}

void Make_Shape(){
	RandomShape = Number_Generator();
    memcpy(CurrentShape, TetrisBlocks[RandomShape][0], sizeof(CurrentShape));
}

void Rotate_Shape(){
	uint8_t previousRot = angle;
	angle +=1;
	if (angle >= 4) {
	        angle = 0;
	}

	memcpy(CurrentShape, c, sizeof(c));
	memcpy(CurrentShape, TetrisBlocks[RandomShape][angle], sizeof(CurrentShape));
	bool collision = Shape_Collide();
	if (!collision){
		memcpy(TetrisTemporaryBoard, TetrisNewBoard, sizeof(TetrisNewBoard));
		Add_Shape(TetrisTemporaryBoard);
		LCD_AddBlock_To_Screen(TetrisNewBoard);
		LCD_AddBlock_To_Screen(TetrisTemporaryBoard);
	} else {
		angle = previousRot;
		memcpy(CurrentShape, f, sizeof(CurrentShape));
		memcpy(CurrentShape, TetrisBlocks[RandomShape][angle], sizeof(CurrentShape));
	}
}

void Shape_Down(){
	uint8_t previousY = column;
	column +=1;
	bool collision = Shape_Collide();

	if (!collision){
		Add_Shape(TetrisTemporaryBoard);
	} else {
		column = previousY;
		Add_Shape(TetrisNewBoard);
	}
}

bool Shape_Collide(){
	for (uint8_t i = 0; i < 4; i++) {
		for (uint8_t j = 0; j < 4; j++) {
			if (CurrentShape[i][j]) {
				uint8_t pos1 = row + j;
				uint8_t pos2 = column + i;
				if (pos1 >= 20 || pos2 >= 30)
				{
					return 1;
				}
			}
		}
	}
    return 0;
}


void Play_Game(){
	uint32_t start = 0;
	uint32_t end = 0;
	uint32_t overall = 0;

    start = HAL_GetTick();
    Make_Shape();
    Add_Shape(TetrisTemporaryBoard);
    LCD_AddBlock_To_Screen(TetrisTemporaryBoard);
    HAL_Delay(100);
    while (true)
    {
    	if (Shape_Collide()) {
    		Add_Shape(TetrisNewBoard);
			memcpy(TetrisTemporaryBoard, TetrisNewBoard, sizeof(TetrisNewBoard));
			column = 0;
			angle = 0;
			Make_Shape();
			if (Shape_Collide())
			{
				Add_Shape(TetrisNewBoard);
				LCD_AddBlock_To_Screen(TetrisNewBoard);
				break;
			} else
			{
				Add_Shape(TetrisTemporaryBoard);
				LCD_AddBlock_To_Screen(TetrisTemporaryBoard);
			}
		}else
		{
			memcpy(TetrisTemporaryBoard, TetrisNewBoard, sizeof(TetrisNewBoard));
			Shape_Down();
			bool colide = Shape_Collide();
			if (!colide)
			{
				LCD_AddBlock_To_Screen(TetrisTemporaryBoard);
			}
		}
		HAL_Delay(100);
    }
    end = HAL_GetTick();
    overall = end-start;
    LCD_end(overall);
}


