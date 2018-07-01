
#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif


#ifndef T_CHARACTER
#define T_CHARACTER
#include "struct_character.h"
#endif

#include "bomb_manager.h"
#include "level_manager.h"

#include <unistd.h>


void move(t_level *level, t_character *character, int x, int y) {
  int new_position_x;
  int new_position_y;

  new_position_x = character->position_x + x;
  new_position_y = character->position_y + y;

  if (is_tile_free(level, new_position_x, new_position_y)) {
    character->position_x = new_position_x;
    character->position_y = new_position_y;
  }
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
