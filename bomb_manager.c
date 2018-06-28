#ifndef T_CHARACTER
#define T_CHARACTER
// #include "struct_character.h"
// #include "character_creation.h"
#include "bomb_manager.h"
#endif

void put_bomb(t_level *level, t_character *character) {
  t_bomb bomb;
  int position_x;
  int position_y;

  position_x = character->position_x;
  position_y = character->position_y;
  bomb.position_x = position_x;
  bomb.position_y = position_y;
  bomb.range = character->bomb_range;
  level->terrain[position_y][position_x] = '@';
}

void check_bombs_timer(t_level *level) {
  // 1 - Get curr time;
  t_bomb bomb;

  bomb = level.first_bomb;
  while (bomb = bomb.next) {
      if () {
        explode_bomb();
      }
  }
}

void explode_bomb() {

}
