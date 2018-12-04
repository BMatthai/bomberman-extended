
#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif


#include "game_constants.h"

int tile_content(t_level *level, int x, int y) {
    return level->terrain[y][x];
}

}
