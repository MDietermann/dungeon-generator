#ifndef HELPER_H
#define HELPER_H

#include "constants.h"
#include "global_imports.h"
#include <raylib.h>

int GetXfromY(Vector2 startPoint, Vector2 endPoint, int y);
int GetYfromX(Vector2 startPoint, Vector2 endPoint, int x);
Vector2 GlobalToLocalCoords(Vector2 globalCoords);
Vector2 LocalToGlobalCoords(Vector2 localCoords);
int GetDistance(Vector2 *p1, Vector2 *p2);

#endif // !HELPER_H
