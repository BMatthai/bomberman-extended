#ifndef T_DISPLAY
#define T_DISPLAY
#include "struct_display.h"
#endif

#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif

#ifndef T_GAME_DATA
#define T_GAME_DATA
#include "struct_game_data.h"
#endif

#include "struct_game_settings.h"

#include "game_constants.h"
#include "game_manager.h"
// #include "level_generation.h"
#include "time_manager.h"
#include "action.h"
#include "level_generation.h"
#include "action.h"
#include "game_constants.h"
#include "bomb_manager.h"
#include "game_manager.h"
#include "character_creation.h"
#include "tile_manager.h"
#include "time_manager.h"
#include "log_manager.h"
#include "maze_generation.h"

#include <poll.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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

int game_state(t_game_data *game_data) {
  if (game_data->playable_character->heal_points < CHARACTER_ALIVE)
      return GAME_PLAYABLE_CHARACTER_IS_DEAD;
  else if (game_data->level->characters[1].state == CHARACTER_DEAD &&
    game_data->level->characters[2].state == CHARACTER_DEAD &&
    game_data->level->characters[3].state == CHARACTER_DEAD)
    return GAME_IS_WON;
  return GAME_IS_RUNNING;
}

void refresh(t_game_data *game_data, t_display *display, t_character *playable_character) {
  t_level *level = game_data->level;

  SDL_RenderClear(display->renderer);
  display_map(level, display);
  display_characters(level, display);
  display_bombs(level, display);
  display_hud(game_data, display);
  //display_misc(game_data, display);
  SDL_RenderPresent(display->renderer);
}

int launch_game(t_display *display, t_game_settings *game_settings) {

  SDL_Event event;

  t_game_data *game_data = NULL;
  game_data = malloc(sizeof(t_game_data));
  if (game_data == NULL) {
   return -1;
  }
  int width = game_settings->width;
  int height = game_settings->height;

  game_data->level = generate_maze_level(game_settings);

  game_data->playable_character = &game_data->level->characters[0];
  t_character *character = game_data->playable_character;

  t_level *level = game_data->level;

  int is_running = YES;
  int offset_x = ((STANDARD_WIN_WIDTH / 2) - ((width * STANDARD_TILE_WIDTH) / 2));
  int offset_y = ((STANDARD_WIN_HEIGHT / 2) - ((height * STANDARD_TILE_HEIGHT) / 2)) + STANDARD_HUD_HEIGHT;
  // int offset_y = STANDARD_WIN_HEIGHT - (height * STANDARD_TILE_HEIGHT);

  display->offset_x = offset_x;
  display->offset_y = offset_y;

  Uint32 time_start = get_time();
  Uint32 last_refresh = get_time();
  while (is_running)
  {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          is_running = NO;
          break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_LEFT: set_velocity_character(character, -1, 0); break;
                case SDLK_RIGHT: set_velocity_character(character, 1, 0); break;
                case SDLK_UP: set_velocity_character(character, 0, -1); break;
                case SDLK_DOWN: set_velocity_character(character, 0,  1); break;
                case SDLK_c: action(level, character, ACTION_BOMB); break;
                case SDLK_ESCAPE: is_running = NO; break;
            }
          break;
        case SDL_KEYUP:
          switch (event.key.keysym.sym)
          {
            case SDLK_LEFT: set_velocity_character(character, 0, 0); break;
            case SDLK_RIGHT: set_velocity_character(character, 0, 0); break;
            case SDLK_UP: set_velocity_character(character, 0, 0); break;
            case SDLK_DOWN: set_velocity_character(character, 0, 0); break;
          }
      }
    }

    game_data->elapsed_time = get_time() - time_start;
    check_bombs_timer(level);
    move_char(level, character);
    motion_char(level, character);

    refresh(game_data, display, character);

  }

  SDL_DestroyTexture(display->text_terrain[0]);
  SDL_DestroyTexture(display->text_terrain[1]);

  SDL_DestroyRenderer(display->renderer);
  SDL_DestroyWindow(display->window);

  SDL_Quit();

  return 0;
}
