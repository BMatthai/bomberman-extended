#include "struct_level.h"

int is_tile_free(t_level *level, int x, int y) {
    //int i;
    if(level->terrain[y][x] != ' ')
      return 0;

    // for(i = 0; i < level->number_characters; i++) {
    //   if(level->characters[i].position_x == x && level->characters[i].position_y == y) {
    //     return 0;
    //   }
    // }
    return 1;
}
