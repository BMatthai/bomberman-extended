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

#include "game_constants.h"
#include "game_manager.h"
#include "level_generation.h"
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

#include <poll.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

t_display *init_display(t_level *level) {
  t_display *display;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow("Bomberman",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, STANDARD_WIN_WIDTH, STANDARD_WIN_HEIGHT, 0);

  Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;



  int offset_x = ((STANDARD_WIN_WIDTH / 2) - ((level->columns * STANDARD_TILE_WIDTH) / 2));
  int offset_y = STANDARD_WIN_HEIGHT - (level->lines * STANDARD_TILE_HEIGHT);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, render_flags);

  SDL_Texture **text_terrain = malloc(2 * sizeof(SDL_Texture *));
  SDL_Texture **text_bomb = malloc(4 * sizeof(SDL_Texture *));
  SDL_Texture **text_character = malloc(1 * sizeof(SDL_Texture *));

  SDL_Surface *image_wall = SDL_LoadBMP("resources/wall.bmp");
  SDL_Surface *image_free = SDL_LoadBMP("resources/free.bmp");

  SDL_Surface *image_char0 = SDL_LoadBMP("resources/char0.bmp");
  SDL_Surface *image_char1 = SDL_LoadBMP("resources/char1.bmp");
  SDL_Surface *image_char2 = SDL_LoadBMP("resources/char2.bmp");
  SDL_Surface *image_char3 = SDL_LoadBMP("resources/char3.bmp");

  SDL_Surface *image_bomb0 = SDL_LoadBMP("resources/bomb0.bmp");
  SDL_Surface *image_bomb1 = SDL_LoadBMP("resources/bomb1.bmp");

  text_terrain[0] = SDL_CreateTextureFromSurface(renderer, image_wall);
  text_terrain[1] = SDL_CreateTextureFromSurface(renderer, image_free);

  text_character[0] = SDL_CreateTextureFromSurface(renderer, image_char0);
  text_character[1] = SDL_CreateTextureFromSurface(renderer, image_char1);
  text_character[2] = SDL_CreateTextureFromSurface(renderer, image_char2);
  text_character[3] = SDL_CreateTextureFromSurface(renderer, image_char3);

  text_bomb[0] = SDL_CreateTextureFromSurface(renderer, image_bomb0);
  text_bomb[1] = SDL_CreateTextureFromSurface(renderer, image_bomb1);

  display = malloc(sizeof(t_display));
  display->window = window;
  display->renderer = renderer;
  display->offset_x = offset_x;
  display->offset_y = offset_y;
  display->text_terrain = text_terrain;
  display->text_character = text_character;
  display->text_bomb = text_bomb;

  return display;
}

void display_map(t_level *level, t_display *display) {
  SDL_Rect location;

  for (int i = 0; i < level->lines; i++) {
    for (int j = 0; j < level->columns; j++) {
      location.h = STANDARD_TILE_HEIGHT;
      location.w = STANDARD_TILE_WIDTH;
      location.x = STANDARD_TILE_WIDTH * j + display->offset_x;
      location.y = STANDARD_TILE_HEIGHT * i + display->offset_y;

      if (is_tile_wall(level, j, i) == YES) {
        SDL_RenderCopy(display->renderer, display->text_terrain[0], NULL, &location);
      }
      else {
        SDL_RenderCopy(display->renderer, display->text_terrain[1], NULL, &location);
      }
    }
  }
}

void display_characters(t_level *level, t_display *display) {
  SDL_Rect location;

  t_character character;

  for (int i = 0; i < 4; i++) {
    character = level->characters[i];

    location.h = STANDARD_TILE_HEIGHT;
    location.w = STANDARD_TILE_WIDTH;
    location.x = STANDARD_TILE_WIDTH * character.position_x + display->offset_x;
    location.y = STANDARD_TILE_HEIGHT * character.position_y + display->offset_y;

    SDL_RenderCopy(display->renderer, display->text_character[i], NULL, &location);
  }
}

void display_bombs(t_level *level, t_display *display) {
  SDL_Rect location;

  for (int i = 0; i < level->lines; i++) {
    for (int j = 0; j < level->columns; j++) {
      location.h = STANDARD_TILE_HEIGHT;
      location.w = STANDARD_TILE_WIDTH;
      location.x = STANDARD_TILE_WIDTH * j + display->offset_x;
      location.y = STANDARD_TILE_HEIGHT * i + display->offset_y;

      if (is_tile_bomb_exploding(level, j, i) == YES) {
        SDL_RenderCopy(display->renderer, display->text_bomb[1], NULL, &location);
      }
      else if (is_tile_bomb_planted(level, j, i) == YES){
        SDL_RenderCopy(display->renderer, display->text_bomb[0], NULL, &location);
      }
    }
  }
}

int game_state(t_game_data *game_data) {
  if(game_data->playable_character->heal_points < CHARACTER_ALIVE) {
      return GAME_PLAYABLE_CHARACTER_IS_DEAD;
  }
  else if (game_data->level->characters[1].state == CHARACTER_DEAD && game_data->level->characters[2].state == CHARACTER_DEAD && game_data->level->characters[3].state == CHARACTER_DEAD) {
    return GAME_IS_WON;
  }
return GAME_IS_RUNNING;
}

int launch_game_SDL() {

  SDL_Event event;

  t_game_data *game_data = NULL;
  game_data = malloc(sizeof(t_game_data));
  if (game_data == NULL) {
   return -1;
  }
  game_data->level = generate_level_from_file("./level/testlevel.lvl");
  game_data->playable_character = &game_data->level->characters[0];
  t_character *playable_character = game_data->playable_character;

  t_level *level = game_data->level;
  int lines = level->lines;
  int columns = level->columns;

  int is_running = YES;
  int offset_x = ((STANDARD_WIN_WIDTH / 2) - ((columns * STANDARD_TILE_WIDTH) / 2));
  int offset_y = STANDARD_WIN_HEIGHT - (lines * STANDARD_TILE_HEIGHT);

  int time_to_reload = get_time();

  t_display *display = init_display(level);


  while (is_running)
  {
    SDL_PollEvent(&event);

    switch (event.type)
    {
      case SDL_QUIT:
        is_running = NO;
        break;
      case SDL_KEYDOWN:
          switch (event.key.keysym.sym)
          {
              case SDLK_LEFT:  action(level, playable_character, ACTION_LEFT); break;
              case SDLK_RIGHT: action(level, playable_character, ACTION_RIGHT); break;
              case SDLK_UP:    action(level, playable_character, ACTION_UP); break;
              case SDLK_DOWN:  action(level, playable_character, ACTION_DOWN); break;
              case SDLK_c:  action(level, playable_character, ACTION_BOMB); break;
          }
        break;
      case SDL_KEYUP: adjust_char(level, playable_character); break;
    }

    SDL_RenderClear(display->renderer);
    display_map(level, display);
    display_characters(level, display);
    display_bombs(level, display);
    SDL_RenderPresent(display->renderer);

  }

  SDL_DestroyTexture(display->text_terrain[0]);
  SDL_DestroyTexture(display->text_terrain[1]);

  SDL_DestroyRenderer(display->renderer);
  SDL_DestroyWindow(display->window);

  SDL_Quit();

  return 0;
}
