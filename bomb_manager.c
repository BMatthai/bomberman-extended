#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif


#ifndef T_CHARACTER
#define T_CHARACTER
#include "struct_character.h"
#endif

#include "time_manager.h"

void explode_bomb();
void check_bombs_timer(t_level *level);
void put_bomb(t_level *level, t_character *character);

void check_bombs_timer(t_level *level) {

  t_bomb *bomb;

  bomb = level->first_bomb;
  while ((bomb = bomb->next_bomb)) {
      if (get_time() - bomb->time_placed > bomb->time_to_explode) {
        explode_bomb(level, bomb);
      }
  }
}

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

void explode_bomb(t_level *level, t_bomb *bomb) {
  level->terrain[bomb->position_y][bomb->position_x] = ' ';
}
