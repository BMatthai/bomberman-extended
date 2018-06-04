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

int main() {

    t_game_data game_data;
    game_data.level = generate_level_from_file("./level/testlevel.lvl");
    game_data.characters = malloc(sizeof(t_character) * 4);

    struct termios termios_p;
    tcgetattr(1, &termios_p);
    termios_p.c_lflag &= ~ICANON;
    tcsetattr(1, 0, &termios_p);

    // for (int i = 0; i < 4; i++) {
    //   game_data.characters[i].heal_points = CHARACTER_HEAL_POINT;
    //   game_data.characters[i].bomb_range = CHARACTER_BOMB_RANGE;
    //   game_data.characters[i].number_bomb = CHARACTER_NUMBER_BOMB;
    //   game_data.characters[i].movement_speed = CHARACTER_MOVEMENT_SPEED;
    //   game_data.characters[i].position_x = 10;
    //   game_data.characters[i]. position_y = 10;
    // }
    char buf[1];
    while(1) {
      read(0, buf, 1);
      //printf("%s", buf);
      write(1,"\033[2J",sizeof("\033[2J"));
      action(game_data.level.characters[0], buf[0]);

      display_level(game_data.level);
    }



    return 0;

}
