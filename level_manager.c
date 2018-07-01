#include "struct_level.h"
#include "game_constants.h"

int tile_content(t_level *level, int x, int y) {
    int i;

    if(level->terrain[y][x] != ' ') {
      return TILE_WITH_WALL;
    }
    else if(level->bomb[y][x] == '@') {
        return TILE_WITH_BOMB;
    }
    for(i = 0; i < level->number_characters; i++) {
      if(level->characters[i].position_x == x && level->characters[i].position_y == y) {
        return TILE_WITH_CHARACTER;
      }
    }
    return TILE_FREE;
}
