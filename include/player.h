#ifndef PLAYER_H
#define PLAYER_H

#include "constants.h"
#include "global_imports.h"
#include <math.h>

struct Player {
  float x, y;
  float velocityX, velocityY;
  int fov;
  float angle;
  int radius;
};

void InitPlayer(struct Player *p, float x, float y, int fov);
void TurnPlayer(struct Player *p, int direction, float delta);
void MovePlayer(struct Player *p, int dirUpDown, int dirLeftRight, float delta);
void DrawPlayer2D(struct Player *p);

#endif // !PLAYER_H
