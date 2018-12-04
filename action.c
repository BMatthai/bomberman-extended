
#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif


#ifndef T_CHARACTER
#define T_CHARACTER
#include "struct_character.h"
#endif

#include "game_constants.h"
#include "bomb_manager.h"
#include "level_manager.h"
#include "character_creation.h"

#include <unistd.h>


int move(t_level *level, t_character *character, int x, int y) {
    int new_position_x;
    int new_position_y;

    new_position_x = character->position_x + x;
    new_position_y = character->position_y + y;

  if (tile_content(level, new_position_x, new_position_y) == TILE_FREE) {
    character->position_x = new_position_x;
    character->position_y = new_position_y;
    pick_item(level, character);
    return MOVE_POSSIBLE;
  }
  return MOVE_IMPOSSIBLE;
}

int is_move_possible(t_level *level, t_character *character, int x, int y) {
  int new_position_x;
  int new_position_y;

  new_position_x = character->position_x + x;
  new_position_y = character->position_y + y;

  if (tile_content(level, new_position_x, new_position_y) == TILE_FREE) {
    return YES;
  }
  return NO;
}

int move_to_dir(t_level *level, t_character *character, int dir) {
  if (dir == 0)
    return move(level, character, 0, -1);
  if (dir == 1)
    return move(level, character, 0, 1);
  if (dir == 2)
    return move(level, character, -1, 0);
  if (dir == 3)
    return move(level, character, 1, 0);
  return MOVE_IMPOSSIBLE;
}

int is_move_to_top_possible(t_level *level, t_character *character) {
  return is_move_possible(level, character, 0, -1);
}

int is_move_to_bot_possible(t_level *level, t_character *character) {
  return is_move_possible(level, character, 0, 1);
}

int is_move_to_left_possible(t_level *level, t_character *character) {
  return is_move_possible(level, character, -1, 0);
}

int is_move_to_right_possible(t_level *level, t_character *character) {
  return is_move_possible(level, character, 1, 0);
}

int number_of_direction_possible(t_level *level, t_character *character) {
  int number_of_direction_possible;

  number_of_direction_possible = 0;

  if (is_move_to_top_possible(level, character))
    number_of_direction_possible++;
  if (is_move_to_bot_possible(level, character))
    number_of_direction_possible++;
  if (is_move_to_left_possible(level, character))
    number_of_direction_possible++;
  if (is_move_to_right_possible(level, character))
    number_of_direction_possible++;
  return number_of_direction_possible;
}



void action(t_level *level, t_character *character, char touch_action) {
  if(touch_action == 'z')
    move(level, character, 0,-1);
  if(touch_action == 's')
    move(level, character, 0,1);
  if(touch_action == 'q')
    move(level, character, -1,0);
  if(touch_action == 'd')
    move(level, character, 1,0);
  if(touch_action == 'c')
    put_bomb(level, character);
}
