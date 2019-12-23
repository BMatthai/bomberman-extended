#ifndef T_LEVEL
#define T_LEVEL
#include "../include/struct_level.h"
#endif

#ifndef T_DISPLAY
#define T_DISPLAY
#include "../include/struct_display.h"
#endif

#ifndef T_GAME_DATA
#define T_GAME_DATA
#include "../include/struct_game_data.h"
#endif

#include "../include/init_display.h"
#include "../include/game_constants.h"
#include "../include/textures_repertory.h"

t_text_display *create_text_display(t_display *display, char *str) {
  t_text_display *text = NULL;

  SDL_Color white = {255, 255, 255, 255};

  text = malloc(sizeof(t_text_display));
  TTF_SizeText(display->font, str, &text->recommended_w, &text->recommended_h);

  SDL_Surface *surface= TTF_RenderText_Solid(display->font, str, white);
  text->texture = SDL_CreateTextureFromSurface(display->renderer, surface);

  return text;
}

t_text_display *create_graphic_display(t_display *display, char *path) {
  t_text_display *text = NULL;
  text = malloc(sizeof(t_text_display));

  SDL_Surface *surface = SDL_LoadBMP(path);
  text->texture = SDL_CreateTextureFromSurface(display->renderer, surface);

  return text;
}

t_text_display *create_color_display(t_display *display, SDL_Color color) {
  t_text_display *text = NULL;
  text = malloc(sizeof(t_text_display));
  SDL_Surface *surface =  SDL_CreateRGBSurface(0, STANDARD_LIFE_GAUGE_WIDTH, STANDARD_LIFE_GAUGE_WIDTH, 32, 0, 0, 0, 0);
  SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
  text->texture = SDL_CreateTextureFromSurface(display->renderer, surface);

  return text;
}

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
  text_menu[TEXT_MENU_NUMBER_PLAYERS] = create_text_display(display, "Nombre de joueurs (IA) : ");
  text_menu[TEXT_MENU_BACK] = create_text_display(display, "Retour");

  display->theme->text_menu = text_menu;
}

void init_terrain(t_display *display) {
  t_text_display **text_terrain = NULL;

  text_terrain = malloc(sizeof(t_text_display *) * 14);

  text_terrain[TEXT_TERRAIN_0] = create_graphic_display(display, "./resources/env/env_wall_0.bmp");
  text_terrain[TEXT_TERRAIN_1] = create_graphic_display(display, "./resources/env/env_wall_1.bmp");
  text_terrain[TEXT_TERRAIN_2] = create_graphic_display(display, "./resources/env/env_wall_2.bmp");
  text_terrain[TEXT_TERRAIN_3] = create_graphic_display(display, "./resources/env/env_wall_3.bmp");
  text_terrain[TEXT_TERRAIN_4] = create_graphic_display(display, "./resources/env/env_wall_4.bmp");
  text_terrain[TEXT_TERRAIN_5] = create_graphic_display(display, "./resources/env/env_wall_5.bmp");
  text_terrain[TEXT_TERRAIN_6] = create_graphic_display(display, "./resources/env/env_wall_6.bmp");
  text_terrain[TEXT_TERRAIN_7] = create_graphic_display(display, "./resources/env/env_wall_7.bmp");
  text_terrain[TEXT_TERRAIN_8] = create_graphic_display(display, "./resources/env/env_wall_8.bmp");
  text_terrain[TEXT_TERRAIN_9] = create_graphic_display(display, "./resources/env/env_wall_9.bmp");
  text_terrain[TEXT_TERRAIN_EMPTY] = create_graphic_display(display, "./resources/env/env_free.bmp");
  text_terrain[TEXT_TERRAIN_OUTSIDE_0] = create_graphic_display(display, "./resources/env/env_outside_0.bmp");
  text_terrain[TEXT_TERRAIN_OUTSIDE_1] = create_graphic_display(display, "./resources/env/env_outside_1.bmp");
  text_terrain[TEXT_TERRAIN_OUTSIDE_2] = create_graphic_display(display, "./resources/env/env_outside_2.bmp");

  display->theme->text_terrain = text_terrain;

}

void init_characters(t_display *display) {
  t_text_display **text_character = NULL;

  text_character = malloc(sizeof(t_text_display *) * 16);

  text_character[TEXT_CHARACTER_0] = create_graphic_display(display, "./resources/char/0.bmp");
  text_character[TEXT_CHARACTER_1] = create_graphic_display(display, "./resources/char/1.bmp");
  text_character[TEXT_CHARACTER_2] = create_graphic_display(display, "./resources/char/2.bmp");
  text_character[TEXT_CHARACTER_3] = create_graphic_display(display, "./resources/char/3.bmp");
  text_character[TEXT_CHARACTER_4] = create_graphic_display(display, "./resources/char/4.bmp");
  text_character[TEXT_CHARACTER_5] = create_graphic_display(display, "./resources/char/5.bmp");
  text_character[TEXT_CHARACTER_6] = create_graphic_display(display, "./resources/char/6.bmp");
  text_character[TEXT_CHARACTER_7] = create_graphic_display(display, "./resources/char/7.bmp");
  text_character[TEXT_CHARACTER_8] = create_graphic_display(display, "./resources/char/8.bmp");
  text_character[TEXT_CHARACTER_9] = create_graphic_display(display, "./resources/char/9.bmp");
  text_character[TEXT_CHARACTER_10] = create_graphic_display(display, "./resources/char/10.bmp");
  text_character[TEXT_CHARACTER_11] = create_graphic_display(display, "./resources/char/11.bmp");
  text_character[TEXT_CHARACTER_12] = create_graphic_display(display, "./resources/char/12.bmp");
  text_character[TEXT_CHARACTER_13] = create_graphic_display(display, "./resources/char/13.bmp");
  text_character[TEXT_CHARACTER_14] = create_graphic_display(display, "./resources/char/14.bmp");
  text_character[TEXT_CHARACTER_15] = create_graphic_display(display, "./resources/char/15.bmp");

  display->theme->text_character = text_character;
}

void init_bonus(t_display *display) {
  t_text_display **text_bonus = NULL;

  text_bonus = malloc(sizeof(t_text_display *) * 5);

  text_bonus[TEXT_BONUS_EXTRA_BOMB] = create_graphic_display(display, "./resources/bonus/extra_bomb.bmp");
  text_bonus[TEXT_BONUS_DAMAGE] = create_graphic_display(display, "./resources/bonus/damage.bmp");
  text_bonus[TEXT_BONUS_BOOTS] = create_graphic_display(display, "./resources/bonus/boots.bmp");
  text_bonus[TEXT_BONUS_RANGE] = create_graphic_display(display, "./resources/bonus/range.bmp");
  text_bonus[TEXT_BONUS_HEAL] = create_graphic_display(display, "./resources/bonus/heal.bmp");

  display->theme->text_bonus = text_bonus;
}

void init_bombs(t_display *display) {
  t_text_display **text_bomb = NULL;

  text_bomb = malloc(sizeof(t_text_display *) * 4);

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
  init_bonus(display);
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
  t_display *display = NULL;

  display = malloc(sizeof(t_display));
  display->window = window;
  display->renderer = renderer;
  display->font = font;
  init_default_theme(display);

  return display;
}
