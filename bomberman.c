#include "struct_level.h"
#include "level_generation.h"
#include "display_level.h"
#include "struct_game_data.h"
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include "action.h"
#include "game_constants.h"
#include "bomb_manager.h"
#include <poll.h>

int main() {

    t_game_data game_data;

    game_data.level = generate_level_from_file("./level/testlevel.lvl");
    t_character *charac = &game_data.level->characters[0];

    struct termios termios_p;
    tcgetattr(1, &termios_p);
    termios_p.c_lflag &= ~ICANON;
    tcsetattr(1, 0, &termios_p);

    char buf[1];
    struct pollfd fds[1];

    fds[0].fd = 0;
    fds[0].events = POLLIN;

    while(1) {
      if(poll(fds, 1, 50) > 0) {
        if(fds[0].revents & POLLIN) {
          read(0, buf, 1);
          action(game_data.level, charac, buf[0]);
        }
      }
      write(1,"\033[2J\n",sizeof("\033[2J\n"));
      check_bombs_timer(game_data.level);
      display_level(game_data.level);
    }



    return 0;

}
