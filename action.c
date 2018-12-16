
#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif


#ifndef T_CHARACTER
#define T_CHARACTER
#include "struct_character.h"
#endif

#include "log_manager.h"
#include "action.h"
#include "game_constants.h"
#include "bomb_manager.h"
#include "level_manager.h"
#include "character_creation.h"

#include <unistd.h>


void move(t_level *level, t_character *character, int direction) {

  float new_position_x = character->position_x;
  float new_position_y = character->position_y;

  if (direction == ACTION_UP) {
    new_position_y = character->position_y - MOVE_DISTANCE;
    if (tile_is_free(level, new_position_x, new_position_y) == YES) {
      character->position_y = new_position_y;
      b_log("Action : UP\n");
    }
    else {
      adjust_char(level, character);
    }
  }
  else if (direction == ACTION_DOWN) {
    new_position_y = character->position_y + MOVE_DISTANCE;
    if (tile_is_free(level, new_position_x, new_position_y + 1) == YES) {
      character->position_y = new_position_y;
      b_log("Action : DOWN\n");
    }
    else {
      adjust_char(level, character);
    }
  }
  else if (direction == ACTION_LEFT) {
    new_position_x = character->position_x - MOVE_DISTANCE;
    if (tile_is_free(level, new_position_x, new_position_y) == YES) {
      character->position_x = new_position_x;
      b_log("Action : LEFT\n");

    }
    else {
      adjust_char(level, character);
    }
  }
  else if (direction == ACTION_RIGHT) {
    new_position_x = character->position_x + MOVE_DISTANCE;
    if (tile_is_free(level, new_position_x + 1, new_position_y) == YES) {
      character->position_x = new_position_x;
      b_log("Action : RIGHT\n");
    }
    else {
      adjust_char(level, character);
    }
  }
  pick_item(level, character);
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

void adjust_char(t_level *level, t_character *character) {
  float position_x = character->position_x;
  float position_y = character->position_y;

  if (position_x - (int)position_x < 0.33) {
    character->position_x = (int) position_x;
  }
  else {
    character->position_x = (int) position_x + 1;
  }

  if (position_y - (int)position_y < 0.33) {
    character->position_y = (int) position_y;
  }
  else {
    character->position_y = (int) position_y + 1;
  }
}

//
// int is_move_possible(t_level *level, t_character *character, int x, int y) {
//   int new_position_x;
//   int new_position_y;
//
//   new_position_x = character->position_x + x;
//   new_position_y = character->position_y + y;
//
//   if (tile_is_free(level, new_position_x, new_position_y) == YES) {
//     return YES;
//   }
//   return NO;
// }

// int is_move_to_top_possible(t_level *level, t_character *character) {
//   return is_move_possible(level, character, 0, -1);
// }
//
// int is_move_to_bot_possible(t_level *level, t_character *character) {
//   return is_move_possible(level, character, 0, 1);
// }
//
// int is_move_to_left_possible(t_level *level, t_character *character) {
//   return is_move_possible(level, character, -1, 0);
// }
//
// int is_move_to_right_possible(t_level *level, t_character *character) {
//   return is_move_possible(level, character, 1, 0);
// }

// int number_of_direction_possible(t_level *level, t_character *character) {
//   int number_of_direction_possible;
//
//   number_of_direction_possible = 0;
//
//   if (is_move_to_top_possible(level, character))
//     number_of_direction_possible++;
//   if (is_move_to_bot_possible(level, character))
//     number_of_direction_possible++;
//   if (is_move_to_left_possible(level, character))
//     number_of_direction_possible++;
//   if (is_move_to_right_possible(level, character))
//     number_of_direction_possible++;
//   return number_of_direction_possible;
// }
