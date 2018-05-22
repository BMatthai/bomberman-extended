#ifndef T_CHARACTER;
#define T_CHARACTER
#include "character.h"
#endif

typedef struct s_level {
    char *level_name;
    char **terrain; //ou terrain[][] ?;
    char **bonus; //ou bonus[][] ?;
    t_character *characters;
}   t_level;
