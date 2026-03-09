#include "map.h"
#include "constants.h"
#include <raylib.h>
#include <stdio.h>
#include <sys/types.h>

Color colors[] = {BLACK, WHITE, GREEN, RED};

typedef void (*CellOperation)(int map[GetMapHeight()][GetMapWidth()], int row,
                              int col);

void ForEachCell(int map[GetMapHeight()][GetMapWidth()], const CellOperation op) {
  struct MapData *md = GetMapData();

  if (md == NULL) {
    fprintf(stderr, "MapData not initialized. Run InitMapData first!");
    return;
  }

  for (int row = 0; row < GetMapHeight(); row++) {
    for (int col = 0; col < GetMapWidth(); col++) {
      op(map, row, col);
    }
  }
}

void InitCell(int map[GetMapHeight()][GetMapWidth()], const int row, const int col) {
  if (row == 0 || row == GetMapHeight() - 1 || col == 0 ||
      col == GetMapWidth() - 1) {
    map[row][col] = GetWallCell();
  } else {
    map[row][col] = GetEmptyCell();
  }
}

void DrawCell(int map[GetMapHeight()][GetMapWidth()], const int row, const int col) {
  Color cellColor = colors[map[row][col]];
  Vector4 cellColorVector = ColorNormalize(cellColor);
  Vector4 borderColorVector = {1.0 - cellColorVector.x, 1.0 - cellColorVector.y,
                               1.0 - cellColorVector.z, cellColorVector.w};

  Color borderColor = ColorFromNormalized(borderColorVector);

  DrawRectangle(col * GetCellSize(), row * GetCellSize(), GetCellSize(),
                GetCellSize(), cellColor);
  DrawRectangleLines(col * GetCellSize(), row * GetCellSize(), GetCellSize(),
                     GetCellSize(), borderColor);
}

void FillWallCells(int map[GetMapHeight()][GetMapWidth()], const int row, const int col) {
  if (map[row][col] != GetFloorCell())
    return;

  if (map[row - 1][col] == GetEmptyCell())
    map[row - 1][col] = GetWallCell();

  if (map[row + 1][col] == GetEmptyCell())
    map[row + 1][col] = GetWallCell();

  if (map[row][col - 1] == GetEmptyCell())
    map[row][col - 1] = GetWallCell();

  if (map[row][col + 1] == GetEmptyCell())
    map[row][col + 1] = GetWallCell();
}

void InitMap(int map[GetMapHeight()][GetMapWidth()]) {
  ForEachCell(map, InitCell);
}

void DrawMap2D(int map[GetMapHeight()][GetMapWidth()]) {
  ForEachCell(map, DrawCell);
}

void FillWalls(int map[GetMapHeight()][GetMapWidth()]) {
  ForEachCell(map, FillWallCells);
}
