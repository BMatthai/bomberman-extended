#ifndef T_CHARACTER;
#define T_CHARACTER
#include "character.h"
#endif

#include "game_constants"

t_character *create_character(char symbol, int x, int y) {
  t_character *character;

  character = malloc(sizeof(character));

    character.heal_point = CHARACTER_HEAL_POINT;
    character.bombe_range = CHARACTER_BOMB_RANGE;
    character.number_bomb = CHARACTER_NUMBER_BOMB;
    character.movement_speed = CHARACTER_MOVEMENT_SPEED;

    character.symbol = symbol;
    character.position_x = x;
    character.position_y = y;
    return character;
}
