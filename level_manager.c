
#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif

#include "stdio.h"
#include "game_constants.h"

// int tile_content(t_level *level, int x, int y) {
//     return level->terrain[y][x];
// }

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
  int i;
  for(i = 0; i < level->number_characters; i++) {
    if(level->characters[i].position_x == x && level->characters[i].position_y == y && level->characters[i].state != CHARACTER_DEAD) {
      return YES;
    }
  }
  return NO;
}

int tile_is_bomb_planted(t_level *level, int x, int y) {
  if(level->bomb[y][x] == '@') {
    return YES;
  }
  return NO;
}

int tile_is_bomb_exploding(t_level *level, int x, int y) {
  if(level->bomb[y][x] == 'O') {
      return YES;
  }
  if(level->bomb[y][x] == '^') {
      return YES;
  }
  if(level->bomb[y][x] == 'v') {
      return YES;
  }
  if(level->bomb[y][x] == '<') {
      return YES;
  }
  if(level->bomb[y][x] == '>') {
      return YES;
  }
  return NO;
}

int tile_is_free(t_level *level, int x, int y) {
  if (tile_is_character(level, x, y)) {
    return NO;
  }
  if (tile_is_wall(level, x, y)) {
    return NO;
  }
  if (tile_is_bomb_planted(level, x, y)) {
    return NO;
  }
  return YES;
}

int tile_character(t_level *level, int x, int y) {
  int i;
  for(i = 0; i < level->number_characters; i++) {
    if(level->characters[i].position_x == x && level->characters[i].position_y == y && level->characters[i].state != CHARACTER_DEAD) {
      return TILE_WITH_PLAYER_A + i;
    }
  }
  return NO;
}

int tile_is_bonus(t_level *level, int x, int y) {
  if (level->bonus[y][x] == TILE_WITH_BONUS_1) {
    return YES;
  }
  if (level->bonus[y][x] == TILE_WITH_BONUS_2) {
    return YES;
  }
  if (level->bonus[y][x] == TILE_WITH_BONUS_3) {
    return YES;
  }
  return NO;
}

int tile_is_free_bomb_blast(t_level *level, int x, int y) {
  if (tile_is_character(level, x, y)) {
    return NO;
  }
  if (tile_is_wall(level, x, y)) {
    return NO;
  }
  return YES;
}

int tile_content(t_level *level, int x, int y) {
  if (tile_is_bomb_planted(level, x, y)){
    return level->bomb[y][x];
  }
  if (tile_is_bomb_exploding(level, x, y)){
    return level->bomb[y][x];
  }
  if (tile_is_wall(level, x, y)) {
    return level->terrain[y][x];
  }
  if (tile_is_bonus(level, x, y)) {
    return level->bonus[y][x];
  }
  int i;
  for(i = 0; i < level->number_characters; i++) {
    if(level->characters[i].position_x == x && level->characters[i].position_y == y && level->characters[i].state != CHARACTER_DEAD) {
      return TILE_WITH_PLAYER_A + i;
    }
  }
  return level->terrain[y][x];
}
