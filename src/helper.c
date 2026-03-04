#include "helper.h"
#include "constants.h"
#include <math.h>

int GetXfromY(Vector2 startPoint, Vector2 endPoint, int y) {
  int x = ((y - startPoint.y) * endPoint.x) / endPoint.y - startPoint.x;
  return x;
}

int GetYfromX(Vector2 startPoint, Vector2 endPoint, int x) {
  int y = ((x - startPoint.x) * endPoint.y) / endPoint.x - startPoint.x;
  return y;
}

Vector2 GlobalToLocalCoords(Vector2 globalCoords) {
  Vector2 localCoords = {floor(globalCoords.x / CELL_SIZE),
                         floor(globalCoords.y / CELL_SIZE)};

  return localCoords;
}
