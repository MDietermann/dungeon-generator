#include "map.h"
#include "constants.h"
#include <raylib.h>
#include <sys/types.h>

Color colors[] = {BLACK, WHITE, GREEN, RED};

void InitMap(int map[WINDOW_HEIGHT / CELL_SIZE][WINDOW_WIDTH / CELL_SIZE]) {
  for (int row = 0; row < WINDOW_HEIGHT / CELL_SIZE; row++) {
    for (int col = 0; col < WINDOW_WIDTH / CELL_SIZE; col++) {
      if (row == 0 || row == WINDOW_HEIGHT / CELL_SIZE - 1 || col == 0 ||
          col == WINDOW_WIDTH / CELL_SIZE - 1) {
        map[row][col] = WALL;
        continue;
      }
      map[row][col] = EMPTY;
    }
  }
}

void DrawMap2D(int map[WINDOW_HEIGHT / CELL_SIZE][WINDOW_WIDTH / CELL_SIZE]) {
  for (int row = 0; row < WINDOW_HEIGHT / CELL_SIZE; row++) {
    for (int col = 0; col < WINDOW_WIDTH / CELL_SIZE; col++) {
      Color cellColor = colors[map[row][col]];
      Vector4 cellColorVector = ColorNormalize(cellColor);
      Vector4 borderColorVector = {1.0 - cellColorVector.x,
                                   1.0 - cellColorVector.y,
                                   1.0 - cellColorVector.y, cellColorVector.w};

      Color borderColor = ColorFromNormalized(borderColorVector);

      DrawRectangle(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE,
                    cellColor);
      DrawRectangleLines(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE,
                         borderColor);
    }
  }
}

void FillWalls(int map[WINDOW_HEIGHT / CELL_SIZE][WINDOW_WIDTH / CELL_SIZE]) {
  for (int row = 1; row < WINDOW_HEIGHT / CELL_SIZE - 1; row++) {
    for (int col = 1; col < WINDOW_WIDTH / CELL_SIZE - 1; col++) {
      if (map[row][col] != FLOOR)
        continue;

      if (map[row - 1][col] == EMPTY)
        map[row - 1][col] = WALL;

      if (map[row + 1][col] == EMPTY)
        map[row + 1][col] = WALL;

      if (map[row][col - 1] == EMPTY)
        map[row][col - 1] = WALL;

      if (map[row][col + 1] == EMPTY)
        map[row][col + 1] = WALL;
    }
  }
}
