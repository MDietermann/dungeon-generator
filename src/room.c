#include "room.h"
#include "constants.h"
#include "global_imports.h"
#include "helper.h"
#include <limits.h>
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void InitRooms(struct Room *rooms) {
  int roomRetries = 20;
  srand(time(NULL));
  for (int i = 0; i < NUM_ROOMS; i++) {
    int retryCounter = 0;
    struct Room newRoom;
    while (retryCounter < roomRetries) {
      newRoom.width = (rand() % MAX_ROOM_SIZE) + MIN_ROOM_SIZE;
      newRoom.height = (rand() % MAX_ROOM_SIZE) + MIN_ROOM_SIZE;
      newRoom.connected = 0;
      newRoom.valid = 0;
      newRoom.x =
          (rand() % ((WINDOW_WIDTH / CELL_SIZE - newRoom.width) - 2)) + 2;
      newRoom.y =
          (rand() % ((WINDOW_HEIGHT / CELL_SIZE - newRoom.height) - 2)) + 2;

      if (RoomNotOverlapping(&newRoom, rooms)) {
        newRoom.valid = 1;
        rooms[i] = newRoom;
        break;
      }

      retryCounter++;
    }
  }
}

int DoOverlap(struct Room *r1, struct Room *r2) {
  int r1x1 = r1->x - ROOM_SPACING;
  int r1x2 = r1->x + r1->width + ROOM_SPACING;
  int r1y1 = r1->y - ROOM_SPACING;
  int r1y2 = r1->y + r1->height + ROOM_SPACING;

  int r2x1 = r2->x;
  int r2x2 = r2->x + r2->width;
  int r2y1 = r2->y;
  int r2y2 = r2->y + r2->height;

  if (r1x1 >= r2x2 || r2x1 >= r1x2)
    return 0;

  if (r1y1 >= r2y2 || r2y1 >= r1y2)
    return 0;

  return 1;
}

int RoomNotOverlapping(struct Room *r1, struct Room *rooms) {
  for (int i = 0; i < NUM_ROOMS; i++) {
    if (DoOverlap(r1, &rooms[i])) {
      return 0;
    }
  }

  return 1;
}

void AddRoomToMap(
    struct Room *room,
    int map[WINDOW_HEIGHT / CELL_SIZE][WINDOW_WIDTH / CELL_SIZE]) {

  int roomTop = room->y;
  int roomBottom = room->y + room->height;
  int roomLeft = room->x;
  int roomRight = room->x + room->width;

  for (int row = roomTop; row < roomBottom; row++) {
    for (int col = roomLeft; col < roomRight; col++) {
      if (row == roomTop || row == roomBottom - 1 || col == roomLeft ||
          col == roomRight - 1) {
        map[row][col] = 1;
        continue;
      }
      map[row][col] = 2;
    }
  }
}

Vector2 RoomCenter(struct Room *r) {
  fprintf(stderr, "X: %d | Y: %d | W: %d | H: %d\n", r->x, r->y, r->width,
          r->height);
  Vector2 center = {r->x + floor(r->width / 2), r->y + floor(r->height / 2)};

  return center;
}

void DebugConnectRooms(
    struct Room *r1, struct Room *r2,
    int map[WINDOW_HEIGHT / CELL_SIZE][WINDOW_WIDTH / CELL_SIZE]) {
  Vector2 r1Center = RoomCenter(r1);
  Vector2 r2Center = RoomCenter(r2);

  Vector2 r1CenterGlobal = LocalToGlobalCoords(r1Center);
  Vector2 r2CenterGlobal = LocalToGlobalCoords(r2Center);
  DrawLineEx(r1CenterGlobal, r2CenterGlobal, 2, RED);

  int sx;
  int ex;
  if (r1Center.x < r2Center.x) {
    sx = r1Center.x;
    ex = r2Center.x;
  } else {
    sx = r2Center.x;
    ex = r1Center.x;
  }

  while (sx < ex) {
    int sy = GetYfromX(r1Center, r2Center, sx);
    fprintf(stderr, "R1Center: (%d, %d) | R2Center: (%d, %d) | X: %d | Y: %d\n",
            r1Center.x, r1Center.y, r2Center.x, r2Center.y, sx, sy);
    map[sy][sx] = 2;

    sx++;
  }
}

void ConnectRooms(
    struct Room *rooms,
    int map[WINDOW_HEIGHT / CELL_SIZE][WINDOW_WIDTH / CELL_SIZE]) {

  struct Room *currentRoom = &rooms[0];

  for (int i = 0; i < NUM_ROOMS; i++) {
    if (!rooms[i].valid)
      continue;

    struct Room *closestRoom = GetClosestRoomCenter(currentRoom, rooms);
    if (closestRoom == NULL)
      break;
    AddCorridor(currentRoom, closestRoom, map);
    currentRoom = closestRoom;
  }

  return;
}

void AddCorridor(struct Room *r1, struct Room *r2,
                 int map[WINDOW_HEIGHT / CELL_SIZE][WINDOW_WIDTH / CELL_SIZE]) {
  Vector2 sRoom = RoomCenter(r1);
  Vector2 eRoom = RoomCenter(r2);

  int sx, ex;
  int sy, ey;

  if (sRoom.x < eRoom.x) {
    sx = sRoom.x;
    ex = eRoom.x;
  } else {
    sx = eRoom.x;
    ex = sRoom.x;
  }

  if (sRoom.y < eRoom.y) {
    sy = sRoom.y;
    ey = eRoom.y;
  } else {
    sy = eRoom.y;
    ey = sRoom.y;
  }

  for (int y = sy; y < ey; y++) {
    map[y][sx] = FLOOR;
  }

  for (int x = sx; x < ex; x++) {
    map[sy][x] = FLOOR;
  }

  r1->connected = 1;
}

struct Room *GetClosestRoomCenter(struct Room *currentRoom,
                                  struct Room *rooms) {
  int closest = INT_MAX;
  struct Room *closestRoom = NULL;

  for (int i = 0; i < NUM_ROOMS; i++) {
    if (!rooms[i].valid)
      continue;

    if (rooms[i].connected)
      continue;

    if (currentRoom->x == rooms[i].x && currentRoom->y == rooms[i].y)
      continue;

    Vector2 p1 = {currentRoom->x, currentRoom->y};
    Vector2 p2 = {rooms[i].x, rooms[i].y};
    int distSq = GetDistance(&p1, &p2);

    if (distSq < closest) {
      closest = distSq;
      closestRoom = &rooms[i];
    }
  }

  return closestRoom;
}
