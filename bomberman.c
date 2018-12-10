
#include "menu_manager.h"
#include "game_constants.h"

#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <SDL2/SDL.h>

int launch_game_sdl() {
      return 0;
   }

void handler(int sig) {
 printf("Salut\n");
}

int main(int argc, char **argv) {

     SDL_Event event;

     SDL_Init(SDL_INIT_VIDEO);

     SDL_Window *window = SDL_CreateWindow("Bomberman",
         SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, render_flags);

    SDL_Rect dstrect = { 5, 5, 320, 240 };




    SDL_Surface * image = SDL_LoadBMP("resources/free.bmp");
    if(!image) {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        return -1;
    }

    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

    int is_running = YES;
     while (is_running)
     {
       SDL_RenderCopy(renderer, texture, NULL, NULL);

       SDL_RenderPresent(renderer);
       SDL_WaitEvent(&event);

       switch (event.type)
       {
       case SDL_QUIT:
           is_running = NO;
           break;
       }
     }

     SDL_DestroyTexture(texture);
     SDL_FreeSurface(image);
     SDL_DestroyRenderer(renderer);
     SDL_DestroyWindow(window);

     SDL_Quit();

     return 0;


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
