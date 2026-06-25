#include "helper.h"
#include "constants.h"
#include <math.h>
#include <raylib.h>

int GetXfromY(const Vector2 startPoint, const Vector2 endPoint, const int y) {
  const int x = ((y - startPoint.y) * endPoint.x) / endPoint.y - startPoint.x;
  return x;
}

int GetYfromX(const Vector2 startPoint, const Vector2 endPoint, const int x) {
  const int y = startPoint.y + (x - startPoint.x) * (endPoint.y - startPoint.y) /
                             (endPoint.x - startPoint.x);
  return y;
}

Vector2 GlobalToLocalCoords(const Vector2 globalCoords) {
  const Vector2 localCoords = {floor(globalCoords.x / GetCellSize()),
                         floor(globalCoords.y / GetCellSize())};

  return localCoords;
}

Vector2 LocalToGlobalCoords(const Vector2 localCoord) {
  const Vector2 global = {localCoord.x * GetCellSize(), localCoord.y * GetCellSize()};

  return global;
}

int GetDistance(const Vector2 *p1, const Vector2 *p2) {
  const int dx = p1->x - p2->x;
  const int dy = p1->y - p2->y;
  const int distSq = (dx * dx) + (dy * dy);
  return distSq;
}
