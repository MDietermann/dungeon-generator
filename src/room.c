#include "room.h"
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
        continue;
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
  Vector2 center = {r->x * CELL_SIZE + (r->width * CELL_SIZE / 2),
                    r->y * CELL_SIZE + (r->height * CELL_SIZE / 2)};

  return center;
}

void DebugConnectRooms(struct Room *r1, struct Room *r2) {
  Vector2 r1Center = RoomCenter(r1);
  Vector2 r2Center = RoomCenter(r2);

  DrawLineEx(r1Center, r2Center, 2, RED);
}

void ConnectRooms(
    int roomCount, struct Room *rooms,
    int map[WINDOW_HEIGHT / CELL_SIZE][WINDOW_WIDTH / CELL_SIZE]) {
  return;
}
