
#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif

#include "game_constants.h"
#include "tile_manager.h"
#include "bomb_manager.h"

int is_tile_wall(t_level *level, int x, int y) {
  if (level->terrain[y][x] >= TILE_WITH_WALL_ZERO && level->terrain[y][x] <= TILE_WITH_WALL_NINE)
      return YES;
  return NO;
}

int is_tile_destructible_wall(t_level *level, int x, int y) {
  if (level->terrain[y][x] > TILE_WITH_WALL_ZERO && level->terrain[y][x] <= TILE_WITH_WALL_NINE)
      return YES;
  return NO;
}

int is_tile_character(t_level *level, int x, int y) {
  for (int i = 0; i < level->number_characters; i++) {
    if (level->characters[i].position_x == x &&
      level->characters[i].position_y == y &&
      level->characters[i].state != CHARACTER_DEAD) {
      return YES;
    }
  }
  return NO;
}


int is_tile_bomb_planted(t_level *level, int x, int y) {
  if (level->bomb[y][x] == '@')
    return YES;
  return NO;
}

int is_tile_bomb_exploding_up(t_level *level, int x, int y) {
  if(level->bomb[y][x] == '^')
      return YES;
  return NO;
}

int is_tile_bomb_exploding_down(t_level *level, int x, int y) {
  if(level->bomb[y][x] == 'v')
      return YES;
  return NO;
}

int is_tile_bomb_exploding_left(t_level *level, int x, int y) {
  if(level->bomb[y][x] == '<')
      return YES;
  return NO;
}

int is_tile_bomb_exploding_right(t_level *level, int x, int y) {
  if(level->bomb[y][x] == '>')
      return YES;
  return NO;
}

int is_tile_bomb_exploding_origin(t_level *level, int x, int y) {
  if(level->bomb[y][x] == 'O')
      return YES;
  return NO;
}

int is_tile_bomb_exploding(t_level *level, int x, int y) {
  if (is_tile_bomb_exploding_up(level, x, y) == YES ||
  is_tile_bomb_exploding_down(level, x, y) == YES  ||
  is_tile_bomb_exploding_left(level, x, y) == YES ||
  is_tile_bomb_exploding_right(level, x, y) == YES ||
  is_tile_bomb_exploding_origin(level, x, y) == YES)
    return YES;
  return NO;
}

int is_tile_free(t_level *level, float x, float y) {
  if (is_tile_wall(level, (int)x, (int)y))
    return NO;
  if (is_tile_defined(level, (int)x, (int)y) == NO)
    return NO;
  return YES;
}

int tile_character(t_level *level, int x, int y) {
  for (int i = 0; i < level->number_characters; i++) {
    if (level->characters[i].position_x == x &&
      level->characters[i].position_y == y &&
      level->characters[i].state != CHARACTER_DEAD)
      return TILE_WITH_PLAYER_A + i;
  }
  return NO;
}

int is_tile_bonus(t_level *level, int x, int y) {
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

int is_tile_free_for_bomb(t_level *level, int x, int y) {
  if (is_tile_bomb_planted(level, x, y))
    return NO;
  if (is_tile_character(level, x, y))
    return NO;
  if (is_tile_wall(level, x, y))
    return NO;
  return YES;
}

int is_tile_free_bomb_blast(t_level *level, int x, int y) {
  if (is_tile_character(level, x, y))
    return NO;
  if (is_tile_wall(level, x, y))
    return NO;
  if (is_tile_bomb_planted(level, x, y))
    return NO;
  return YES;
}

int tile_content(t_level *level, int x, int y) {
  if (is_tile_bomb_planted(level, x, y))
    return level->bomb[y][x];
  if (is_tile_bomb_exploding(level, x, y))
    return level->bomb[y][x];
  if (is_tile_wall(level, x, y))
    return level->terrain[y][x];
  if (is_tile_bonus(level, x, y))
    return level->bonus[y][x];
  for (int i = 0; i < level->number_characters; i++) {
    if (level->characters[i].position_x == x &&
      level->characters[i].position_y == y &&
      level->characters[i].state != CHARACTER_DEAD) {
      return TILE_WITH_PLAYER_A + i;
    }
  }
  return level->terrain[y][x];
}

int is_tile_defined(t_level *level, int x, int y) {
  if (x < 0)
    return NO;
  if (y < 0)
    return NO;
  if (x >= level->columns)
    return NO;
  if (y >= level->lines)
    return NO;
  return YES;
}
