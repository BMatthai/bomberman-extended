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


t_display *init_display(t_level *level) {
  t_display *display;

  SDL_Init(SDL_INIT_VIDEO);

  // *police = NULL; //initialisation de la police
  //TTF_Init(); //initialisation de ttf
  // police = TTF_OpenFont("ta_police.ttf", 15); //déclare la police
  // TTF_SetFontStyle(police, TTF_STYLE_BOLD); //On gère la police
  // SDL_Color couleurBlanc = {255, 255, 255}; //La couleur
  // SDL_Surface *texte = {NULL}; //la surface de la police
  // SDL_Rect position_texte = {NULL}; //La position de la police
  // texte = TTF_RenderText_Solid(police, "Hello", couleurBlanc); //on dit le texte
  // SDL_BlitSurface(texte, NULL, ecran, &position_texte); // On blite la surface
  // SDL_FreeSurface(texte); //libère la surface du texte
  // TTF_CloseFont(police); //libère la police
  // TTF_Quit(); //on quitte sdl_ttf

  SDL_Window *window = SDL_CreateWindow("Bomberman",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, STANDARD_WIN_WIDTH, STANDARD_WIN_HEIGHT, 0);

  Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

  int offset_x = ((STANDARD_WIN_WIDTH / 2) - ((level->width * STANDARD_TILE_WIDTH) / 2));
  int offset_y = STANDARD_WIN_HEIGHT - (level->height * STANDARD_TILE_HEIGHT);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, render_flags);

  SDL_Texture **text_terrain = malloc(4 * sizeof(SDL_Texture *));
  SDL_Texture **text_bomb = malloc(4 * sizeof(SDL_Texture *));
  SDL_Texture **text_character = malloc(1 * sizeof(SDL_Texture *));

  SDL_Surface *image_free = SDL_LoadBMP("resources/free.bmp");
  SDL_Surface *image_wall = SDL_LoadBMP("resources/wall.bmp");
  SDL_Surface *image_destr = SDL_LoadBMP("resources/destructible.bmp");
  SDL_Surface *image_misc = SDL_LoadBMP("resources/misc.bmp");

  SDL_Surface *image_char0 = SDL_LoadBMP("resources/char0.bmp");
  SDL_Surface *image_char1 = SDL_LoadBMP("resources/char1.bmp");
  SDL_Surface *image_char2 = SDL_LoadBMP("resources/char2.bmp");
  SDL_Surface *image_char3 = SDL_LoadBMP("resources/char3.bmp");

  SDL_Surface *image_bomb0 = SDL_LoadBMP("resources/bomb0.bmp");
  SDL_Surface *image_bomb1 = SDL_LoadBMP("resources/bomb1.bmp");
  SDL_Surface *image_bomb2 = SDL_LoadBMP("resources/bomb2.bmp");
  SDL_Surface *image_bomb3 = SDL_LoadBMP("resources/bomb2b.bmp");

  text_terrain[0] = SDL_CreateTextureFromSurface(renderer, image_free);
  text_terrain[1] = SDL_CreateTextureFromSurface(renderer, image_wall);
  text_terrain[2] = SDL_CreateTextureFromSurface(renderer, image_destr);
  text_terrain[3] = SDL_CreateTextureFromSurface(renderer, image_misc);

  text_character[0] = SDL_CreateTextureFromSurface(renderer, image_char0);
  text_character[1] = SDL_CreateTextureFromSurface(renderer, image_char1);
  text_character[2] = SDL_CreateTextureFromSurface(renderer, image_char2);
  text_character[3] = SDL_CreateTextureFromSurface(renderer, image_char3);

  text_bomb[0] = SDL_CreateTextureFromSurface(renderer, image_bomb0);
  text_bomb[1] = SDL_CreateTextureFromSurface(renderer, image_bomb1);
  text_bomb[2] = SDL_CreateTextureFromSurface(renderer, image_bomb2);
  text_bomb[3] = SDL_CreateTextureFromSurface(renderer, image_bomb3);

  display = malloc(sizeof(t_display));
  display->window = window;
  display->renderer = renderer;
  display->offset_x = offset_x;
  display->offset_y = offset_y;
  display->text_bomb = text_bomb;
  display->text_terrain = text_terrain;
  display->text_character = text_character;

  return display;
}

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

    location.h = STANDARD_TILE_HEIGHT;
    location.w = STANDARD_TILE_WIDTH;
    location.x = STANDARD_TILE_WIDTH * character.position_x + display->offset_x;
    location.y = STANDARD_TILE_HEIGHT * character.position_y + display->offset_y;

    SDL_RenderCopy(display->renderer, display->text_character[i], NULL, &location);
  }
}

void display_misc(t_level *level, t_display *display) {

  TTF_Font *font = NULL;

  font = TTF_OpenFont("Arial.ttf", 50); //this opens a font style and sets a size

  SDL_Color White = {255, 34, 34};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "put your text here", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

  SDL_Texture* Message = SDL_CreateTextureFromSurface(display->renderer, surfaceMessage); //now you can convert it into a texture

  SDL_Rect Message_rect; //create a rect
  Message_rect.x = 0;  //controls the rect's x coordinate
  Message_rect.y = 0; // controls the rect's y coordinte
  Message_rect.w = 100; // controls the width of the rect
  Message_rect.h = 100; // controls the height of the rect

  // Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

  // Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

 SDL_RenderCopy(display->renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

  // Don't forget too free your surface and texture
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
  t_character *playable_character = game_data->playable_character;

  t_level *level = game_data->level;

  int is_running = YES;
  int offset_x = ((STANDARD_WIN_WIDTH / 2) - ((width * STANDARD_TILE_WIDTH) / 2));
  int offset_y = STANDARD_WIN_HEIGHT - (height * STANDARD_TILE_HEIGHT);

  //t_display *display = init_display(level);

  while (is_running)
  {
    while (SDL_PollEvent(&event)) {
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
              case SDLK_ESCAPE: is_running = NO; break;
          }
        break;
      case SDL_KEYUP: adjust_char(level, playable_character); break;
    }

    SDL_RenderClear(display->renderer);
    display_map(level, display);
    display_characters(level, display);
    display_bombs(level, display);
    // display_misc(level, display);
    SDL_RenderPresent(display->renderer);

    check_bombs_timer(level);

  }

  SDL_DestroyTexture(display->text_terrain[0]);
  SDL_DestroyTexture(display->text_terrain[1]);

  SDL_DestroyRenderer(display->renderer);
  SDL_DestroyWindow(display->window);

  SDL_Quit();

  return 0;
}
return 0;
}
