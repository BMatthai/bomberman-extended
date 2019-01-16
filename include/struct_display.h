#ifndef T_SDL
#define T_SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif

typedef struct s_text_display {
  SDL_Texture *texture;
  int recommended_w;
  int recommended_h;
} t_text_display;

typedef struct s_theme_display {
  t_text_display **text_menu;
  t_text_display **text_terrain;
  t_text_display **text_bomb;
  t_text_display **text_character;
  t_text_display **text_blizzard;
  t_text_display **text_red;
} t_theme_display;

typedef struct s_display {
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;
  int offset_x;
  int offset_y;
  t_theme_display *theme;
}   t_display;
