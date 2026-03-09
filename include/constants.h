#ifndef CONSTANTS_H
#define CONSTANTS_H

struct MapData {
  int width, height, cellSize;
  int emptyCell, wallCell, floorCell, debugCell;
};

struct RoomData {
  int numberOfRooms;
  int minSize, maxSize;
  int spacing;
  int maxRetries;
};

// Global Getter
struct MapData *GetMapData();
struct RoomData *GetRoomData();
int GetMapWidth();
int GetMapHeight();
int GetCellSize();
int GetNumberOfRooms();
int GetMinRoomSize();
int GetMaxRoomSize();
int GetRoomSpacing();
int GetRoomMaxIterationRetries();
int GetEmptyCell();
int GetWallCell();
int GetFloorCell();
int GetDebugCell();

// Global Setter
void InitMapData(int width, int height, int cellSize);
void InitRoomData(int numberOfRooms, int minSize, int maxSize, int spacing,
                  int maxRetries);
void SetMapWidth(int width);
void SetMapHeight(int height);
void SetCellSize(int cellSize);
void SetNumberOfRooms(int numberOfRooms);
void SetMinRoomSize(int minSize);
void SetMaxRoomSize(int maxSize);
void SetRoomSpacing(int spacing);
void SetRoomMaxIterationRetries(int maxRetries);

#endif // !CONSTANTS_H
