
#ifndef T_DISPLAY
#define T_DISPLAY
#include "struct_display.h"
#endif

#include "struct_game_settings.h"


#include "game_constants.h"
#include "game_manager.h"

#include <string.h>
#include <signal.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

t_display *init_window() {

  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  SDL_Window *window = SDL_CreateWindow("Bomberman",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, STANDARD_WIN_WIDTH, STANDARD_WIN_HEIGHT, 0);
  Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

  SDL_Renderer *renderer = NULL;
  TTF_Font *font = NULL;

  renderer = SDL_CreateRenderer(window, -1, render_flags);
  font = TTF_OpenFont("./resources/fonts/OpenSans-Light.ttf", 100);

  if(!font) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
  }

  SDL_Color white = {255, 255, 255};

  SDL_Texture **text_terrain = malloc(4 * sizeof(SDL_Texture *));
  SDL_Texture **text_bomb = malloc(4 * sizeof(SDL_Texture *));
  SDL_Texture **text_character = malloc(4 * sizeof(SDL_Texture *));
  SDL_Texture **text_main_menu = malloc(5 * sizeof(SDL_Texture *));
  SDL_Texture **text_settings_menu = malloc(4 * sizeof(SDL_Texture *));
  SDL_Texture *text_blizzard = malloc(sizeof(SDL_Texture *));


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

  SDL_Surface *surfaceMono = TTF_RenderText_Solid(font, "Monojoueur", white);
  SDL_Surface *surfaceMulti = TTF_RenderText_Solid(font, "Multijoueur", white);
  SDL_Surface *surfaceQuit = TTF_RenderText_Solid(font, "Quitter", white);
  SDL_Surface *surfaceSelectL = TTF_RenderText_Solid(font, ">", white);
  SDL_Surface *surfaceSelectR = TTF_RenderText_Solid(font, "<", white);

  SDL_Surface *surfaceWidth = TTF_RenderText_Solid(font, "Largeur map : ", white);
  SDL_Surface *surfaceHeight = TTF_RenderText_Solid(font, "Hauteur map : ", white);
  SDL_Surface *surfaceProbaDestrWall = TTF_RenderText_Solid(font, "% de cases destructible : ", white);
  SDL_Surface *surfaceProbaEmpty = TTF_RenderText_Solid(font, "% de cases libres libre : ", white);

  SDL_Surface *surfaceBlizzard =  SDL_CreateRGBSurface(0, STANDARD_WIN_WIDTH, STANDARD_WIN_HEIGHT, 32, 0, 9, 0, 0);

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

  text_main_menu[0] = SDL_CreateTextureFromSurface(renderer, surfaceMono);
  text_main_menu[1] = SDL_CreateTextureFromSurface(renderer, surfaceMulti);
  text_main_menu[2] = SDL_CreateTextureFromSurface(renderer, surfaceQuit);
  text_main_menu[3] = SDL_CreateTextureFromSurface(renderer, surfaceSelectL);
  text_main_menu[4] = SDL_CreateTextureFromSurface(renderer, surfaceSelectR);

  text_settings_menu[0] = SDL_CreateTextureFromSurface(renderer, surfaceWidth);
  text_settings_menu[1] = SDL_CreateTextureFromSurface(renderer, surfaceHeight);
  text_settings_menu[2] = SDL_CreateTextureFromSurface(renderer, surfaceProbaDestrWall);
  text_settings_menu[3] = SDL_CreateTextureFromSurface(renderer, surfaceProbaEmpty);

  SDL_FillRect(surfaceBlizzard, NULL, SDL_MapRGBA(surfaceBlizzard->format, 0, 0, 255, 0));

  text_blizzard = SDL_CreateTextureFromSurface(renderer, surfaceBlizzard);


  t_display *display = NULL;

  display = malloc(sizeof(t_display));
  display->window = window;
  display->renderer = renderer;
  display->text_bomb = text_bomb;
  display->text_terrain = text_terrain;
  display->text_character = text_character;
  display->text_main_menu = text_main_menu;
  display->text_settings_menu = text_settings_menu;
  display->text_blizzard = text_blizzard;
  display->font = font;

  return display;
}

void display_settings_menu(t_display *display, t_game_settings *settings, int selected) {


  SDL_Rect location;
  int width = 400;
  int height = 100;
  for (int i = 0; i < 4; i++) {
    location.x = (STANDARD_WIN_WIDTH / 2) - (width);
    location.y = (STANDARD_WIN_HEIGHT / 2) - ((3 * height) / 2) + (i * height);
    location.w = width;
    location.h = height;
    SDL_RenderCopy(display->renderer, display->text_settings_menu[i], NULL, &location);
  }

  location.x = (STANDARD_WIN_WIDTH / 2) - (width) - 100;
  location.y = (STANDARD_WIN_HEIGHT / 2) - ((3 * height) / 2) + (selected * height);
  location.w = height;
  location.h = height;
  SDL_RenderCopy(display->renderer, display->text_main_menu[3], NULL, &location);

  location.x = (STANDARD_WIN_WIDTH / 2) + 150;
  location.y = (STANDARD_WIN_HEIGHT / 2) - ((3 * height) / 2) + (selected * height);
  location.w = height;
  location.h = height;
  SDL_RenderCopy(display->renderer, display->text_main_menu[4], NULL, &location);
}

void display_main_menu(t_display *display, int selected) {

  SDL_Rect location;
  int width = 400;
  int height = 100;
  for (int i = 0; i < 3; i++) {
    location.x = (STANDARD_WIN_WIDTH / 2) - (width / 2);
    location.y = (STANDARD_WIN_HEIGHT / 2) - ((3 * height) / 2) + (i * height);
    location.w = width;
    location.h = height;
    SDL_RenderCopy(display->renderer, display->text_main_menu[i], NULL, &location);
  }

  location.x = (STANDARD_WIN_WIDTH / 2) - (width / 2) - 100;
  location.y = (STANDARD_WIN_HEIGHT / 2) - ((3 * height) / 2) + (selected * height);
  location.w = height;
  location.h = height;
  SDL_RenderCopy(display->renderer, display->text_main_menu[3], NULL, &location);

  location.x = (STANDARD_WIN_WIDTH / 2) + (width / 2) + 100;
  location.y = (STANDARD_WIN_HEIGHT / 2) - ((3 * height) / 2) + (selected * height);
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

    SDL_RenderClear(display->renderer);
    display_settings_menu(display, settings, selected);
    SDL_RenderPresent(display->renderer);

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
            selected %= 4;
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
            selected %= 3;
            break;
        }
      }
      SDL_RenderClear(display->renderer);
      display_main_menu(display, selected);
      SDL_RenderPresent(display->renderer);
}

}

int main(int argc, char **argv) {

  t_display *display = NULL;
  display = init_window();

  main_menu_loop(display);

  SDL_DestroyWindow(display->window);
  SDL_Quit();
  return 0;
}
