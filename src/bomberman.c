
#ifndef T_DISPLAY
#define T_DISPLAY
#include "../include/struct_display.h"
#endif

#ifndef T_SETTINGS
#define T_SETTINGS
#include "../include/struct_game_settings.h"
#endif

#include "../include/textures_repertory.h"

#include "../include/game_constants.h"
#include "../include/game_manager.h"

#include "../include/menu_manager.h"

#include "../include/display_menu.h"
#include  "../include/init_display.h"
#include "../include/test.h"

#include <string.h>
#include <signal.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void init_menu(t_display *display) {
  t_text_display **text_menu = NULL;

  text_menu = malloc(sizeof(t_text_display *) * 11);

  text_menu[TEXT_MENU_MONOPLAYER] = create_text_display(display, "Monojoueur");
  text_menu[TEXT_MENU_MULTIPLAYER] = create_text_display(display, "Multijoueur");
  text_menu[TEXT_MENU_QUIT] = create_text_display(display, "Quitter");
  text_menu[TEXT_MENU_SELECTOR_LEFT] = create_text_display(display, ">");
  text_menu[TEXT_MENU_SELECTOR_RIGHT] = create_text_display(display, "<");
  text_menu[TEXT_MENU_TILE_DESTRUCTIBLE_STR] = create_text_display(display, "% de cases destructible : ");
  text_menu[TEXT_MENU_TILE_EMPTY_STR] = create_text_display(display, "% de cases libres libre : ");
  text_menu[TEXT_MENU_MAP_WIDTH_STR] = create_text_display(display, "Largeur map : ");
  text_menu[TEXT_MENU_MAP_HEIGHT_STR] = create_text_display(display, "Hauteur map : ");
  text_menu[TEXT_MENU_NUMBER_PLAYERS] = create_text_display(display, "Nombre de joueurs (ordinateur)");
  text_menu[TEXT_MENU_BACK] = create_text_display(display, "Retour");

  display->theme->text_menu = text_menu;
}

void init_terrain(t_display *display) {
  t_text_display **text_terrain = NULL;

  text_terrain = malloc(sizeof(t_text_display *) * 14);

  text_terrain[TEXT_TERRAIN_0] = create_graphic_display(display, "./resources/env_wall_0.bmp");
  text_terrain[TEXT_TERRAIN_1] = create_graphic_display(display, "./resources/env_wall_1.bmp");
  text_terrain[TEXT_TERRAIN_2] = create_graphic_display(display, "./resources/env_wall_2.bmp");
  text_terrain[TEXT_TERRAIN_3] = create_graphic_display(display, "./resources/env_wall_3.bmp");
  text_terrain[TEXT_TERRAIN_4] = create_graphic_display(display, "./resources/env_wall_4.bmp");
  text_terrain[TEXT_TERRAIN_5] = create_graphic_display(display, "./resources/env_wall_5.bmp");
  text_terrain[TEXT_TERRAIN_6] = create_graphic_display(display, "./resources/env_wall_6.bmp");
  text_terrain[TEXT_TERRAIN_7] = create_graphic_display(display, "./resources/env_wall_7.bmp");
  text_terrain[TEXT_TERRAIN_8] = create_graphic_display(display, "./resources/env_wall_8.bmp");
  text_terrain[TEXT_TERRAIN_9] = create_graphic_display(display, "./resources/env_wall_9.bmp");
  text_terrain[TEXT_TERRAIN_EMPTY] = create_graphic_display(display, "./resources/env_free.bmp");
  text_terrain[TEXT_TERRAIN_OUTSIDE_0] = create_graphic_display(display, "./resources/env_outside_0.bmp");
  text_terrain[TEXT_TERRAIN_OUTSIDE_1] = create_graphic_display(display, "./resources/env_outside_1.bmp");
  text_terrain[TEXT_TERRAIN_OUTSIDE_2] = create_graphic_display(display, "./resources/env_outside_2.bmp");

  display->theme->text_terrain = text_terrain;

}

void init_characters(t_display *display) {
  t_text_display **text_character = NULL;

  text_character = malloc(sizeof(t_text_display *) * 11);

  text_character[TEXT_CHARACTER_0] = create_graphic_display(display, "./resources/char_0.bmp");
  text_character[TEXT_CHARACTER_1] = create_graphic_display(display, "./resources/char_1.bmp");
  text_character[TEXT_CHARACTER_2] = create_graphic_display(display, "./resources/char_2.bmp");
  text_character[TEXT_CHARACTER_3] = create_graphic_display(display, "./resources/char_3.bmp");

  display->theme->text_character = text_character;
}

void init_bombs(t_display *display) {
  t_text_display **text_bomb = NULL;

  // 11 ?? Pourquoi pas 4 ?
  text_bomb = malloc(sizeof(t_text_display *) * 11);

  text_bomb[TEXT_BOMB_PLANTED] = create_graphic_display(display, "./resources/bomb_planted.bmp");
  text_bomb[TEXT_BOMB_UNSTABLE] = create_graphic_display(display, "./resources/bomb_unstable.bmp");
  text_bomb[TEXT_BOMB_EXP_0] = create_graphic_display(display, "./resources/bomb_exp_0.bmp");
  text_bomb[TEXT_BOMB_EXP_1] = create_graphic_display(display, "./resources/bomb_exp_1.bmp");

  display->theme->text_bomb = text_bomb;
}

