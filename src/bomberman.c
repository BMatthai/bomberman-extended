
#ifndef T_DISPLAY
#define T_DISPLAY
#include "../include/struct_display.h"
#endif

#include "../include/struct_game_settings.h"


#include "../include/game_constants.h"
#include "../include/game_manager.h"

#include <string.h>
#include <signal.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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
}


void init_default_theme(t_display *display) {
  s_theme_display *theme = NULL;

  theme = malloc(sizeof(t_theme_display));

  t_text_display **text_main_menu = NULL;

  *text_main_menu = malloc(sizeof(t_text_display *) * 3);

  text_main_menu[MENU_MONOPLAYER] = create_text_display(display, "Monojoueur");
  text_main_menu[MENU_MULTIPLAYER] = create_text_display(display, "Multijoueur");
  text_main_menu[MENU_QUIT] = create_text_display(display, "Quitter");

  // text_main_menu[3] = create_text_display(display, ">");
  // text_main_menu[4] = create_text_display(display, "<");

  // text_settings_menu[0] = create_text_display(display, "Largeur map : ");
  // text_settings_menu[1] = create_text_display(display, "Hauteur map : ");
  // text_settings_menu[2] = create_text_display(display, "% de cases destructible : ");
  // text_settings_menu[3] = create_text_display(display, "% de cases libres libre : ");

  // create_graphic_display("resources/wall.bmp");
  // SDL_Surface *image_wall = SDL_LoadBMP();
  // SDL_Surface *image_destr = SDL_LoadBMP("resources/destructible.bmp");
  // SDL_Surface *image_misc = SDL_LoadBMP("resources/misc.bmp");
  //
  // SDL_Surface *image_char0 = SDL_LoadBMP("resources/char0.bmp");
  // SDL_Surface *image_char1 = SDL_LoadBMP("resources/char1.bmp");
  // SDL_Surface *image_char2 = SDL_LoadBMP("resources/char2.bmp");
  // SDL_Surface *image_char3 = SDL_LoadBMP("resources/char3.bmp");
  //
  // SDL_Surface *image_bomb0 = SDL_LoadBMP("resources/bomb0.bmp");
  // SDL_Surface *image_bomb1 = SDL_LoadBMP("resources/bomb1.bmp");
  // SDL_Surface *image_bomb2 = SDL_LoadBMP("resources/bomb2.bmp");
  // SDL_Surface *image_bomb3 = SDL_LoadBMP("resources/bomb2b.bmp");



  display->text_main_menu = text_main_menu;
  display->text_settings_menu = text_settings_menu;
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

  SDL_Color white = {255, 255, 255, 255};

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



  SDL_Surface *surfaceBlizzard =  SDL_CreateRGBSurface(0, STANDARD_WIN_WIDTH, STANDARD_WIN_HEIGHT, 32, 0, 0, 0, 0);
  SDL_Surface *surfaceRed =  SDL_CreateRGBSurface(0, STANDARD_LIFE_GAUGE_WIDTH, STANDARD_LIFE_GAUGE_WIDTH, 32, 0, 0, 0, 0);

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

  t_text_display **text_main_menu;
  t_text_display **text_settings_menu;

  SDL_FillRect(surfaceBlizzard, NULL, SDL_MapRGBA(surfaceBlizzard->format, 0, 0, 255, 0));
  SDL_FillRect(surfaceRed, NULL, SDL_MapRGBA(surfaceRed->format, 255, 0, 0, 0));

  text_red = SDL_CreateTextureFromSurface(renderer, surfaceRed);
  text_blizzard = SDL_CreateTextureFromSurface(renderer, surfaceBlizzard);

  t_display *display = NULL;

  display = malloc(sizeof(t_display));
  display->window = window;
  display->renderer = renderer;
  display->text_bomb = text_bomb;
  display->text_terrain = text_terrain;
  display->text_character = text_character;
  display->text_blizzard = text_blizzard;
  display->text_red = text_red;
  display->font = font;

  return display;
}




