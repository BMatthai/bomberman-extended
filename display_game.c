#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif

#ifndef T_DISPLAY
#define T_DISPLAY
#include "struct_display.h"
#endif

#ifndef T_GAME_DATA
#define T_GAME_DATA
#include "struct_game_data.h"
#endif

#include "display_game.h"
#include "game_constants.h"
#include "tile_manager.h"

void display_map(t_level *level, t_display *display) {
  SDL_Rect location;
  char cur_tile;
  char **terrain = NULL;

  terrain = level->terrain;

  for (int i = 0; i < level->height; i++) {
    for (int j = 0; j < level->width; j++) {
        location.h = STANDARD_TILE_HEIGHT;
        location.w = STANDARD_TILE_WIDTH;
        location.x = STANDARD_TILE_WIDTH * j + display->offset_x;
        location.y = STANDARD_TILE_HEIGHT * i + display->offset_y;

        cur_tile = terrain[j][i];
        if (cur_tile == ' ')
          SDL_RenderCopy(display->renderer, display->text_terrain[0], NULL, &location);
        if (cur_tile == '0')
          SDL_RenderCopy(display->renderer, display->text_terrain[1], NULL, &location);
        if (cur_tile == '1')
          SDL_RenderCopy(display->renderer, display->text_terrain[2], NULL, &location);
    }
  }
}

void display_background(t_level *level, t_display *display) {
  SDL_Rect location;

  for (int i = 0; i < STANDARD_WIN_HEIGHT / STANDARD_TILE_HEIGHT; i++) {
    for (int j = 0; j < STANDARD_WIN_WIDTH / STANDARD_TILE_WIDTH; j++) {
      location.h = STANDARD_TILE_HEIGHT;
      location.w = STANDARD_TILE_WIDTH;
      location.x = STANDARD_TILE_WIDTH * j;
      location.y = STANDARD_TILE_HEIGHT * i;

      SDL_RenderCopy(display->renderer, display->text_terrain[0], NULL, &location);
    }
  }
}

void display_characters(t_level *level, t_display *display) {
  SDL_Rect location;

  t_character character;

  for (int i = 0; i < 4; i++) {
    character = level->characters[i];

    if (character.state != CHARACTER_DEAD) {
      location.h = STANDARD_TILE_HEIGHT;
      location.w = STANDARD_TILE_WIDTH;
      location.x = STANDARD_TILE_WIDTH * character.position_x + display->offset_x;
      location.y = STANDARD_TILE_HEIGHT * character.position_y + display->offset_y;

      SDL_RenderCopy(display->renderer, display->text_character[i], NULL, &location);
    }

  }
}

void display_hud(t_game_data *game_data, t_display *display) {
  SDL_Rect location;

  location.h = STANDARD_LIFE_GAUGE_HEIGHT;
  location.w = game_data->playable_character->heal_points * (STANDARD_LIFE_GAUGE_WIDTH / CHARACTER_HEAL_POINT);
  location.x = (STANDARD_WIN_WIDTH / 2) - (STANDARD_LIFE_GAUGE_WIDTH / 2);
  location.y = (STANDARD_HUD_HEIGHT / 2) - (STANDARD_LIFE_GAUGE_HEIGHT / 2);

  SDL_RenderCopy(display->renderer, display->text_red, NULL, &location);
}

void display_misc(t_game_data *game_data, t_display *display) {
  Uint32 elapsed_time = (game_data->elapsed_time / DEFAULT_BLIZZARD_COOLDOWN) - DEFAULT_BLIZZARD_START;

  if (elapsed_time < 0) {
    return;
  }

  float ratio_wh = ((float) game_data->level->height / (float) game_data->level->width);

  SDL_Rect location;

  location.h = STANDARD_WIN_HEIGHT;
  location.w = STANDARD_WIN_WIDTH;

  location.x = -STANDARD_WIN_WIDTH + display->offset_x + elapsed_time;
  location.y = 0;

  SDL_RenderCopy(display->renderer, display->text_blizzard, NULL, &location);

  location.x = STANDARD_WIN_WIDTH - display->offset_x - elapsed_time;
  location.y = 0;

  SDL_RenderCopy(display->renderer, display->text_blizzard, NULL, &location);

  location.x = 0;
  location.y = -STANDARD_WIN_HEIGHT + display->offset_y + (elapsed_time * ratio_wh);

  SDL_RenderCopy(display->renderer, display->text_blizzard, NULL, &location);

  location.x = 0;
  location.y = STANDARD_WIN_HEIGHT - display->offset_y - (elapsed_time * ratio_wh);

  SDL_RenderCopy(display->renderer, display->text_blizzard, NULL, &location);
}