void init_misc(t_display *display) {

  t_text_display **text_misc = NULL;

  text_misc = malloc(sizeof(t_text_display *) * 4);

  SDL_Color redColor = {255, 0, 0, 0};
  text_misc[TEXT_MISC_LIFE_GAUGE] = create_color_display(display, redColor);

  display->theme->text_misc = text_misc;

}

void init_default_theme(t_display *display) {
  t_theme_display *theme = NULL;

  theme = malloc(sizeof(t_theme_display));

  init_menu(display);
  init_terrain(display);
  init_characters(display);
  init_bombs(display);
  init_misc(display);

}

t_display *init_window() {

  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  SDL_Window *window = SDL_CreateWindow("Bomberman",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, STANDARD_WIN_WIDTH, STANDARD_WIN_HEIGHT, 0);
  Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

  SDL_Renderer *renderer = NULL;
  TTF_Font *font = NULL;

  renderer = SDL_CreateRenderer(window, -1, render_flags);
  font = TTF_OpenFont("./resources/fonts/OpenSans-Light.ttf", STANDARD_MENU_LETTERING_SIZE);

  if(!font) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
  }

  // SDL_Color white = {255, 255, 255, 255};

  // SDL_Texture **text_terrain = malloc(4 * sizeof(SDL_Texture *));
  // SDL_Texture **text_bomb = malloc(4 * sizeof(SDL_Texture *));
  // SDL_Texture **text_character = malloc(4 * sizeof(SDL_Texture *));
  //
  // SDL_Texture *text_blizzard = malloc(sizeof(SDL_Texture *));
  // SDL_Texture *text_red = malloc(sizeof(SDL_Texture *));
  //
  // t_text_display **text_main_menu = malloc(5 * sizeof(t_text_display *));
  // t_text_display **text_settings_menu = malloc(4 * sizeof(t_text_display *));
  //

  // SDL_Surface *surfaceBlizzard =  SDL_CreateRGBSurface(0, STANDARD_WIN_WIDTH, STANDARD_WIN_HEIGHT, 32, 0, 0, 0, 0);

  // text_terrain[0] = SDL_CreateTextureFromSurface(renderer, image_free);
  // text_terrain[1] = SDL_CreateTextureFromSurface(renderer, image_wall);
  // text_terrain[2] = SDL_CreateTextureFromSurface(renderer, image_destr);
  // text_terrain[3] = SDL_CreateTextureFromSurface(renderer, image_misc);
  //
  // text_character[0] = SDL_CreateTextureFromSurface(renderer, image_char0);
  // text_character[1] = SDL_CreateTextureFromSurface(renderer, image_char1);
  // text_character[2] = SDL_CreateTextureFromSurface(renderer, image_char2);
  // text_character[3] = SDL_CreateTextureFromSurface(renderer, image_char3);
  //
  // text_bomb[0] = SDL_CreateTextureFromSurface(renderer, image_bomb0);
  // text_bomb[1] = SDL_CreateTextureFromSurface(renderer, image_bomb1);
  // text_bomb[2] = SDL_CreateTextureFromSurface(renderer, image_bomb2);
  // text_bomb[3] = SDL_CreateTextureFromSurface(renderer, image_bomb3);

  // t_text_display **text_main_menu;
  // t_text_display **text_settings_menu;

  // SDL_FillRect(surfaceBlizzard, NULL, SDL_MapRGBA(surfaceBlizzard->format, 0, 0, 255, 0));
  // SDL_FillRect(surfaceRed, NULL, SDL_MapRGBA(surfaceRed->format, 255, 0, 0, 0));

  // text_red = SDL_CreateTextureFromSurface(renderer, surfaceRed);
  // text_blizzard = SDL_CreateTextureFromSurface(renderer, surfaceBlizzard);

  t_display *display = NULL;

  display = malloc(sizeof(t_display));
  display->window = window;
  display->renderer = renderer;
  display->font = font;
  init_default_theme(display);

  return display;
}

t_game_settings *random_settings() {
  t_game_settings *game_settings = NULL;

  game_settings = malloc(sizeof(t_game_settings));

  int width = (rand() % (64 - 4 + 1)) + 4;
  int height = (rand() % (48 - 4 + 1)) + 4;
  int proba_destr_wall = (rand() % (100 - 0 + 1)) + 0;
  int proba_empty = (rand() % (100 - proba_destr_wall + 1)) + proba_destr_wall;

  game_settings->width = width;
  game_settings->height = height;
  game_settings->proba_destr_wall = proba_destr_wall;
  game_settings->proba_empty = proba_empty;

  return game_settings;
}

void go_to_selected(t_display *display, int selected) {
  if (selected == MENU_MONOPLAYER) {
    launch_settings_menu(display);
  }
}

// void release_memory_display(t_display *display) {
//   SDL_Texture *texture;
//   int recommended_w;
//   int recommended_h;
// } t_text_display;
//
// typedef struct s_theme_display {
//   struct s_text_display **text_menu;
//   struct s_text_display **text_terrain;
//   struct s_text_display **text_bomb;
//   struct s_text_display **text_character;
//   struct s_text_display **text_misc;
//   // struct s_text_display **text_blizzard;
//   // struct s_text_display **text_red;
//
// } t_theme_display;
//
// typedef struct s_display {
//   SDL_Window *window;
//   SDL_Renderer *renderer;
//   TTF_Font *font;
//   int offset_x;
//   int offset_y;
//   struct s_theme_display *theme;
// }

int main() {

  // test_procedure();
  t_display *display = NULL;
  display = init_window();

  launch_main_menu(display);
  SDL_DestroyWindow(display->window);
  SDL_Quit();
  return 0;
}
