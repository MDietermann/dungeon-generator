#ifndef ROOM_H
#define ROOM_H

#include "constants.h"
#include "global_imports.h"

struct Room {
  int x, y;
  int width, height;
  int valid;
  int connected;
};

void InitRooms(struct Room *rooms);
int RoomNotOverlapping(struct Room *r1, struct Room *rooms);
int DoOverlap(struct Room *r1, struct Room *r2);
void AddRoomToMap(struct Room *room,
                  int map[WINDOW_HEIGHT / CELL_SIZE][WINDOW_WIDTH / CELL_SIZE]);
void DebugConnectRooms(struct Room *r1, struct Room *r2);
void ConnectRooms(int roomCount, struct Room *rooms,
                  int map[WINDOW_HEIGHT / CELL_SIZE][WINDOW_WIDTH / CELL_SIZE]);
Vector2 GetClosestRoomCenter(struct Room *currentRoom);
#endif // !ROOM_H
