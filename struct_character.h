#ifndef T_CHARACTER
#define T_CHARACTER
#include "struct_character.h"
#endif

typedef struct s_character {
  int heal_points;
  char symbol;
  char bomb_range;
  char number_bomb;
  char movement_speed;
  int position_x;
  int position_y;
}   t_character;
