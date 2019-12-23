
#ifndef T_DISPLAY
#define T_DISPLAY
#include "../include/struct_display.h"
#endif

#ifndef T_SETTINGS
#define T_SETTINGS
#include "../include/struct_game_settings.h"
#endif


#include "../include/game_constants.h"
#include "../include/game_manager.h"

#include "../include/menu_manager.h"

#include "../include/display_menu.h"
#include  "../include/init_display.h"
#include "../include/test.h"

#include <string.h>
#include <signal.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main() {
  // test_procedure();
  t_display *display = NULL;
  display = init_window();

  launch_main_menu(display);
  SDL_DestroyWindow(display->window);
  SDL_Quit();
  return 0;
}
