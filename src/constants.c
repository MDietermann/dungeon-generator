#include "constants.h"
#include <stdlib.h>

struct MapData *md;
struct RoomData *rd;

// Global Getter
struct MapData *GetMapData() { return md; }

struct RoomData *GetRoomData() { return rd; }

int GetMapWidth() { return md->width; }

int GetMapHeight() { return md->height; }

int GetCellSize() { return md->cellSize; }

int GetEmptyCell() { return md->emptyCell; }

int GetWallCell() { return md->wallCell; }

int GetFloorCell() { return md->floorCell; }

int GetDebugCell() { return md->debugCell; }

int GetNumberOfRooms() { return rd->numberOfRooms; }

int GetMinRoomSize() { return rd->minSize; }

int GetMaxRoomSize() { return rd->maxSize; }

int GetRoomSpacing() { return rd->spacing; }

int GetRoomMaxIterationRetries() { return rd->maxRetries; }

// Global Setter

/*
 * @brief Initializes Map Data
 *
 * Initializes crutial Parameters used for automated Map Generation.
 * It also generates preset cell IDs:
 * emptyCell -> 0
 * wallCell -> 1
 * floorCell -> 2
 * debugCell -> -1
 *
 * @param[in] width int The overall width of the generated map.
 * @param[in] height int The overall height of the generated map.
 * @return void
 */
void InitMapData(const int width, const int height, const int cellSize) {
  if (md == NULL)
    md = malloc(sizeof(struct MapData));
  md->width = width;
  md->height = height;
  md->cellSize = cellSize;
  md->emptyCell = 0;
  md->wallCell = 1;
  md->floorCell = 2;
  md->debugCell = -1;
}

void InitRoomData(const int numberOfRooms, const int minSize, const int maxSize, const int spacing,
                  const int maxRetries) {
  if (rd == NULL)
    rd = malloc(sizeof(struct RoomData));
  rd->numberOfRooms = numberOfRooms;
  rd->minSize = minSize;
  rd->maxSize = maxSize;
  rd->spacing = spacing;
  rd->maxRetries = maxRetries;
}

void SetMapWidth(const int width) { md->width = width; }

void SetMapHeight(const int height) { md->height = height; }

void SetCellSize(const int cellSize) { md->cellSize = cellSize; }

void SetNumberOfRooms(const int numberOfRooms) { rd->numberOfRooms = numberOfRooms; }

void SetMinRoomSize(const int minSize) { rd->minSize = minSize; }

void SetMaxRoomSize(const int maxSize) { rd->maxSize = maxSize; }

void SetRoomSpacing(const int spacing) { rd->spacing = spacing; }

void SetRoomMaxIterationRetries(const int maxRetries) { rd->maxRetries = maxRetries; }
