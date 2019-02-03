#ifndef T_LEVEL
#define T_LEVEL
#include "../include/struct_level.h"
#endif


#ifndef T_CHARACTER
#define T_CHARACTER
#include "../include/struct_character.h"
#endif

#ifndef T_BOMB
#define T_BOMB
#include "../include/struct_bomb.h"
#endif

#include "../include/log_manager.h"
#include "../include/tile_manager.h"
#include "../include/game_constants.h"
#include "../include/time_manager.h"
#include "../include/bomb_manager.h"

#include <stdlib.h>
#include <stdio.h>

void check_bombs_timer(t_level *level) {
  t_bomb *cur_bomb;

  if ((cur_bomb = level->first_bomb) != NULL) {
    while (cur_bomb != NULL) {
      set_exploding_routine(level, cur_bomb);
      cur_bomb = cur_bomb->next_bomb;
    }
  }
}

t_bomb *get_last_bomb(t_level *level) {
  t_bomb *cur_bomb = NULL;

  cur_bomb = level->first_bomb;

  while (cur_bomb->next_bomb != NULL) {
    cur_bomb = cur_bomb->next_bomb;
  }
  return cur_bomb;
}

t_bomb *create_bomb(t_level *level, t_character *character) {
  t_bomb *bomb = malloc(sizeof(t_bomb));

  if (bomb == NULL) {
    return NULL;
  }

  int position_x = character->position_x - character->velocity_x;
  int position_y = character->position_y - character->velocity_y;

  level->bomb[position_x][position_y] = '@';

  bomb->state = BOMB_IS_PLACED_ON_GROUND;
  bomb->position_x = position_x;
  bomb->position_y = position_y;
  bomb->time_state_has_changed = get_time();
  bomb->time_to_explode_millis = character->time_to_bomb_explode_millis;
  bomb->range = character->bomb_range;
  bomb->next_bomb = NULL;

  return bomb;
}


void set_bomb_unstable(t_bomb *bomb) {
    bomb->state = BOMB_IS_UNSTABLE;
    bomb->time_state_has_changed = get_time();
}

void set_exploding_routine(t_level *level, t_bomb *bomb) {
  if (bomb->state == BOMB_IS_PLACED_ON_GROUND) {
    if ((get_time() - bomb->time_state_has_changed) > bomb->time_to_explode_millis) {
      set_bomb_unstable(bomb);
      return;
    }
  }
  if (bomb->state == BOMB_IS_UNSTABLE) {
    if ((get_time() - bomb->time_state_has_changed) > BOMB_UNSTABLE_DURATION) {
      explode_bomb(level, bomb);
      return;
    }
  }
  if (bomb->state == BOMB_IS_EXPLODING){
    if ((get_time() - bomb->time_state_has_changed) > BOMB_TIME_BLAST_EXPLOSION) {
      bomb_has_exploded(level, bomb);
      free(bomb);
      return;
    }
  }
}

int is_in_bomb_range(t_bomb *bomb, int position_x, int position_y) {
  int bomb_position_x = bomb->position_x;
  int bomb_position_y = bomb->position_y;

  if(bomb_position_x == position_x && bomb_position_y == position_y)
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
    if(bomb_position_x - i == position_x && bomb_position_y == position_y)
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
    if (is_in_bomb_range(cur_bomb, position_x, position_y) == IS_IN_BOMB_RANGE){
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

  level->bomb[bomb_position_x][bomb_position_y] = 'O';
  //damage_tile(level, bomb_position_x, bomb_position_y);

  int i;
  int last_hitted_is_free;

  for (i = 1; i <= bomb->range && (last_hitted_is_free = is_tile_free_bomb_blast(level, bomb_position_x, bomb_position_y - i)); i++) {
    level->bomb[bomb_position_x][bomb_position_y - i] = '^';
  }
  if (last_hitted_is_free == NO)
    damage_tile(level, bomb_position_x, bomb_position_y - i);
  else
    damage_tile(level, bomb_position_x, bomb_position_y - i + 1);

  for (i = 1; i <= bomb->range && (last_hitted_is_free = is_tile_free_bomb_blast(level, bomb_position_x, bomb_position_y + i)); i++) {
    level->bomb[bomb_position_x][bomb_position_y + i] = 'v';
  }
  if (last_hitted_is_free == NO)
    damage_tile(level, bomb_position_x, bomb_position_y + i);
  else
    damage_tile(level, bomb_position_x, bomb_position_y + i - 1);
  for (i = 1; i <= bomb->range && (last_hitted_is_free = is_tile_free_bomb_blast(level, bomb_position_x - i, bomb_position_y)); i++) {
    level->bomb[bomb_position_x - i][bomb_position_y] = '<';
  }
  if (last_hitted_is_free == NO)
    damage_tile(level, bomb_position_x - i, bomb_position_y);
  else
    damage_tile(level, bomb_position_x - i + 1, bomb_position_y);
  for (i = 1; i <= bomb->range && (last_hitted_is_free = is_tile_free_bomb_blast(level, bomb_position_x + i, bomb_position_y)); i++) {
    level->bomb[bomb_position_x + i][bomb_position_y] = '>';
  }
  if (last_hitted_is_free == NO)
    damage_tile(level, bomb_position_x + i, bomb_position_y);
  else
    damage_tile(level, bomb_position_x + i - 1, bomb_position_y);
}

void bomb_has_exploded(t_level *level, t_bomb *bomb) {

  bomb->state = BOMB_HAS_EXPLODED;
  bomb->time_state_has_changed = get_time();


  int bomb_position_x = bomb->position_x;
  int bomb_position_y = bomb->position_y;

  level->bomb[bomb_position_x][bomb_position_y] = ' ';
  int i;

  for (i = 1; is_tile_defined(level, bomb_position_x, bomb_position_y - i) && i <= bomb->range; i++) {
    level->bomb[bomb_position_x][bomb_position_y - i] = ' ';
  }
  for (i = 1; is_tile_defined(level, bomb_position_x, bomb_position_y + i) && i <= bomb->range; i++) {
    level->bomb[bomb_position_x][bomb_position_y + i] = ' ';
  }
  for (i = 1; is_tile_defined(level, bomb_position_x - i, bomb_position_y) && i <= bomb->range; i++) {
    level->bomb[bomb_position_x - i][bomb_position_y] = ' ';
  }
  for (i = 1; is_tile_defined(level, bomb_position_x + i, bomb_position_y) && i <= bomb->range; i++) {
    level->bomb[bomb_position_x + i][bomb_position_y] = ' ';
  }
  remove_bomb_from_list(level, bomb);
}

void damage_tile(t_level *level, int position_x, int position_y) {
  if (level->terrain[position_x][position_y] > WALL_SQUISHY && level->terrain[position_x][position_y] <= WALL_STRONG) {
    level->terrain[position_x][position_y]--;
  }
  else if (level->terrain[position_x][position_y] == WALL_SQUISHY) {
    level->terrain[position_x][position_y] = ' ';
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
  t_bomb *bomb = bomb_at_pos(level, position_x, position_y);
  if (bomb != NULL) {
    if (bomb->state == BOMB_IS_PLACED_ON_GROUND) {
      set_bomb_unstable(bomb);
    }
  }
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
}

t_bomb *bomb_at_pos(t_level *level, int x, int y) {
  t_bomb *cur_bomb = NULL;

  if((cur_bomb = level->first_bomb) != NULL) {
    while (cur_bomb != NULL) {
      if(cur_bomb->position_x == x && cur_bomb->position_y == y) {
        return cur_bomb;
      }
      cur_bomb = cur_bomb->next_bomb;
    }
  }
  return NULL;
}
