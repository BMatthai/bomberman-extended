#ifndef T_CHARACTER
#define T_CHARACTER
#include "struct_character.h"
#endif

#ifndef T_BOMB
#define T_BOMB
#include "struct_bomb.h"
#endif


typedef struct s_level {
    char *level_name;
    char width;
    char height;
    char **terrain;
    char **bonus;
    char **bomb;
    int number_characters;
    t_character *characters;
    t_bomb *first_bomb;
}   t_level;
