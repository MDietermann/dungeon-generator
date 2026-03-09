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
  struct RoomData *rd = GetRoomData();
  struct MapData *md = GetMapData();

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
  srand(time(NULL));

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

int DoOverlap(struct Room *r1, struct Room *r2) {
  int r1x1 = r1->x - GetRoomSpacing();
  int r1x2 = r1->x + r1->width + GetRoomSpacing();
  int r1y1 = r1->y - GetRoomSpacing();
  int r1y2 = r1->y + r1->height + GetRoomSpacing();

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

void InitRooms(struct Room *rooms) { ForEachRoom(rooms, CreateRoom); }

void AddRoomToMap(struct Room *room, int map[GetMapHeight()][GetMapWidth()]) {

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
  Vector2 center = {r->x + floor(r->width / 2), r->y + floor(r->height / 2)};

  return center;
}

void ConnectRooms(struct Room *rooms, int map[GetMapHeight()][GetMapWidth()]) {
  struct Room *currentRoom = &rooms[0];

  for (int i = 0; i < GetNumberOfRooms(); i++) {
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
                 int map[GetMapHeight()][GetMapWidth()]) {
  Vector2 sRoom = RoomCenter(r1);
  Vector2 eRoom = RoomCenter(r2);
  struct MapData *md = GetMapData();

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
    map[y][sx] = md->floorCell;
  }

  for (int x = sx; x < ex; x++) {
    map[sy][x] = md->floorCell;
  }

  r1->connected = 1;
}

struct Room *GetClosestRoomCenter(struct Room *currentRoom,
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
    int distSq = GetDistance(&p1, &p2);

    if (distSq < closest) {
      closest = distSq;
      closestRoom = &rooms[i];
    }
  }

  return closestRoom;
}
