#ifndef T_GAME_DATA
#define T_GAME_DATA
#include "struct_game_data.h"
#endif

#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif

#ifndef T_CHARACTER
#define T_CHARACTER
#include "struct_character.h"
#endif

#include "client_manager.h"
#include "server_manager.h"
#include "string.h"
#include "game_manager.h"

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
  write(1, "2 - VERSUS COMPUTER\n", strlen("2 - VERSUS COMPUTER\n"));
  write(1, "3 - MULTIJOUEUR\n", strlen("3 - MULTIJOUEUR\n"));
  while (1) {
    read(0, buf, 1);

    if (buf[0] == '1') {
      launch_game(1);
    }
    if (buf[0] == '2') {
      launch_game(2);
    }
    else if(buf[0] == '3') {
      set_multiplayer_menu();
    }
  }
}
