#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif

#ifndef T_CHARACTER
#define T_CHARACTER
#include "struct_character.h"
#endif

#include "character_creation.h"
#include "stdio.h"
#include "game_constants.h"
#include "bomb_manager.h"
#include "time_manager.h"

int is_character_in_bomb_range(t_level *level, t_character *character) {
  t_bomb *cur_bomb = NULL;

  if ((cur_bomb = level->first_bomb) == NULL) {
    return IS_SAFE;
  }

  while(cur_bomb != NULL) {
    if (is_in_bomb_range(level, cur_bomb, character->position_x, character->position_y) == IS_IN_BOMB_RANGE){
      return IS_IN_BOMB_RANGE;
    }
    cur_bomb = cur_bomb->next_bomb;
  }
  return IS_SAFE;
}

t_character create_character(char symbol, int x, int y) {
  t_character character;

  character.state = CHARACTER_ALIVE;
  character.heal_points = CHARACTER_HEAL_POINT;
  character.bomb_range = CHARACTER_BOMB_RANGE;
  character.number_bomb = CHARACTER_NUMBER_BOMB;
  character.movement_speed = CHARACTER_MOVEMENT_SPEED;
  character.time_to_bomb_explode_millis = CHARACTER_TIME_TO_BOMB_EXPLODE;

  character.symbol = symbol;
  character.position_x = x;
  character.position_y = y;
  return character;
}

void reset_character_state(t_character *character) {
  if (character->state == CHARACTER_HITTED) {
    if (get_time() - character->time_state_has_changed > CHARACTER_TIME_HITTED) {
      character->time_state_has_changed = get_time();
      character->state = CHARACTER_ALIVE;
    }
  }
}


void pick_item(t_level *level, t_character *character) {
  int position_x;
  int position_y;

  position_x = character->position_x;
  position_y = character->position_y;

  if (level->bonus[position_y][position_x] == '+'){
    level->bonus[position_y][position_x] = ' ';
    character->bomb_range += 1;
  }
  else if (level->bonus[position_y][position_x] == '#'){
    level->bonus[position_y][position_x] = ' ';
    character->heal_points += 1;
  }
}
