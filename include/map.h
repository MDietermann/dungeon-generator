#ifndef MAP_H
#define MAP_H

#include "constants.h"
#include "global_imports.h"

void InitMap(int map[GetMapHeight()][GetMapWidth()]);
void DrawMap2D(int map[GetMapHeight()][GetMapWidth()]);
void FillWalls(int map[GetMapHeight()][GetMapWidth()]);

#endif // !MAP_H
