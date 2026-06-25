//
// Created by marvin on 3/9/26.
//

#ifndef DUNGEON_GENERATOR_H
#define DUNGEON_GENERATOR_H

#include "constants.h"
#include "global_imports.h"
#include "map.h"
#include "room.h"
#include <raylib.h>
#include <string.h>

void GenerateDungeon(void);
void FreeDungeon(void);
struct Room *GetDungeonRooms(int *outCount);
int *GetDungeonMap(void);

#endif
