#ifndef T_DISPLAY
#define T_DISPLAY
#include "../include/struct_display.h"
#endif

#ifndef T_SETTINGS
#define T_SETTINGS
#include "../include/struct_game_settings.h"
#endif


#include "../include/menu_manager.h"
#include "../include/game_manager.h"
#include "../include/game_constants.h"
#include "../include/display_menu.h"

void refresh_settings_menu(t_display *display, t_game_settings *settings, int selected) {
  SDL_RenderClear(display->renderer);
  display_settings_menu(display, settings, selected);
  SDL_RenderPresent(display->renderer);
}

void decrease(t_game_settings *settings, int selected) {
  switch (selected)
  {
    case 0:
      if (settings->width > 0) {
          settings->width--;
      }
      break;
    case 1:
      if (settings->height > 0)
        settings->height--;
      break;
    case 2:
      if (settings->proba_destr_wall >= 5)
        settings->proba_destr_wall -= 5;
      break;
    case 3:
      if (settings->proba_empty >= 5)
        settings->proba_empty -= 5;
      break;
    }
}

void increase(t_game_settings *settings, int selected) {
  switch (selected)
  {
    case 0:
      if (settings->width < 64)
        settings->width++;
      break;
    case 1:
      if (settings->height < 48)
        settings->height++;
      break;
    case 2:
      if (settings->proba_destr_wall <= 95)
        settings->proba_destr_wall += 5;
        if (settings->proba_empty + settings->proba_destr_wall > 100) {
          settings->proba_empty -=5;
        }
      break;
    case 3:
      if (settings->proba_empty <= 95)
        settings->proba_empty += 5;
        if (settings->proba_empty + settings->proba_destr_wall > 100) {
          settings->proba_destr_wall -=5;
        }
      break;
    }
}

void launch_main_menu(t_display *display) {
  int is_running = YES;
  SDL_Event event;
  int selected = 0;

  while (is_running) {
      while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
          case SDL_QUIT:
            is_running = NO;
            break;
          case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_UP:    selected -= 1; break;
                case SDLK_DOWN:  selected += 1; break;
                case SDLK_RETURN: {
                  is_running = NO;
                  launch_settings_menu(display);
                  break;
                }
            }
            selected = (selected % 3 + 3) % 3;
            break;
        }
      }
      SDL_RenderClear(display->renderer);
      display_main_menu(display, selected);
      SDL_RenderPresent(display->renderer);
    }
}

void launch_settings_menu(t_display *display) {

  t_game_settings *settings = NULL;
  settings = malloc(sizeof(settings));
  settings->width = DEFAULT_LEVEL_WIDTH;
  settings->height = DEFAULT_LEVEL_HEIGHT;
  settings->proba_destr_wall = DEFAULT_PROBA_DEST;
  settings->proba_empty = DEFAULT_EMPTY;

  int is_running = YES;
  SDL_Event event;
  int selected = 0;

  refresh_settings_menu(display, settings, selected);
  while (is_running) {
      while (SDL_PollEvent(&event)) {

        switch (event.type)
        {
          case SDL_QUIT:
            is_running = NO;
            break;
          case SDL_KEYDOWN:

            switch (event.key.keysym.sym)
            {
                case SDLK_UP:    selected -= 1; break;
                case SDLK_DOWN:  selected += 1; break;
                case SDLK_LEFT: decrease(settings, selected); break;
                case SDLK_RIGHT: increase(settings, selected); break;
                case SDLK_RETURN: {
                  launch_game(display, settings);
                  break;
                }
            }

            selected = (selected % 4 + 4) % 4;
            refresh_settings_menu(display, settings, selected);
            break;
        }
      }
    }
}
