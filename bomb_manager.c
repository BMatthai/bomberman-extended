#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif


#ifndef T_CHARACTER
#define T_CHARACTER
#include "struct_character.h"
#endif

#include "level_manager.h"
#include "game_constants.h"
#include "time_manager.h"
#include <stdlib.h>
#include <stdio.h>

void damage_tile(t_level *level, int position_x, int position_y);
void explode_bomb(t_level *level, t_bomb *bomb);
void bomb_has_exploded(t_level *level, t_bomb *bomb);
void remove_bomb_from_list(t_level *level, t_bomb *bomb);
void check_bombs_timer(t_level *level);
void put_bomb(t_level *level, t_character *character);

void check_bombs_timer(t_level *level) {

  t_bomb *cur_bomb;

  if((cur_bomb = level->first_bomb) != NULL) {
    while (cur_bomb != NULL) {
      if(cur_bomb->state == 1) {
        if ((get_time() - cur_bomb->time_state_has_changed) > cur_bomb->time_to_explode_millis) {
          explode_bomb(level, cur_bomb);
        }
      }
      if(cur_bomb->state == 2){
        if ((get_time() - cur_bomb->time_state_has_changed) > 1000) {
          bomb_has_exploded(level, cur_bomb);
        }
      }
      cur_bomb = cur_bomb->next_bomb;
    }
  }
}

void put_bomb(t_level *level, t_character *character) {
  int position_x;
  int position_y;

  position_x = character->position_x;
  position_y = character->position_y;

  if (tile_content(level, position_x, position_y) != TILE_WITH_BOMB) {
    t_bomb *new_bomb;

    new_bomb = NULL;
    new_bomb = malloc(sizeof(t_bomb));

    level->bomb[position_y][position_x] = '@';

    new_bomb->state = 1;
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
}

int is_in_bomb_range(t_level *level, t_bomb *bomb, int position_x, int position_y) {

  int bomb_position_x = bomb->position_x;
  int bomb_position_y = bomb->position_y;


  if(bomb_position_x == position_x && bomb_position_y== position_y)
      return IS_IN_BOMB_RANGE;
  int i = 1;
  while (i != bomb->range) {
    if(bomb_position_x == position_x && bomb_position_y - i == position_y)
      return IS_IN_BOMB_RANGE;
    i++;
  }
  i = 1;
  while (i != bomb->range) {
    if(bomb_position_x == position_x && bomb_position_y + i == position_y)
      return IS_IN_BOMB_RANGE;
    i++;
  }
  i = 1;
  while (i != bomb->range) {
    if(bomb_position_x -i == position_x && bomb_position_y == position_y)
      return IS_IN_BOMB_RANGE;
    i++;
  }
  i = 1;
  while (i != bomb->range) {
    if(bomb_position_x + i == position_x && bomb_position_y == position_y)
      return IS_IN_BOMB_RANGE;
    i++;
  }
  return IS_SAFE;

}

int is_position_in_any_bomb_range(t_level *level, int position_x, int position_y) {
  t_bomb *cur_bomb = NULL;

  if ((cur_bomb = level->first_bomb) == NULL) {
    return IS_SAFE;
  }

  while (cur_bomb != NULL) {
    if (is_in_bomb_range(level, cur_bomb, position_x, position_y) == IS_IN_BOMB_RANGE){
      if (cur_bomb->state == BOMB_IS_PLACED_ON_GROUND)
        return IS_IN_BOMB_RANGE;
    }
    cur_bomb = cur_bomb->next_bomb;
  }
  return IS_SAFE;
}

void explode_bomb(t_level *level, t_bomb *bomb) {

  bomb->state = BOMB_IS_EXPLODING;
  bomb->time_state_has_changed = get_time();


  int bomb_position_x = bomb->position_x;
  int bomb_position_y = bomb->position_y;

  level->bomb[bomb_position_y][bomb_position_x] = 'O';
  damage_tile(level, bomb_position_x, bomb_position_y);

  int i = 1;
  while (tile_content(level, bomb_position_x, bomb_position_y - i) == TILE_FREE && i != bomb->range) {
    level->bomb[bomb_position_y - i][bomb_position_x] = '^';
    i++;
  }
  damage_tile(level, bomb_position_x, bomb_position_y - i);
  i = 1;
  while (tile_content(level, bomb_position_x, bomb_position_y + i) == TILE_FREE && i != bomb->range) {
    level->bomb[bomb_position_y + i][bomb_position_x] = 'v';
    i++;
  }
  damage_tile(level, bomb_position_x, bomb_position_y + i);
  i = 1;
  while (tile_content(level, bomb_position_x - i, bomb_position_y) == TILE_FREE && i != bomb->range) {
    level->bomb[bomb_position_y][bomb_position_x - i] = '<';
    i++;
  }
  damage_tile(level, bomb_position_x - i, bomb_position_y);
  i = 1;
  while (tile_content(level, bomb_position_x + i, bomb_position_y) == TILE_FREE && i != bomb->range) {
    level->bomb[bomb_position_y][bomb_position_x + i] = '>';
    i++;
  }
  damage_tile(level, bomb_position_x + i, bomb_position_y);


}

void damage_tile(t_level *level, int position_x, int position_y) {
  if (level->terrain[position_y][position_x] > WALL_SQUISHY && level->terrain[position_y][position_x] <= WALL_STRONG) {
    level->terrain[position_y][position_x]--;
  }
  else if (level->terrain[position_y][position_x] == WALL_SQUISHY) {
    level->terrain[position_y][position_x]= ' ';
  }
  for(int i = 0; i < level->number_characters; i++) {
    if(level->characters[i].position_x == position_x && level->characters[i].position_y == position_y) {
      level->characters[i].heal_points -= CHARACTER_BOMB_DAMAGE;
      level->characters[i].state = CHARACTER_HITTED;
      level->characters[i].time_state_has_changed = get_time();
      if (level->characters[i].heal_points <= 0) {
        level->characters[i].symbol = ' ';
        level->characters[i].state = CHARACTER_DEAD;
      }
    }
  }
}

void bomb_has_exploded(t_level *level, t_bomb *bomb) {

  bomb->state = BOMB_HAS_EXPLODED;
  bomb->time_state_has_changed = get_time();

  int i = 1;

  int bomb_position_x = bomb->position_x;
  int bomb_position_y = bomb->position_y;

  level->bomb[bomb_position_y][bomb_position_x] = ' ';
  while (tile_content(level, bomb_position_x, bomb_position_y - i) != TILE_WITH_WALL && i != bomb->range) {
    level->bomb[bomb_position_y - i][bomb_position_x] = ' ';
    i++;
  }
  i = 1;
  while (tile_content(level, bomb_position_x, bomb_position_y + i) != TILE_WITH_WALL && i != bomb->range) {
    level->bomb[bomb_position_y + i][bomb_position_x] = ' ';
    i++;
  }
  i = 1;
  while (tile_content(level, bomb_position_x - i, bomb_position_y) != TILE_WITH_WALL && i != bomb->range) {
    level->bomb[bomb_position_y][bomb_position_x - i] = ' ';
    i++;
  }
  i = 1;
  while (tile_content(level, bomb_position_x + i, bomb_position_y) != TILE_WITH_WALL && i != bomb->range) {
    level->bomb[bomb_position_y][bomb_position_x + i] = ' ';
    i++;
  }
  remove_bomb_from_list(level, bomb);
}

void remove_bomb_from_list(t_level *level, t_bomb *bomb) {
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
  free(bomb);
}
