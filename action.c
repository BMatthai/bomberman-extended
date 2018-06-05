//#include "action.h"
#include "stdio.h"
//#include "struct_character.h"
//#include "action.h"

#include <unistd.h>
#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif




int is_tile_free(t_level *level, int x, int y) {
    int i;
    if(level->terrain[y][x] != ' ')
      return 0;

    for(i = 0; i < level->number_characters; i++) {
      if(level->characters[i].position_x == x && level->characters[i].position_y == y) {
        return 0;
      }
    }
    return 1;
}

void move(t_level *level, t_character *character, int x, int y){
  int new_position_x;
  int new_position_y;

  new_position_x = character->position_x + x;
  new_position_y = character->position_y + y;

  if (is_tile_free(level, new_position_x, new_position_y)) {
    character->position_x = new_position_x;
    character->position_y = new_position_y;
  }

}

void action(t_level *level, t_character *character, char touch_action){
  if(touch_action == 'z')
    move(level, character, 0,-1);
  if(touch_action == 's')
    move(level, character, 0,1);
  if(touch_action == 'q')
    move(level, character, -1,0);
  if(touch_action == 'd')
    move(level, character, 1,0);

}
