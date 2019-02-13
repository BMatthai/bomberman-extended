#ifndef T_LEVEL
#define T_LEVEL
#include "../include/struct_level.h"
#endif

#ifndef T_CHARACTER
#define T_CHARACTER
#include "../include/struct_character.h"
#endif

#include "../include/character_creation.h"
#include "../include/stdio.h"
#include "../include/game_constants.h"
#include "../include/bomb_manager.h"
#include "../include/time_manager.h"

int is_character_in_bomb_range(t_level *level, t_character *character) {
  t_bomb *cur_bomb = NULL;

  if ((cur_bomb = level->first_bomb) == NULL) {
    return NO;
  }

  while(cur_bomb != NULL) {
    if (is_in_bomb_range(cur_bomb, character->position_x, character->position_y) == IS_IN_BOMB_RANGE){
      return NO;
    }
    cur_bomb = cur_bomb->next_bomb;
  }
  return YES;
}

t_character create_character(char symbol, int x, int y) {
  t_character character;

  character.state = CHARACTER_ALIVE;
  character.heal_points = CHARACTER_HEAL_POINT;
  character.bomb_range = CHARACTER_BOMB_RANGE;
  character.stock_bomb = CHARACTER_NUMBER_BOMB;
  character.number_bomb_planted = 0;
  character.movement_speed = CHARACTER_MOVEMENT_SPEED;
  character.time_to_bomb_explode_millis = CHARACTER_TIME_TO_BOMB_EXPLODE;
  character.bomb_damage = CHARACTER_BOMB_DAMAGE;

  character.velocity_x = 0;
  character.velocity_y = 0;

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

  if (level->bonus[position_x][position_y] == BONUS_BOMB_RANGE){
    level->bonus[position_x][position_y] = ' ';
    character->bomb_range += VALUE_BONUS_BOMB_RANGE;
  }
  else if (level->bonus[position_x][position_y] == BONUS_HEAL){
    level->bonus[position_x][position_y] = ' ';
    character->heal_points += VALUE_BONUS_HEAL;
  }
  else if (level->bonus[position_x][position_y] == BONUS_MOVE_SPEED){
    level->bonus[position_x][position_y] = ' ';
    character->movement_speed += VALUE_BONUS_MOVE_SPEED;
  }
  else if (level->bonus[position_x][position_y] == BONUS_EXTRA_BOMB){
    level->bonus[position_x][position_y] = ' ';
    character->stock_bomb += VALUE_BONUS_EXTRA_BOMB;
  }
  else if (level->bonus[position_x][position_y] == BONUS_BOMB_DAMAGE){
    level->bonus[position_x][position_y] = ' ';
    character->bomb_damage += VALUE_BONUS_BOMB_DAMAGE;
  }
}
