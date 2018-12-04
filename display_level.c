#ifndef T_GAME_DATA
#define T_GAME_DATA
#include "struct_game_data.h"
#endif



#include "display_level.h"
#include "game_constants.h"
#include "color_manager.h"

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *level_to_display(t_level *level) {
  int i;
  int j;
  int k;
  int lines;
  int columns;
  char *level_to_display;

  lines = level->lines;
  columns = level->columns;

  level_to_display = malloc(sizeof(char) * lines * columns);

  if (level_to_display == NULL) {
    return NULL;
  }

  for (i = 0; i < lines; i++) {
    for (j = 0; j < columns; j++) {

      if((level_to_display[i * columns + j] = level->terrain[i][j]) == ' ') {
        level_to_display[i * columns + j] = level->bonus[i][j];
      }

      if (level->bomb[i][j] == '^'
      || level->bomb[i][j] == 'v'
      || level->bomb[i][j] == '>'
      || level->bomb[i][j] == '<'
      || level->bomb[i][j] == '@'
      || level->bomb[i][j] == 'O')
        level_to_display[i * columns + j] = level->bomb[i][j];
    }
  }

  for (k = 0; k < level->number_characters; k++) {
    if (level->characters[k].state != CHARACTER_DEAD) {
      level_to_display[level->characters[k].position_y * columns + level->characters[k].position_x] = level->characters[k].symbol;
    }
  }

  return level_to_display;
}

void display_hud(t_game_data *game_data) {

  t_character *character = game_data->playable_character;

  int heal_points = character->heal_points;
  char bomb_range = character->bomb_range;
  char number_bomb = character->number_bomb;
  char movement_speed = character->movement_speed;
  int time_to_bomb_explode_millis = character->time_to_bomb_explode_millis;

  set_color_hud();
  printf("Vie : %d\n", heal_points);
  printf("Porté des bombes : %d\n", bomb_range);
  printf("Nombre max de bombes : %d\n", number_bomb);
  printf("Vitesse : %d\n", movement_speed);
  printf("Délai explosion bombe : %d\n", time_to_bomb_explode_millis);
  write(1, "--------", strlen("--------"));
  write(1, "\n", strlen("\n"));

}

void display_level(t_game_data *game_data) {

  t_level *level = game_data->level;
  char *level_terrain = level_to_display(game_data->level);


  for(int i = 0; i < level->lines; i++) {
    for(int j = 0; j < level->columns; j++) {
        int cur_tile_content = level->terrain[y][x];
        if(cur_tile_content == TILE_WITH_PLAYER_A) {
          if (level->characters[0].state == CHARACTER_HITTED)
            set_color_white();
          else
            set_color_red();
        }
        else if(cur_tile_content == TILE_WITH_PLAYER_B) {
          if (level->characters[1].state == CHARACTER_HITTED)
            set_color_white();
          else
            set_color_red();
        }
        else if(cur_tile_content == TILE_WITH_PLAYER_C) {
          if (level->characters[2].state == CHARACTER_HITTED)
            set_color_white();
          else
          set_color_yellow();
        }
        else if(cur_tile_content == TILE_WITH_PLAYER_D) {
          if (level->characters[3].state == CHARACTER_HITTED)
            set_color_white();
          else
            set_color_green();
        }
        else if(cur_tile_content == TILE_WITH_BONUS_1) {
          set_color_cyan();
        }
        else if(cur_tile_content == TILE_WITH_BONUS_2) {
          set_color_cyan();
        }
        else if(cur_tile_content == TILE_WITH_BOMB
          || cur_tile_content == TILE_WITH_BOMB_EXP_DOWN
          || cur_tile_content == TILE_WITH_BOMB_EXP_UP
          || cur_tile_content == TILE_WITH_BOMB_EXP_LEFT
          || cur_tile_content == TILE_WITH_BOMB_EXP_RIGHT
          || cur_tile_content == TILE_WITH_BOMB_ORIGIN)
            set_color_red();
         else if(cur_tile_content == ' ') {
           set_color_black();
         }
         else {
           set_color_light_gray();
         }
        write(1, cur_tile_content, 1);
    }
    write(1, "\n", strlen("\n"));

  }
  set_color_normal();
}

void display_screen(t_game_data *game_data) {
  display_hud(game_data);
  display_level(game_data);
}
