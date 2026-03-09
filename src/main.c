#include "constants.h"
#include "global_imports.h"
#include "map.h"
#include "room.h"
#include <raylib.h>

int MAP_HEIGHT;
int MAP_WIDTH;
int CELL_SIZE;

int *InitializeMap(const int mapWidth, const int mapHeight) {
  MAP_HEIGHT = mapHeight;
  MAP_WIDTH = mapWidth;

  InitMapData(MAP_WIDTH, MAP_HEIGHT, 16);
  int map[GetMapHeight()][GetMapWidth()];
  InitMap(map);

  return map;
}

int *InitializeRooms(int *map[MAP_HEIGHT][MAP_WIDTH], const int numberOfRooms) {
  struct Room rooms[numberOfRooms];
  InitRooms(rooms);

  for (int i = 0; i < numberOfRooms; i++) {
    AddRoomToMap(&rooms[i], map);
  }

  ConnectRooms(rooms, map);
  FillWalls(map);

  return map;
}

int main() {
  int width = 10;
  int height = 10;
  int newMap = *InitializeMap(width, height);

  return 0;
}
