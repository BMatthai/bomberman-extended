#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif


#ifndef T_CHARACTER
#define T_CHARACTER
#include "struct_character.h"
#endif

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
        if ((get_time() - cur_bomb->time_placed) > cur_bomb->time_to_explode) {
          explode_bomb(level, cur_bomb);
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

  level->terrain[position_y][position_x] = '@';

  new_bomb->position_x = position_x;
  new_bomb->position_y = position_y;
  new_bomb->time_placed = get_time();
  new_bomb->time_to_explode = character->time_to_bomb_explode;
  new_bomb->range = character->bomb_range;
  new_bomb->next_bomb = NULL;

  if (level->first_bomb == NULL) {
    level->first_bomb = new_bomb;
    new_bomb->prev_bomb = NULL;
  }
  else {
    t_bomb *cur_bomb;
    cur_bomb = level->first_bomb;
    // while (cur_bomb->next_bomb != NULL) {
    //   cur_bomb = cur_bomb->next_bomb;
    // }
    new_bomb->prev_bomb = cur_bomb;
    cur_bomb->next_bomb = new_bomb;
  }
}

void explode_bomb(t_level *level, t_bomb *bomb) {

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

  level->terrain[bomb->position_y][bomb->position_x] = ' ';

  //Free bomb
}
