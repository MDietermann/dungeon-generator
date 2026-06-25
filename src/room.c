#include "room.h"
#include "constants.h"
#include "global_imports.h"
#include "helper.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef void (*RoomOperation)(struct Room *rooms, int roomId);

void ForEachRoom(struct Room *rooms, const RoomOperation op) {
  const struct RoomData *rd = GetRoomData();
  const struct MapData *md = GetMapData();

  if (rd == NULL) {
    fprintf(stderr, "RoomData not initialized. Runn InitRoomData first!\n");
    return;
  }

  if (md == NULL) {
    fprintf(stderr, "MapData not initialized. Run InitMapData first!");
    return;
  }

  for (int roomId = 0; roomId < GetNumberOfRooms(); roomId++) {
    op(rooms, roomId);
  }
}

void CreateRoom(struct Room *rooms, const int roomId) {
  int retryCounter = 0;
  struct Room newRoom;

  while (retryCounter < GetRoomMaxIterationRetries()) {
    newRoom.width = (rand() % GetMaxRoomSize()) + GetMinRoomSize();
    newRoom.height = (rand() % GetMaxRoomSize()) + GetMinRoomSize();
    newRoom.connected = 0;
    newRoom.valid = 0;
    newRoom.x = (rand() % ((GetMapWidth() - newRoom.width) - 2)) + 2;
    newRoom.y = (rand() % ((GetMapHeight() - newRoom.height) - 2)) + 2;

    if (RoomNotOverlapping(&newRoom, rooms)) {
      newRoom.valid = 1;
      rooms[roomId] = newRoom;
      break;
    }

    retryCounter++;
  }
}

int DoOverlap(const struct Room *r1, const struct Room *r2) {
  const int r1x1 = r1->x - GetRoomSpacing();
  const int r1x2 = r1->x + r1->width + GetRoomSpacing();
  const int r1y1 = r1->y - GetRoomSpacing();
  const int r1y2 = r1->y + r1->height + GetRoomSpacing();

  const int r2x1 = r2->x;
  const int r2x2 = r2->x + r2->width;
  const int r2y1 = r2->y;
  const int r2y2 = r2->y + r2->height;

  if (r1x1 >= r2x2 || r2x1 >= r1x2)
    return 0;

  if (r1y1 >= r2y2 || r2y1 >= r1y2)
    return 0;

  return 1;
}

void InitRooms(struct Room *rooms) {
  srand(time(NULL));
  ForEachRoom(rooms, CreateRoom);
}

int RoomNotOverlapping(struct Room *r1, struct Room *rooms) {
  for (int i = 0; i < GetNumberOfRooms(); i++) {
    if (DoOverlap(r1, &rooms[i])) {
      return 0;
    }
  }

  return 1;
}

void AddRoomToMap(const struct Room *room, int map[GetMapHeight()][GetMapWidth()]) {

  const int roomTop = room->y;
  const int roomBottom = room->y + room->height;
  const int roomLeft = room->x;
  const int roomRight = room->x + room->width;

  for (int row = roomTop; row < roomBottom; row++) {
    for (int col = roomLeft; col < roomRight; col++) {
      if (row == roomTop || row == roomBottom - 1 || col == roomLeft ||
          col == roomRight - 1) {
        map[row][col] = GetWallCell();
        continue;
      }
      map[row][col] = GetFloorCell();
    }
  }
}

Vector2 RoomCenter(const struct Room *r) {
  const Vector2 center = {r->x + floor(r->width / 2), r->y + floor(r->height / 2)};
  return center;
}

void ConnectRooms(struct Room *rooms, int map[GetMapHeight()][GetMapWidth()]) {
  struct Room *currentRoom = NULL;

  for (int i = 0; i < GetNumberOfRooms(); i++) {
    if (rooms[i].valid) {
      currentRoom = &rooms[i];
      break;
    }
  }

  if (currentRoom == NULL)
    return;

  for (int i = 0; i < GetNumberOfRooms(); i++) {
    if (!rooms[i].valid)
      continue;

    struct Room *closestRoom = GetClosestRoomCenter(currentRoom, rooms);
    if (closestRoom == NULL)
      break;
    AddCorridor(currentRoom, closestRoom, map);
    currentRoom = closestRoom;
  }
}

void AddCorridor(struct Room *r1, const struct Room *r2,
                 int map[GetMapHeight()][GetMapWidth()]) {
  const Vector2 sRoom = RoomCenter(r1);
  const Vector2 eRoom = RoomCenter(r2);

  const int sx = (int)sRoom.x;
  const int sy = (int)sRoom.y;
  const int ex = (int)eRoom.x;
  const int ey = (int)eRoom.y;

  // Vertical segment from sRoom.y to eRoom.y at column sRoom.x
  const int yStart = sy < ey ? sy : ey;
  const int yEnd = sy < ey ? ey : sy;
  for (int y = yStart; y <= yEnd; y++) {
    map[y][sx] = GetFloorCell();
  }

  // Horizontal segment from sRoom.x to eRoom.x at row eRoom.y
  const int xStart = sx < ex ? sx : ex;
  const int xEnd = sx < ex ? ex : sx;
  for (int x = xStart; x <= xEnd; x++) {
    map[ey][x] = GetFloorCell();
  }

  r1->connected = 1;
}

struct Room *GetClosestRoomCenter(const struct Room *currentRoom,
                                  struct Room *rooms) {
  int closest = INT_MAX;
  struct Room *closestRoom = NULL;

  for (int i = 0; i < GetNumberOfRooms(); i++) {
    if (!rooms[i].valid)
      continue;

    if (rooms[i].connected)
      continue;

    if (currentRoom->x == rooms[i].x && currentRoom->y == rooms[i].y)
      continue;

    Vector2 p1 = {currentRoom->x, currentRoom->y};
    Vector2 p2 = {rooms[i].x, rooms[i].y};
    const int distSq = GetDistance(&p1, &p2);

    if (distSq < closest) {
      closest = distSq;
      closestRoom = &rooms[i];
    }
  }

  return closestRoom;
}
