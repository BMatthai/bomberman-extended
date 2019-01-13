#include "../include/time_manager.h"
#include <SDL2/SDL.h>

unsigned int get_time() {
  return SDL_GetTicks();
}
