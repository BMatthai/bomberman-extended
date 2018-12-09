
#include "menu_manager.h"

#include <string.h>
#include <stdio.h>
#include <signal.h>

int launch_game_sdl() {
      return 0;
   }

void handler(int sig) {
 printf("Salut\n");
}

int main(int argc, char **argv) {

  signal (SIGTERM, handler);
  launch_menu();

    return 0;
}
