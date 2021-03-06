#ifndef T_LEVEL
#define T_LEVEL
#include "../include/struct_level.h"
#endif

#ifndef T_CHARACTER
#define T_CHARACTER
#include "../include/struct_character.h"
#endif

#include "../include/action.h"
#include "../include/log_manager.h"
#include "../include/game_constants.h"
#include "../include/bomb_manager.h"
#include "../include/tile_manager.h"
#include "../include/character_creation.h"
#include "../include/time_manager.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void move(t_level *level, t_character *character, int direction) {

  float new_position_x = character->position_x;
  float new_position_y = character->position_y;

  if (direction == ACTION_UP) {
    new_position_y = character->position_y - (MOVE_DISTANCE * character->movement_speed);
    if (is_tile_free(level, new_position_x, new_position_y) == YES) {
      character->position_y = new_position_y;
    }
    else {
      adjust_char(character);
    }
  }
  else if (direction == ACTION_DOWN) {
    new_position_y = character->position_y + (MOVE_DISTANCE * character->movement_speed);
    if (is_tile_free(level, new_position_x, new_position_y + 1) == YES) {
      character->position_y = new_position_y;
    }
    else {
      adjust_char(character);
    }
  }
  else if (direction == ACTION_LEFT) {
    new_position_x = character->position_x - (MOVE_DISTANCE * character->movement_speed);
    if (is_tile_free(level, new_position_x, new_position_y) == YES) {
      character->position_x = new_position_x;
    }
    else {
      adjust_char(character);
    }
  }
  else if (direction == ACTION_RIGHT) {
    new_position_x = character->position_x + (MOVE_DISTANCE * character->movement_speed);
    if (is_tile_free(level, new_position_x + 1, new_position_y) == YES) {
      character->position_x = new_position_x;
    }
    else {
      adjust_char(character);
    }
  }
  pick_item(level, character);
}

void put_bomb(t_level *level, t_character *character) {
  int position_x;
  int position_y;

  position_x = character->position_x;
  position_y = character->position_y;

  if (character->number_bomb_planted >= character->stock_bomb) {
    return;
  }

  if (level->terrain[position_x][position_y] != TILE_WITH_BOMB) {
    t_bomb *new_bomb;

    new_bomb = NULL;
    //new_bomb = malloc(sizeof(t_bomb)); // free done

    level->bomb[position_x][position_y] = '@';
    character->number_bomb_planted += 1;

    new_bomb = create_bomb(level, character);

    if (level->first_bomb == NULL) {
      level->first_bomb = new_bomb;
      new_bomb->prev_bomb = NULL;
    }
    else {
      t_bomb *cur_bomb;
      cur_bomb = level->first_bomb;
      while (cur_bomb->next_bomb != NULL) {
        cur_bomb = cur_bomb->next_bomb;
      }
      new_bomb->prev_bomb = cur_bomb;
      cur_bomb->next_bomb = new_bomb;
    }
  }
}

void action(t_level *level, t_character *character, int touch_action) {
  if(touch_action == ACTION_UP)
    move(level, character, ACTION_UP);
  if(touch_action == ACTION_DOWN)
    move(level, character, ACTION_DOWN);
  if(touch_action == ACTION_LEFT)
    move(level, character, ACTION_LEFT);
  if(touch_action == ACTION_RIGHT)
    move(level, character, ACTION_RIGHT);
  if(touch_action == ACTION_BOMB)
    put_bomb(level, character);
}

void set_velocity_character(t_character *character, int velocity_x, int velocity_y) {
  character->velocity_x = velocity_x;
  character->velocity_y = velocity_y;
}

void adjust_char(t_character *character) {
  float position_x = character->position_x;
  float position_y = character->position_y;

  float scale_x = position_x - (int)position_x;
  float scale_y = position_y - (int)position_y;

  if (scale_y < 0.1)
    character->position_y = (int) position_y;
  else if (scale_y > 0.9)
    character->position_y = (int) position_y + 1;

  if (scale_x < 0.1)
    character->position_x = (int) position_x;
  else if (scale_x > 0.9)
    character->position_x = (int) position_x + 1;
}

void motion_char(t_level *level, t_character *character) {
  float position_x = character->position_x;
  float position_y = character->position_y;

  float scale_x = position_x - (int)position_x;
  float scale_y = position_y - (int)position_y;
  if (character->velocity_y == 0 && scale_y > 0 && scale_y < 0.1)
    character->position_y = (int) position_y;
  else if (character->velocity_y == 0 && scale_y >= 0.1 && scale_y < 0.5)
    move(level, character, ACTION_UP);
  else if (character->velocity_y == 0 && scale_y >= 0.5 && scale_y < 1)
    move(level, character, ACTION_DOWN);

  if(character->velocity_x == 0  && scale_x > 0 && scale_x < 0.1)
    character->position_x = (int) position_x;
  else if(character->velocity_x == 0  && scale_x >= 0.1 && scale_x < 0.5)
    move(level, character, ACTION_LEFT);
  else if(character->velocity_x == 0 && scale_x >= 0.5 && scale_x < 1)
    move(level, character, ACTION_RIGHT);
}

void move_char(t_level *level, t_character *character) {
  if (character->velocity_y == -1)
    move(level, character, ACTION_UP);
  else if (character->velocity_y == 1)
    move(level, character, ACTION_DOWN);
  if(character->velocity_x == -1)
    move(level, character, ACTION_LEFT);
  else if(character->velocity_x == 1)
    move(level, character, ACTION_RIGHT);
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
    if (character->heal_points <= 100)
      character->heal_points += VALUE_BONUS_HEAL;
  }
  else if (level->bonus[position_x][position_y] == BONUS_MOVE_SPEED){
    level->bonus[position_x][position_y] = ' ';
    if (character->movement_speed <= 20)
      character->movement_speed += VALUE_BONUS_MOVE_SPEED;
  }
  else if (level->bonus[position_x][position_y] == BONUS_EXTRA_BOMB){
    level->bonus[position_x][position_y] = ' ';
    if (character->stock_bomb <= 5)
      character->stock_bomb += VALUE_BONUS_EXTRA_BOMB;
  }
  else if (level->bonus[position_x][position_y] == BONUS_BOMB_DAMAGE){
    level->bonus[position_x][position_y] = ' ';
    if (character->bomb_damage <= 350)
      character->bomb_damage += VALUE_BONUS_BOMB_DAMAGE;
  }
}
