
#ifndef T_DISPLAY
#define T_DISPLAY
#include "struct_display.h"
#endif

#include "game_constants.h"
#include "game_manager.h"

#include <string.h>
#include <signal.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

t_display *init_window() {
  t_display *display;

  SDL_Init(SDL_INIT_VIDEO);

  // *police = NULL; //initialisation de la police
  // TTF_Init(); //initialisation de ttf
  // police = TTF_OpenFont("Sans.ttf", 15); //déclare la police
  // TTF_SetFontStyle(police, TTF_STYLE_BOLD); //On gère la police
  // SDL_Color couleurBlanc = {255, 255, 255}; //La couleur
  // SDL_Surface *texte = {NULL}; //la surface de la police
  // SDL_Rect position_texte = {NULL}; //La position de la police
  // texte = TTF_RenderText_Solid(police, "Hello", couleurBlanc); //on dit le texte
  // SDL_BlitSurface(texte, NULL, ecran, &position_texte); // On blite la surface
  // SDL_FreeSurface(texte); //libère la surface du texte
  // TTF_CloseFont(police); //libère la police
  // TTF_Quit(); //on quitte sdl_ttf

  SDL_Window *window = SDL_CreateWindow("Bomberman",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, STANDARD_WIN_WIDTH, STANDARD_WIN_HEIGHT, 0);

  Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, render_flags);

  display = malloc(sizeof(t_display));
  display->window = window;
  display->renderer = renderer;

  return display;
}

void display_menu(t_display *display, int selected) {

  SDL_Rect location;
  int width = 400;
  int height = 100;
  for (int i = 0; i < 3; i++) {
    location.x = (STANDARD_WIN_WIDTH / 2) - (width / 2);
    location.y = (STANDARD_WIN_HEIGHT / 2) - ((3 * height) / 2) + (i * height);
    location.w = width;
    location.h = height;
    SDL_RenderCopy(display->renderer, display->text_menu[i], NULL, &location);
  }

  location.x = (STANDARD_WIN_WIDTH / 2) - (width / 2) - 100;
  location.y = (STANDARD_WIN_HEIGHT / 2) - ((3 * height) / 2) + (selected * height);
  location.w = height;
  location.h = height;
  SDL_RenderCopy(display->renderer, display->text_menu[3], NULL, &location);

  location.x = (STANDARD_WIN_WIDTH / 2) + (width / 2) + 100;
  location.y = (STANDARD_WIN_HEIGHT / 2) - ((3 * height) / 2) + (selected * height);
  location.w = height;
  location.h = height;
  SDL_RenderCopy(display->renderer, display->text_menu[4], NULL, &location);

}

int go_to_selected(selected) {
  if (selected == MENU_MONOPLAYER) {
    launch_game_SDL();
  }
}

int main(int argc, char **argv) {

  t_display *display = NULL;
  display = init_window();

  TTF_Init();
  TTF_Font *font = NULL;

  font = TTF_OpenFont("./resources/fonts/OpenSans-Light.ttf", 100); //this opens a font style and sets a size

  if(!font) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
   // handle error
}

  display->font = font;

  SDL_Color white = {255, 255, 255};

  SDL_Surface *surfaceMono = TTF_RenderText_Solid(font, "Monojoueur", white); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
  SDL_Surface *surfaceMulti = TTF_RenderText_Solid(font, "Multijoueur", white); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
  SDL_Surface *surfaceQuit = TTF_RenderText_Solid(font, "Quitter", white); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
  SDL_Surface *surfaceSelectL = TTF_RenderText_Solid(font, ">", white); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
  SDL_Surface *surfaceSelectR = TTF_RenderText_Solid(font, "<", white); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

  SDL_Texture *textMenu[5];

  textMenu[0] = SDL_CreateTextureFromSurface(display->renderer, surfaceMono); //now you can convert it into a texture
  textMenu[1] = SDL_CreateTextureFromSurface(display->renderer, surfaceMulti); //now you can convert it into a texture
  textMenu[2] = SDL_CreateTextureFromSurface(display->renderer, surfaceQuit); //now you can convert it into a texture
  textMenu[3] = SDL_CreateTextureFromSurface(display->renderer, surfaceSelectL); //now you can convert it into a texture
  textMenu[4] = SDL_CreateTextureFromSurface(display->renderer, surfaceSelectR); //now you can convert it into a texture

  display->text_menu = textMenu;


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
                case SDLK_RETURN: go_to_selected(selected); break;

            }
            selected %= 3;
            break;

        }
      }


      SDL_RenderClear(display->renderer);
      display_menu(display, selected);

      SDL_RenderPresent(display->renderer);

  }

  SDL_RenderPresent(display->renderer);


  SDL_DestroyWindow(display->window);
  SDL_Quit();
  return 0;

//launch_game_SDL();

  //
  // SDL_Window *window;                    // Declare a pointer
  //
  // SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
  //
  // // Create an application window with the following settings:
  // window = SDL_CreateWindow(
  //     "An SDL2 window",                  // window title
  //     SDL_WINDOWPOS_UNDEFINED,           // initial x position
  //     SDL_WINDOWPOS_UNDEFINED,           // initial y position
  //     640,                               // width, in pixels
  //     480,                               // height, in pixels
  //     SDL_WINDOW_OPENGL                  // flags - see below
  // );
  //
  // // Check that the window was successfully created
  // if (window == NULL) {
  //     // In the case that the window could not be made...
  //     printf("Could not create window: %s\n", SDL_GetError());
  //     return 1;
  // }
  //
  // SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  //
  // SDL_Surface *free_image = SDL_LoadBMP("resources/free.bmp");
  //
  // SDL_Texture *free_texture = SDL_CreateTextureFromSurface(renderer, free_image);
  //
  // SDL_FreeSurface(free_image);
  //
  // SDL_Rect dstrect = { 5, 5, 320, 240 };
  //
  // SDL_RenderCopy(renderer, free_texture, NULL,  &dstrect);
  // //SDL_RenderCopy(renderer, free_texture, NULL,  NULL);
  //
  //
  //
  // // A basic main loop to prevent blocking
  // int is_running = YES;
  // SDL_Event event;
  // while (is_running) {
  //     while (SDL_PollEvent(&event)) {
  //         if (event.type == SDL_QUIT) {
  //             is_running = NO;
  //         }
  //     }
  //     SDL_RenderClear(renderer);
  //     SDL_RenderPresent(renderer);
  //     SDL_Delay(16);
  // }
  //
  // // Close and destroy the window
  // SDL_DestroyWindow(window);
  //
  // // Clean up
  // SDL_Quit();
  // return 0;
}
