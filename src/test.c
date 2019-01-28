#ifndef T_LEVEL
#define T_LEVEL
#include "../include/struct_level.h"
#endif

#include "../include/test.h"
#include "../include/struct_game_settings.h"
#include "../include/maze_generation.h"
#include <stdlib.h>
#include <stdio.h>

void generate_mazes() {

  t_game_settings *settings = NULL;
  settings = malloc(sizeof(t_game_settings));
  t_level *cur_level = NULL;

  for(int i = 8; i < 64; i++) {
    for(int j = 8; j < 48; j++) {
      // for(int k = 0; k < 105; k+=20) {
      //   for(int l = 0; l < 105; l+=20) {
          settings->width = i;
          settings->height = j;
          settings->proba_destr_wall = 50;
          settings->proba_empty = 50;
          printf("Trying : (%d;%d;%d;%d)\n",settings->width, settings->height , settings->proba_destr_wall, settings->proba_empty);
          cur_level = generate_maze_level(settings);
          printf("Niveau généré\n\n");
          free(cur_level);

      //   }
      // }
    }
  }
  // printf("Génération OK");
}
