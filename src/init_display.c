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
