#include "constants.h"
#include "global_imports.h"
#include "map.h"
#include "player.h"
#include "room.h"
#include <raylib.h>

int map[WINDOW_HEIGHT / CELL_SIZE][WINDOW_WIDTH / CELL_SIZE];
struct Room rooms[NUM_ROOMS];
struct Player p;

void Initialize() {
  InitMap(map);
  InitRooms(rooms);

  for (int i = 0; i < NUM_ROOMS; i++) {
    AddRoomToMap(&rooms[i], map);
  }

  ConnectRooms(rooms, map);
  FillWalls(map);

  struct Room startRoom = rooms[0];
  float roomCenterX = (startRoom.x + startRoom.width / 2) * CELL_SIZE;
  float roomCenterY = (startRoom.y + startRoom.height / 2) * CELL_SIZE;

  InitPlayer(&p, roomCenterX, roomCenterY, 100);
}

void Update() {
  float delta = GetFrameTime();
  if (IsKeyDown(KEY_W))
    MovePlayer(&p, DIR_UP, 0, delta);
  if (IsKeyDown(KEY_S))
    MovePlayer(&p, DIR_DOWN, 0, delta);
  if (IsKeyDown(KEY_A))
    MovePlayer(&p, 0, DIR_LEFT, delta);
  if (IsKeyDown(KEY_D))
    MovePlayer(&p, 0, DIR_RIGHT, delta);
  if (IsKeyDown(KEY_LEFT))
    TurnPlayer(&p, ROTATE_LEFT, delta);
  if (IsKeyDown(KEY_RIGHT))
    TurnPlayer(&p, ROTATE_RIGHT, delta);
}

void Draw() {
  BeginDrawing();
  {
    ClearBackground(BLACK);
    DrawMap2D(map);
    DrawPlayer2D(&p);
  }
  EndDrawing();
}

int main(void) {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);
  SetTargetFPS(FPS);
  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  ToggleFullscreen();

  Initialize();

  while (!WindowShouldClose()) {
    Update();
    Draw();
  }

  CloseWindow();

  return 0;
}
