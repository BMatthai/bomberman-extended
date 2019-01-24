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

#ifndef T_SETTINGS
#define T_SETTINGS
#include "../include/struct_game_settings.h"
#endif

#include "../include/textures_repertory.h"
#include "../include/game_constants.h"
#include "../include/display_menu.h"

#include  "../include/init_display.h"

void display_settings_menu(t_display *display, t_game_settings *settings, int selected) {
  int nb_menu = 4;
  t_text_display **values = NULL;

  values = malloc(sizeof(t_text_display *) * nb_menu);

  // SDL_Color white = {255, 255, 255, 255};

  // TTF_Font *font = NULL;
  // font = TTF_OpenFont("./resources/fonts/OpenSans-Light.ttf", STANDARD_MENU_LETTERING_SIZE);

  char str_width[3];
  char str_height[3];
  char str_prob_destr[4];
  char str_prob_empty[4];

  sprintf(str_width, "%d", settings->width);
  sprintf(str_height, "%d", settings->height);
  sprintf(str_prob_destr, "%d", settings->proba_destr_wall);
  sprintf(str_prob_empty, "%d", settings->proba_empty);

  // t_text_display *width_value = NULL;
  // t_text_display *height_value = NULL;
  // t_text_display *percentaged_destructible_value = NULL;
  // t_text_display *percentage_empty_value = NULL;

  values[0] = create_text_display(display, str_width);
  values[1] = create_text_display(display, str_height);
  values[2] = create_text_display(display, str_prob_destr);
  values[3] = create_text_display(display, str_prob_empty);

  SDL_Rect location;
  t_text_display *cur_text_display = NULL;

  for (int i = 0; i < 4; i++) {
    cur_text_display = display->theme->text_menu[TEXT_MENU_MAP_WIDTH_STR + i];

    location.x = (STANDARD_WIN_WIDTH / 2) - (cur_text_display->recommended_w / 2);
    location.y = (STANDARD_WIN_HEIGHT / 2) - ((nb_menu * cur_text_display->recommended_h) / 2) + (i * cur_text_display->recommended_h);
    location.w = cur_text_display->recommended_w;
    location.h = cur_text_display->recommended_h;
    SDL_RenderCopy(display->renderer, cur_text_display->texture, NULL, &location);

    cur_text_display = values[i];

    location.x = (STANDARD_WIN_WIDTH / 2) + 300;
    location.y = (STANDARD_WIN_HEIGHT / 2) - ((nb_menu * cur_text_display->recommended_h) / 2) + (i * cur_text_display->recommended_h);
    location.w = cur_text_display->recommended_w;
    location.h = cur_text_display->recommended_h;
    SDL_RenderCopy(display->renderer, cur_text_display->texture, NULL, &location); /* Blit du texte */

    // SDL_DestroyTexture(text_values[i]);
    // SDL_FreeSurface(surface_values[i]);
  }

  cur_text_display = display->theme->text_menu[TEXT_MENU_SELECTOR_LEFT];

  location.x = (STANDARD_WIN_WIDTH / 2) - 400;
  location.y = (STANDARD_WIN_HEIGHT / 2) - ((nb_menu * cur_text_display->recommended_h) / 2) + (selected * cur_text_display->recommended_h);
  location.w = cur_text_display->recommended_w;
  location.h = cur_text_display->recommended_h;
  SDL_RenderCopy(display->renderer, cur_text_display->texture, NULL, &location);

  cur_text_display = display->theme->text_menu[TEXT_MENU_SELECTOR_RIGHT];

  location.x = (STANDARD_WIN_WIDTH / 2) + 400;
  location.y = (STANDARD_WIN_HEIGHT / 2) - ((nb_menu * cur_text_display->recommended_h) / 2) + (selected * cur_text_display->recommended_h);
  location.w = cur_text_display->recommended_w;
  location.h = cur_text_display->recommended_h;
  SDL_RenderCopy(display->renderer, cur_text_display->texture, NULL, &location);
}

void display_main_menu(t_display *display, int selected) {

  int nb_menu = 3;
  SDL_Rect location;
  t_text_display *cur_text_display = NULL;


  for (int i = 0; i < 3; i++) {
    cur_text_display = display->theme->text_menu[TEXT_MENU_MONOPLAYER + i];

    location.x = (STANDARD_WIN_WIDTH / 2) - (cur_text_display->recommended_w / 2);
    location.y = (STANDARD_WIN_HEIGHT / 2) - ((nb_menu * cur_text_display->recommended_h) / 2) + (i * cur_text_display->recommended_h);
    location.w = cur_text_display->recommended_w;
    location.h = cur_text_display->recommended_h;
    SDL_RenderCopy(display->renderer, cur_text_display->texture, NULL, &location);
  }

  cur_text_display = display->theme->text_menu[TEXT_MENU_SELECTOR_LEFT];

  location.x = (STANDARD_WIN_WIDTH / 2) - 400;
  location.y = (STANDARD_WIN_HEIGHT / 2) - ((nb_menu * cur_text_display->recommended_h) / 2) + (selected * cur_text_display->recommended_h);
  location.w = cur_text_display->recommended_w;
  location.h = cur_text_display->recommended_h;
  SDL_RenderCopy(display->renderer, cur_text_display->texture, NULL, &location);

  cur_text_display = display->theme->text_menu[TEXT_MENU_SELECTOR_RIGHT];


  location.x = (STANDARD_WIN_WIDTH / 2) + 400;
  location.y = (STANDARD_WIN_HEIGHT / 2) - ((nb_menu * cur_text_display->recommended_h) / 2) + (selected * cur_text_display->recommended_h);
  location.w = cur_text_display->recommended_w;
  location.h = cur_text_display->recommended_h;
  SDL_RenderCopy(display->renderer, display->theme->text_menu[TEXT_MENU_SELECTOR_RIGHT]->texture, NULL, &location);
}
