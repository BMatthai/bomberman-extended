#ifndef T_GAME_DATA
#define T_GAME_DATA
#include "struct_game_data.h"
#endif

#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif

#include "level_generation.h"
#include "display_level.h"
#include "action.h"
#include "game_constants.h"
#include "bomb_manager.h"
#include "string.h"
#include "menu_manager.h"
#include "game_manager.h"

#include "client_manager.h"
#include "server_manager.h"

#include <poll.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>


void read_ip(){
 while(1){
  char input[32];

  printf("\nInput IP Address : ");
  scanf("%s", input);
  join_game(input);
  printf("\nL'addresse du server est incorrecte");
      
 }
 
}
void set_multiplayer_menu() {
  char buf[1];
  

  write(1, "\033[2J\n", sizeof("\033[2J\n"));
  write(1, "1 - HOST GAME\n", strlen("1 - HOST GAME\n"));
  write(1, "2 - JOIN GAME\n", strlen("2 - JOIN GAME\n"));
  while (1) {
    read(0, buf, 1);

    if (buf[0] == '1') {
     host_game();
    }
    else if(buf[0] == '2') {
      write(1, "Enter server address\n", strlen("Enter server address\n"));
      
      read_ip();
      write(1, "Did entered server address\n", strlen("Did entered server address\n"));
      
        
    }
  }
}

void launch_menu() {
  char buf[1];

  write(1, "\033[2J\n", sizeof("\033[2J\n"));
  write(1, "1 - MONOJOUEUR\n", strlen("1 - MONOJOUEUR\n"));
  write(1, "2 - MULTIJOUEUR\n", strlen("2 - MULTIJOUEUR\n"));
  while (1) {
    read(0, buf, 1);

    if (buf[0] == '1') {
      launch_game();
    }
    else if(buf[0] == '2') {
      set_multiplayer_menu();
    }
  }
}

void launch_listmap() {
  char buf[1];

  write(1, "\033[2J\n", sizeof("\033[2J\n"));

  while (1) {
    read(0, buf, 1);

    if (buf[0] == '1') {
      launch_game();
    }
  }
}

void launch_game() {
  t_game_data *game_data = NULL;

  game_data = malloc(sizeof(t_game_data));

  game_data->level = generate_level_from_file("./level/testlevel2.lvl");
  t_character *charac = game_data->playable_character = &game_data->level->characters[0];

  struct termios termios_p;
  tcgetattr(1, &termios_p);
  termios_p.c_lflag &= ~ICANON;
  tcsetattr(1, 0, &termios_p);

  char buf[1];
  struct pollfd fds[1];

  fds[0].fd = 0;
  fds[0].events = POLLIN;

  while(game_state(game_data) != GAME_PLAYABLE_CHARACTER_IS_DEAD) {
    if (poll(fds, 1, 50) > 0) {
      if(fds[0].revents & POLLIN) {
        read(0, buf, 1);
        action(game_data->level, charac, buf[0]);
      }
    }
    write(1,"\033[2J\n",sizeof("\033[2J\n"));
    check_bombs_timer(game_data->level);
    display_screen(game_data);
  }
  launch_menu();
}
