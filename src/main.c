#include "constants.h"
#include "global_imports.h"
#include "map.h"
#include "room.h"
#include <raylib.h>

int map[WINDOW_HEIGHT / CELL_SIZE][WINDOW_WIDTH / CELL_SIZE];
struct Room rooms[NUM_ROOMS];

void Initialize() {
  InitMap(map);
  InitRooms(rooms);
}

int main(void) {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);
  SetTargetFPS(FPS);
  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  ToggleFullscreen();

  InitMap(map);
  InitRooms(rooms);

  for (int i = 0; i < NUM_ROOMS; i++) {
    AddRoomToMap(&rooms[i], map);
  }

  int roomsSize = sizeof(rooms) / sizeof(rooms[0]);
  ConnectRooms(rooms, map);
  FillWalls(map);

  while (!WindowShouldClose()) {
    BeginDrawing();
    {
      ClearBackground(BLACK);
      DrawMap2D(map);
    }
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
