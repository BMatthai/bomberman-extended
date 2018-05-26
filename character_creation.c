#ifndef T_CHARACTER;
#define T_CHARACTER
#include "character.h"
#endif

#include "game_constants"

create_character() {
    t_character  character;

    character.heal_point = CHARACTER_HEAL_POINT;
    character.bombe_range = CHARACTER_BOMB_RANGE;
    character.number_bomb = CHARACTER_NUMBER_BOMB;
    character.movement_speed = CHARACTER_MOVEMENT_SPEED;
    return character;
}