void display_settings_menu(t_display *display, t_game_settings *settings, int selected) {

  SDL_Surface **surface_values = NULL;
  SDL_Texture **text_values = NULL;

  int nb_menu = 4;
  surface_values = malloc(sizeof(SDL_Surface *) * nb_menu);
  text_values = malloc(sizeof(SDL_Texture *) * nb_menu);

  SDL_Color white = {255, 255, 255, 255};

  TTF_Font *font = NULL;
  font = TTF_OpenFont("./resources/fonts/OpenSans-Light.ttf", STANDARD_MENU_LETTERING_SIZE);

  char str_width[3];
  char str_height[3];
  char str_prob_destr[4];
  char str_prob_empty[4];

  sprintf(str_width, "%d", settings->width);
  sprintf(str_height, "%d", settings->height);
  sprintf(str_prob_destr, "%d", settings->proba_destr_wall);
  sprintf(str_prob_empty, "%d", settings->proba_empty);

  surface_values[0] = TTF_RenderText_Blended(font, str_width, white);
  surface_values[1] = TTF_RenderText_Blended(font, str_height, white);
  surface_values[2] = TTF_RenderText_Blended(font, str_prob_destr, white);
  surface_values[3] = TTF_RenderText_Blended(font, str_prob_empty, white);

  text_values[0] = SDL_CreateTextureFromSurface(display->renderer, surface_values[0]);
  text_values[1] = SDL_CreateTextureFromSurface(display->renderer, surface_values[1]);
  text_values[2] = SDL_CreateTextureFromSurface(display->renderer, surface_values[2]);
  text_values[3] = SDL_CreateTextureFromSurface(display->renderer, surface_values[3]);

  SDL_Rect location;
  int width = 400;
  int height = STANDARD_MENU_LETTERING_SIZE;

  for (int i = 0; i < 4; i++) {
    location.x = (STANDARD_WIN_WIDTH / 2) - (width);
    location.y = (STANDARD_WIN_HEIGHT / 2) - ((nb_menu * height) / 2) + (i * height);
    location.w = width;
    location.h = height;
    SDL_RenderCopy(display->renderer, display->text_settings_menu[i], NULL, &location);

    location.x = (STANDARD_WIN_WIDTH / 2);
    location.y = (STANDARD_WIN_HEIGHT / 2) - ((nb_menu * height) / 2) + (i * height);
    location.w = 150;
    location.h = height;
    SDL_RenderCopy(display->renderer, text_values[i], NULL, &location); /* Blit du texte */

    // SDL_DestroyTexture(text_values[i]);
    // SDL_FreeSurface(surface_values[i]);
  }

  location.x = (STANDARD_WIN_WIDTH / 2) - (width) - 100;
  location.y = (STANDARD_WIN_HEIGHT / 2) - ((nb_menu * height) / 2) + (selected * height);
  location.w = height;
  location.h = height;
  SDL_RenderCopy(display->renderer, display->text_main_menu[3], NULL, &location);

  location.x = (STANDARD_WIN_WIDTH / 2) + 150;
  location.y = (STANDARD_WIN_HEIGHT / 2) - ((nb_menu * height) / 2) + (selected * height);
  location.w = height;
  location.h = height;
  SDL_RenderCopy(display->renderer, display->text_main_menu[4], NULL, &location);
}

void display_main_menu(t_display *display, int selected) {

  int nb_menu = 3;
  SDL_Rect location;
  int width = 400;
  int height = STANDARD_MENU_LETTERING_SIZE;
  for (int i = 0; i < 3; i++) {
    location.x = (STANDARD_WIN_WIDTH / 2) - (width / 2);
    location.y = (STANDARD_WIN_HEIGHT / 2) - ((nb_menu * height) / 2) + (i * height);
    location.w = width;
    location.h = height;
    SDL_RenderCopy(display->renderer, display->text_main_menu[i], NULL, &location);
  }

  location.x = (STANDARD_WIN_WIDTH / 2) - (width / 2) - 100;
  location.y = (STANDARD_WIN_HEIGHT / 2) - ((nb_menu * height) / 2) + (selected * height);
  location.w = height;
  location.h = height;
  SDL_RenderCopy(display->renderer, display->text_main_menu[3], NULL, &location);

  location.x = (STANDARD_WIN_WIDTH / 2) + (width / 2) + 100;
  location.y = (STANDARD_WIN_HEIGHT / 2) - ((nb_menu * height) / 2) + (selected * height);
  location.w = height;
  location.h = height;
  SDL_RenderCopy(display->renderer, display->text_main_menu[4], NULL, &location);
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
      break;
    case 3:
      if (settings->proba_empty <= 95)
        settings->proba_empty += 5;
      break;
    }
}

void game_settings_menu_loop(t_display *display) {

  t_game_settings *settings = NULL;
  settings = malloc(sizeof(settings));
  settings->width = DEFAULT_LEVEL_WIDTH;
  settings->height = DEFAULT_LEVEL_HEIGHT;
  settings->proba_destr_wall = DEFAULT_PROBA_DEST;
  settings->proba_empty = DEFAULT_EMPTY;

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
                case SDLK_LEFT: decrease(settings, selected); break;
                case SDLK_RIGHT: increase(settings, selected); break;
                case SDLK_RETURN: {
                  launch_game(display, settings);
                  break;
                }
            }

            selected = (selected % 4 + 4) % 4;
            SDL_RenderClear(display->renderer);
            display_settings_menu(display, settings, selected);
            SDL_RenderPresent(display->renderer);
            break;
        }
      }
}
}

void go_to_selected(t_display *display, int selected) {
  if (selected == MENU_MONOPLAYER) {
    game_settings_menu_loop(display);
  }
}

void main_menu_loop(t_display *display) {
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
                  game_settings_menu_loop(display);
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

int main() {

  t_display *display = NULL;
  display = init_window();

  main_menu_loop(display);

  SDL_DestroyWindow(display->window);
  SDL_Quit();
  return 0;
}
