#ifndef T_CHARACTER
#define T_CHARACTER
#include "struct_character.h"
#include "character_creation.h"
#endif

#include "stdio.h"
#include "game_constants.h"

t_character create_character(char symbol, int x, int y) {
  t_character character;

  character.heal_points = CHARACTER_HEAL_POINT;
  character.bomb_range = CHARACTER_BOMB_RANGE;
  character.number_bomb = CHARACTER_NUMBER_BOMB;
  character.movement_speed = CHARACTER_MOVEMENT_SPEED;
  character.time_to_bomb_explode = CHARACTER_TIME_TO_BOMB_EXPLODE;

  character.symbol = symbol;
  character.position_x = x;
  character.position_y = y;
  return character;
}
