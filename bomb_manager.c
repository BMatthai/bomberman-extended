#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif


#ifndef T_CHARACTER
#define T_CHARACTER
#include "struct_character.h"
#endif

#include "game_constants.h"
#include "time_manager.h"
#include <stdlib.h>
#include <stdio.h>

void explode_bomb();
void check_bombs_timer(t_level *level);
void put_bomb(t_level *level, t_character *character);

void check_bombs_timer(t_level *level) {

  t_bomb *cur_bomb;

  if((cur_bomb = level->first_bomb) != NULL) {
    while (cur_bomb != NULL) {
      if(cur_bomb->state == IS_PLACED_ON_GROUND)
      {
        if ((get_time() - cur_bomb->time_state_has_changed) > cur_bomb->time_to_explode_millis) {
          explode_bomb(level, cur_bomb);
        }
      }
      if(cur_bomb->state == IS_PLACED_ON_GROUND)
      {
        if ((get_time() - cur_bomb->time_state_has_changed) > BOMB_TIME_BLAST_EXPLOSION){
          bomb_has_exploded(level, cur_bomb);
        }
      }
      cur_bomb = cur_bomb->next_bomb;
    }
  }
}

void put_bomb(t_level *level, t_character *character) {

  t_bomb *new_bomb;

  new_bomb = NULL;
  new_bomb = malloc(sizeof(t_bomb));

  int position_x;
  int position_y;

  position_x = character->position_x;
  position_y = character->position_y;

  level->bomb[position_y][position_x] = '@';

  new_bomb->state = IS_PLACED_ON_GROUND;
  new_bomb->position_x = position_x;
  new_bomb->position_y = position_y;
  new_bomb->time_state_has_changed = get_time();
  new_bomb->time_to_explode_millis = character->time_to_bomb_explode_millis;
  new_bomb->range = character->bomb_range;
  new_bomb->next_bomb = NULL;

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

void explode_bomb(t_level *level, t_bomb *bomb) {

  bomb->state = BOMB_IS_EXPLODING;
  bomb->time_state_has_changed = get_time();

  level->bomb[bomb->position_y][bomb->position_x] = 'O';
  // for (int i = 1; i < 3; i++) {
  //   level->bomb[bomb->position_y + i][bomb->position_x] = 'v';
  //   level->bomb[bomb->position_y - i][bomb->position_x] = '^';
  //   level->bomb[bomb->position_y][bomb->position_x + i] = '>';
  //   level->bomb[bomb->position_y][bomb->position_x - i] = '<';
  // }

  int i = 0;

  int bomb_position_x = bomb->position_x;
  int bomb_position_y = bomb->position_y;

  while (level->terrain[bomb->position_y - i][bomb_position_x] == ' ') {
    level->bomb[bomb->position_y - i][bomb->position_x] = '^';
    i++;
  }
  if (level->terrain[bomb->position_y - i][bomb_position_x] != 0) {
    level->terrain[bomb->position_y - i][bomb_position_x]--;
  }


}

void bomb_has_exploded(t_level *level, t_bomb *bomb) {

  bomb->state = BOMB_HAS_EXPLODED;
  bomb->time_state_has_changed = get_time();

  if (bomb->prev_bomb == NULL && bomb->next_bomb == NULL) {
    level->first_bomb = NULL;
  }
  else if (bomb->prev_bomb == NULL && bomb->next_bomb != NULL) {
    level->first_bomb = bomb->next_bomb;
    bomb->next_bomb->prev_bomb = NULL;
  }
  else if (bomb->prev_bomb != NULL && bomb->next_bomb == NULL) {
    bomb->prev_bomb->next_bomb = NULL;
  }
  else if (bomb->prev_bomb != NULL && bomb->next_bomb != NULL) {
    bomb->prev_bomb->next_bomb = bomb->next_bomb;
    bomb->next_bomb->prev_bomb = bomb->prev_bomb;
  }




}
