
#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif


#include "game_constants.h"

int tile_content(t_level *level, int x, int y) {
    int i;

    if(level->terrain[y][x] > WALL_INDESTRUCTIBLE && level->terrain[y][x] <= WALL_STRONG) {
      return TILE_WITH_DESTRUCTIBLE_WALL;
    }
    else if(level->terrain[y][x] != ' ') {
      return TILE_WITH_WALL;
    }
    else if(level->bomb[y][x] == '@') {
        return TILE_WITH_BOMB;
    }
    for(i = 0; i < level->number_characters; i++) {
      if(level->characters[i].position_x == x && level->characters[i].position_y == y && level->characters[i].state != CHARACTER_DEAD) {
        return TILE_WITH_CHARACTER;
      }
    }
    return TILE_FREE;
}
