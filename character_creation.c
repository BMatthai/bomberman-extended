#ifndef T_CHARACTER;
#define T_CHARACTER
#include "character.h"
#endif

create_character() {
    t_character  character;
    
    character.heal_point = 100;
    character.bombe_range = 1;
    character.number_bomb = 1;
    character.movement_speed = 10;
    return character;
}


