#ifndef T_CHARACTER
#define T_CHARACTER
#include "struct_character.h"
#endif

typedef struct s_level {
    char *level_name;
    char lines;
    char columns;
    char **terrain; //ou terrain[][] ?;
    char **bonus; //ou bonus[][] ?;
    int number_characters;
    t_character *characters;
}   t_level;
