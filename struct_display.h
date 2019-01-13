#ifndef T_SDL
#define T_SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif



typedef struct s_display {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture **text_terrain;
  SDL_Texture **text_bomb;
  SDL_Texture **text_character;
  SDL_Texture **text_main_menu;
  SDL_Texture **text_settings_menu;
  SDL_Texture *text_blizzard;
  SDL_Texture *text_red;
  TTF_Font *font;
  int offset_x;
  int offset_y;
}   t_display;
