
#include "menu_manager.h"

#include <string.h>

#include <SDL2/SDL.h>


void launch_game_sdl() {
  SDL_CreateWindow("tesdt'",0,0,640,180,0);
}


int main(int argc, char **argv) {

    if (argc == 2 && strcmp(argv[1], "term") == 0){
      launch_menu();
    }
    else if (argc == 2 && strcmp(argv[1], "sdl") == 0) {
      launch_game_sdl();
    }
    return 0;

}
