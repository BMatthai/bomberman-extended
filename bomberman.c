
#include "menu_manager.h"

#include <string.h>
#include <stdio.h>
#include <SDL2/SDL.h>


int launch_game_sdl() {
  // if (SDL_Init(SDL_INIT_VIDEO) != 0 )
  //    {
  //        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
  //        return -1;
  //    }
  //
  //    {
  //        /* Création de la fenêtre */
  //        SDL_Window* pWindow = NULL;
  //        pWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_UNDEFINED,
  //                                                                  SDL_WINDOWPOS_UNDEFINED,
  //                                                                  640,
  //                                                                  480,
  //                                                                  SDL_WINDOW_SHOWN);
  //
  //        if( pWindow )
  //        {
  //            SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voie la fenêtre */
  //
  //            SDL_DestroyWindow(pWindow);
  //        }
  //        else
  //        {
  //            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
  //        }
  //    }
  //
  //    SDL_Quit();
      return 0;
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
