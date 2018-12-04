
#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif


#include "game_constants.h"

int tile_content(t_level *level, int x, int y) {
    return level->terrain[y][x];
}

int tile_is_wall(t_level *level, int x, int y) {
  if (level->terrain[y][x] >= TILE_WITH_WALL_ZERO && level->terrain[y][x] <= TILE_WITH_WALL_NINE) {
      return YES;
  }
  return NO;
}

int tile_is_destructible_wall(t_level *level, int x, int y) {
  if (level->terrain[y][x] > TILE_WITH_WALL_ZERO && level->terrain[y][x] <= TILE_WITH_WALL_NINE) {
      return YES;
  }
  return NO;
}

int tile_is_character(t_level *level, int x, int y) {
  if (level->terrain[y][x] == TILE_WITH_PLAYER_A || level->terrain[y][x] == TILE_WITH_PLAYER_B || level->terrain[y][x] == TILE_WITH_PLAYER_C || level->terrain[y][x] == TILE_WITH_PLAYER_D) {
      return YES;
  }
  return NO;
}
