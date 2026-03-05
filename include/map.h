#ifndef MAP_H
#define MAP_H

#include "constants.h"
#include "global_imports.h"

void InitMap(int map[WINDOW_HEIGHT / CELL_SIZE][WINDOW_WIDTH / CELL_SIZE]);
void DrawMap2D(int map[WINDOW_HEIGHT / CELL_SIZE][WINDOW_WIDTH / CELL_SIZE]);
void FillWalls(int map[WINDOW_HEIGHT / CELL_SIZE][WINDOW_WIDTH / CELL_SIZE]);

#endif // !MAP_H
