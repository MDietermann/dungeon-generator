#ifndef ROOM_H
#define ROOM_H

#include "constants.h"
#include "global_imports.h"
#include "helper.h"

struct Room {
  int x, y;
  int width, height;
  int valid;
  int connected;
};

void InitRooms(struct Room *rooms);
int RoomNotOverlapping(struct Room *r1, struct Room *rooms);
int DoOverlap(const struct Room *r1, const struct Room *r2);
void AddRoomToMap(const struct Room *room, int map[GetMapHeight()][GetMapWidth()]);
void DebugConnectRooms(struct Room *r1, struct Room *r2,
                       int map[GetMapHeight()][GetMapWidth()]);
void ConnectRooms(struct Room *rooms, int map[GetMapHeight()][GetMapWidth()]);
struct Room *GetClosestRoomCenter(const struct Room *currentRoom, struct Room *rooms);

void AddCorridor(struct Room *r1, const struct Room *r2,
                 int map[GetMapHeight()][GetMapWidth()]);

#endif // !ROOM_H
