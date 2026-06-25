#include "dungeon_generator.h"

static struct Room *gRooms = NULL;
static int gRoomCount = 0;
static int *gMap = NULL;

void GenerateDungeon(void) {
  FreeDungeon();

  int h = GetMapHeight();
  int w = GetMapWidth();

  gMap = malloc(sizeof(int) * h * w);
  InitMap((int(*)[w])gMap);

  gRoomCount = GetNumberOfRooms();
  gRooms = malloc(sizeof(struct Room) * gRoomCount);
  memset(gRooms, 0, sizeof(struct Room) * gRoomCount);
  InitRooms(gRooms);

  for (int i = 0; i < gRoomCount; i++) {
    if (!gRooms[i].valid)
      continue;
    AddRoomToMap(&gRooms[i], (int(*)[w])gMap);
  }

  ConnectRooms(gRooms, (int(*)[w])gMap);
  FillWalls((int(*)[w])gMap);
}

void FreeDungeon(void) {
  free(gRooms);
  gRooms = NULL;
  gRoomCount = 0;
  free(gMap);
  gMap = NULL;
}

struct Room *GetDungeonRooms(int *outCount) {
  if (outCount)
    *outCount = gRoomCount;
  return gRooms;
}

int *GetDungeonMap(void) {
  return gMap;
}
