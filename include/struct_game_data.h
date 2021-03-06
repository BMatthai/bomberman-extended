#ifndef T_LEVEL
#define T_LEVEL
#include "../include/struct_level.h"
#endif

#ifndef T_CHARACTER
#define T_CHARACTER
#include "../include/struct_character.h"
#endif



typedef struct s_game_data {
  t_character *playable_character;
  t_level *level;
  Uint32 elapsed_time;
} t_game_data;
