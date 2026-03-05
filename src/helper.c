#include "helper.h"
#include "constants.h"
#include <math.h>
#include <raylib.h>

int GetXfromY(Vector2 startPoint, Vector2 endPoint, int y) {
  int x = ((y - startPoint.y) * endPoint.x) / endPoint.y - startPoint.x;
  return x;
}

int GetYfromX(Vector2 startPoint, Vector2 endPoint, int x) {
  int y = startPoint.y + (x - startPoint.x) * (endPoint.y - startPoint.y) /
                             (endPoint.x - startPoint.x);
  return y;
}

Vector2 GlobalToLocalCoords(Vector2 globalCoords) {
  Vector2 localCoords = {floor(globalCoords.x / CELL_SIZE),
                         floor(globalCoords.y / CELL_SIZE)};

  return localCoords;
}

Vector2 LocalToGlobalCoords(Vector2 localCoord) {
  Vector2 global = {localCoord.x * CELL_SIZE, localCoord.y * CELL_SIZE};

  return global;
}

int GetDistance(Vector2 *p1, Vector2 *p2) {
  int dx = p1->x - p2->x;
  int dy = p1->y - p2->y;
  int distSq = (dx * dx) + (dy * dy);
  return distSq;
}
