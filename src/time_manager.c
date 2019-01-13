#include "time_manager.h"
#include <SDL2/SDL.h>



Uint32 get_time() {
  return SDL_GetTicks();
}
