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

void update_values(t_game_settings *settings, int selected, int variation) {
  switch (selected)
  {
    case 0:
      if ((settings->width > 4 && variation < 0) || (settings->width < 64 && variation > 0))
          settings->width += variation;
      break;
    case 1:
      if ((settings->height > 4 && variation < 0) || (settings->height < 48 && variation > 0))
        settings->height += variation;
      break;
    case 2:
      if ((settings->proba_destr_wall > 0 && variation < 0) || (settings->proba_destr_wall < 100  && variation > 0))
        settings->proba_destr_wall += (5 * variation);
        if (settings->proba_empty + settings->proba_destr_wall > 100) {
          settings->proba_empty -=5;
        }
      break;
    case 3:
      if ((settings->proba_empty > 0 && variation < 0) || (settings->proba_empty < 100 && variation > 0))
        settings->proba_empty += (5 * variation);
        if (settings->proba_empty + settings->proba_destr_wall > 100) {
          settings->proba_destr_wall -=5;
        }
      break;
    case 4:
      if ((settings->number_ai > 1 && variation < 0) || (settings->number_ai < 16 && variation > 0))
        settings->number_ai += variation;
      break;
    }
}

// void increase(t_game_settings *settings, int selected) {
//   switch (selected)
//   {
//     case 0:
//       if (settings->width < 64)
//         settings->width++;
//       break;
//     case 1:
//       if (settings->height < 48)
//         settings->height++;
//       break;
//     case 2:
//       if (settings->proba_destr_wall <= 95)
//         settings->proba_destr_wall += 5;
//         if (settings->proba_empty + settings->proba_destr_wall > 100) {
//           settings->proba_empty -=5;
//         }
//       break;
//     case 3:
//       if (settings->proba_empty <= 95)
//         settings->proba_empty += 5;
//         if (settings->proba_empty + settings->proba_destr_wall > 100) {
//           settings->proba_destr_wall -=5;
//         }
//       break;
//     }
// }

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
                  if (selected == 0  || selected == 1) {
                    launch_settings_menu(display);
                  }
                  else {
                  }
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

void set_random_settings(t_game_settings *settings) {
  settings->width = 5 + (rand() % (60));
  settings->height = 5 + (rand() % (44));
  settings->proba_destr_wall = (rand() % (21)) * 5;
  settings->proba_empty = (rand() % (21)) * 5;
  settings->number_ai = 2 + (rand() % (15));
}


void set_settings(t_game_settings *settings, int width, int height, int proba_destr_wall, int proba_empty, int number_ai) {
  settings->width = width;
  settings->height = height;
  settings->proba_destr_wall = proba_destr_wall;
  settings->proba_empty = proba_empty;
  settings->number_ai = number_ai;
}

void launch_settings_menu(t_display *display) {

  t_game_settings settings;
  settings.width = DEFAULT_LEVEL_WIDTH;
  settings.height = DEFAULT_LEVEL_HEIGHT;
  settings.proba_destr_wall = DEFAULT_PROBA_DEST;
  settings.proba_empty = DEFAULT_EMPTY;
  settings.number_ai = DEFAULT_NUMBER_AI;

  int is_running = YES;
  SDL_Event event;
  int selected = 0;

  refresh_settings_menu(display, &settings, selected);
  while (is_running) {
      while (SDL_PollEvent(&event)) {

        switch (event.type)
        {
          // case SDL_QUIT:
          //   is_running = NO;
          //   break;
          case SDL_KEYDOWN:

            switch (event.key.keysym.sym)
            {
                case SDLK_UP:    selected -= 1; break;
                case SDLK_DOWN:  selected += 1; break;
                case SDLK_LEFT: update_values(&settings, selected, -1); break;
                case SDLK_RIGHT: update_values(&settings, selected, 1); break;
                case SDLK_RETURN: {
                  is_running = NO;
                  if (selected == 5) {
                    launch_main_menu(display);
                  }
                  else {
                    launch_game(display, &settings);
                  }
                  break;
                }
                case SDLK_1: set_settings(&settings, 15, 13, 0, 100, 4); break;
                case SDLK_2: set_settings(&settings, 15, 13, 0, 0, 4); break;
                case SDLK_3: set_settings(&settings, 15, 13, 100, 0, 4); break;
                case SDLK_4: set_settings(&settings, 15, 13, 50, 50, 4); break;
                case SDLK_5: set_settings(&settings, 40, 40, 25, 75, 10); break;
                case SDLK_6: set_settings(&settings, 40, 40, 100, 0, 10); break;
                case SDLK_7: set_settings(&settings, 64, 48, 0, 100, 10); break;
                case SDLK_8: set_settings(&settings, 64, 48, 100, 0, 16); break;
                case SDLK_9: set_settings(&settings, 64, 48, 0, 0, 16); break;
                case SDLK_0: set_random_settings(&settings); break;
            }

            selected = (selected % 6 + 6) % 6;
            refresh_settings_menu(display, &settings, selected);
            break;
        }
      }
    }
}
