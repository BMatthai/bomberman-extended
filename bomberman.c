
#include "game_constants.h"
#include "game_manager.h"

#include <string.h>
#include <signal.h>
#include <SDL2/SDL.h>




int main(int argc, char **argv) {


launch_game_SDL();

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
