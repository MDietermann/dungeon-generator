#ifndef HELPER_H
#define HELPER_H

#include "constants.h"
#include "global_imports.h"

int GetXfromY(Vector2 startPoint, Vector2 endPoint, int y);
int GetYfromX(Vector2 startPoint, Vector2 endPoint, int x);
Vector2 GlobalToLocalCoords(Vector2 globalCoords);
Vector2 LocalToGlobalCoords(Vector2 localCoords);

#endif // !HELPER_H