void display_bombs(t_level *level, t_display *display) {
  SDL_Rect location;

  t_bomb *cur_bomb = NULL;
  int pos_x;
  int pos_y;

  cur_bomb = level->first_bomb;

  while (cur_bomb != NULL) {
    pos_x = cur_bomb->position_x;
    pos_y = cur_bomb->position_y;

    location.h = STANDARD_TILE_HEIGHT;
    location.w = STANDARD_TILE_WIDTH;
    location.x = STANDARD_TILE_WIDTH * pos_x + display->offset_x;
    location.y = STANDARD_TILE_HEIGHT * pos_y + display->offset_y;

    if (cur_bomb->state == BOMB_IS_PLACED_ON_GROUND) {
      SDL_RenderCopy(display->renderer, display->text_bomb[0], NULL, &location);
    }
    else if (cur_bomb->state == BOMB_IS_UNSTABLE) {
      SDL_RenderCopy(display->renderer, display->text_bomb[1], NULL, &location);
    }
    else {
      SDL_RenderCopy(display->renderer, display->text_bomb[2], NULL, &location);
      for (int i = 1; i <= cur_bomb->range; i++) {
        if (is_tile_bomb_exploding(level, pos_x - i, pos_y) == YES) {
          location.h = STANDARD_TILE_HEIGHT;
          location.w = STANDARD_TILE_WIDTH;
          location.x = STANDARD_TILE_WIDTH * (pos_x - i) + display->offset_x;
          location.y = STANDARD_TILE_HEIGHT * pos_y + display->offset_y;
          if (i < cur_bomb->range) {
            SDL_RenderCopy(display->renderer, display->text_bomb[2], NULL, &location);
          }
          else {
            SDL_RenderCopyEx(display->renderer, display->text_bomb[3], NULL, &location, 0, 0, SDL_FLIP_NONE);
          }
        }
        if (is_tile_bomb_exploding(level, pos_x + i, pos_y) == YES) {
          location.h = STANDARD_TILE_HEIGHT;
          location.w = STANDARD_TILE_WIDTH;
          location.x = STANDARD_TILE_WIDTH * (pos_x + i) + display->offset_x;
          location.y = STANDARD_TILE_HEIGHT * pos_y + display->offset_y;
          if (i < cur_bomb->range) {
            SDL_RenderCopy(display->renderer, display->text_bomb[2], NULL, &location);
          }
          else {
            SDL_RenderCopyEx(display->renderer, display->text_bomb[3], NULL, &location, 180, 0, SDL_FLIP_NONE);
          }
        }
        if (is_tile_bomb_exploding(level, pos_x, pos_y - i) == YES) {
          location.h = STANDARD_TILE_HEIGHT;
          location.w = STANDARD_TILE_WIDTH;
          location.x = STANDARD_TILE_WIDTH * pos_x + display->offset_x;
          location.y = STANDARD_TILE_HEIGHT * (pos_y - i) + display->offset_y;
          if (i < cur_bomb->range) {
            SDL_RenderCopy(display->renderer, display->text_bomb[2], NULL, &location);
          }
          else {
            SDL_RenderCopyEx(display->renderer, display->text_bomb[3], NULL, &location, 90, 0, SDL_FLIP_NONE);
          }
        }
        if (is_tile_bomb_exploding(level, pos_x, pos_y + i) == YES) {
          location.h = STANDARD_TILE_HEIGHT;
          location.w = STANDARD_TILE_WIDTH;
          location.x = STANDARD_TILE_WIDTH * pos_x + display->offset_x;
          location.y = STANDARD_TILE_HEIGHT * (pos_y + i) + display->offset_y;
          if (i < cur_bomb->range) {
            SDL_RenderCopy(display->renderer, display->text_bomb[2], NULL, &location);
          }
          else {
            SDL_RenderCopyEx(display->renderer, display->text_bomb[3], NULL, &location, 270, 0, SDL_FLIP_NONE);
          }
        }
      }
    }
    cur_bomb = cur_bomb->next_bomb;
  }
}
