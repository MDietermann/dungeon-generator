#include "player.h"
#include <raylib.h>

void InitPlayer(struct Player *p, float x, float y, int fov) {
  p->x = x;
  p->y = y;
  p->velocityX = 0;
  p->velocityY = 0;
  p->fov = fov;
  p->angle = 0;
  p->radius = 3;
}

void TurnPlayer(struct Player *p, int direction, float delta) {
  p->angle += direction * TURN_SPEED * delta;
}

void MovePlayer(struct Player *p, int dirUpDown, int dirLeftRight,
                float delta) {
  p->x += cos(p->angle) * dirUpDown * MOVEMENT_SPEED * delta;
  p->y += sin(p->angle) * dirUpDown * MOVEMENT_SPEED * delta;

  p->x += cos(p->angle + M_PI / 2) * dirLeftRight * MOVEMENT_SPEED * delta;
  p->y += sin(p->angle + M_PI / 2) * dirLeftRight * MOVEMENT_SPEED * delta;
}

void DrawPlayer2D(struct Player *p) {
  // Draw Player Circle
  DrawCircle(p->x, p->y, p->radius, RED);
}
