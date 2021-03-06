#ifndef T_DISPLAY
#define T_DISPLAY
#include "../include/struct_display.h"
#endif

#ifndef T_LEVEL
#define T_LEVEL
#include "../include/struct_level.h"
#endif

#ifndef T_GAME_DATA
#define T_GAME_DATA
#include "../include/struct_game_data.h"
#endif

#ifndef T_SETTINGS
#define T_SETTINGS
#include "../include/struct_game_settings.h"
#endif


#include "../include/game_constants.h"
#include "../include/game_manager.h"
#include "../include/time_manager.h"
#include "../include/action.h"
#include "../include/action.h"
#include "../include/game_constants.h"
#include "../include/bomb_manager.h"
#include "../include/game_manager.h"
#include "../include/character_creation.h"
#include "../include/tile_manager.h"
#include "../include/time_manager.h"
#include "../include/log_manager.h"
#include "../include/maze_generation.h"
#include "../include/display_game.h"
#include "../include/menu_manager.h"

#include <poll.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int game_state(t_game_data *game_data) {
  if (game_data->playable_character->heal_points < CHARACTER_ALIVE)
      return GAME_PLAYABLE_CHARACTER_IS_DEAD;
  else if (game_data->level->characters[1].state == CHARACTER_DEAD &&
    game_data->level->characters[2].state == CHARACTER_DEAD &&
    game_data->level->characters[3].state == CHARACTER_DEAD)
    return GAME_IS_WON;
  return GAME_IS_RUNNING;
}

// void free_game_memory(t_game_data *game_data) {
//   free(game_data->playable_character);
//   free(ga)
//   t_level *level;
//   Uint32 elapsed_time;
//
// }

void refresh(t_game_data *game_data, t_display *display) {
 t_level *level = game_data->level;


  SDL_RenderClear(display->renderer);

  display_map(level, display);
  display_bonus(level, display);
  display_characters(level, display);
  display_bombs(level, display);
  display_hud(game_data, display);
  // display_misc(game_data, display);
  SDL_RenderPresent(display->renderer);
}

// void pick_bonus_char(t_level *level) {
//   for (int i = 0; i < level->number_characters; i++) {
//     pick_item(t_level *level, t_character *character)
//   }
// }

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
  // int offset_y = ((STANDARD_WIN_HEIGHT / 2) - ((height * STANDARD_TILE_HEIGHT) / 2)) + STANDARD_HUD_HEIGHT + (STANDARD_TILE_HEIGHT / 2);
  int offset_y = ((STANDARD_WIN_HEIGHT / 2) - ((height * STANDARD_TILE_HEIGHT) / 2));
  // int offset_y = STANDARD_WIN_HEIGHT - (height * STANDARD_TILE_HEIGHT);

  display->offset_x = offset_x;
  display->offset_y = offset_y;

  unsigned int time_start = get_time();
  // SDL_RenderClear(display->renderer);

  // display_outside(display);
  unsigned int time_refresh = get_time();

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
    move_char(level, character);
    motion_char(level, character);

    if (get_time() - time_refresh > 20) {
      check_bombs_timer(level);
      refresh(game_data, display);
      time_refresh = get_time();
    }
  }

  free(game_data); //TODO Ensure each component of game_data is freed...
  launch_main_menu(display);

  return 0;
}
