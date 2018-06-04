//#include "action.h"
#include "stdio.h"
#include "struct_character.h"
#include <unistd.h>



void put_bomb();
void move(t_character character, int x, int y);
void action(t_character *character, char touch_action);


void put_bomb() {
  printf("Poser bombe sans effet");
}

// void move(t_character *character, int x, int y){
//
//   character->position_x += x;
//   character->position_y += y;
//
// }
//
// void action(t_character *character, char touch_action){
//   if(touch_action == 'z')
//     move(character, 0,-1);
//   if(touch_action == 's')
//     move(character, 0,1);
//   if(touch_action == 'q')
//     move(character, -1,0);
//   if(touch_action == 'd')
//     move(character, 1,0);
//   if(touch_action == 'c')
//     put_bomb();
// }
//
// void move(t_character *character, int x, int y){
//
//   character->position_x += x;
//   character->position_y += y;
//
// }

void action(t_character *character, char touch_action){
  if(touch_action == 'z') {
    character->position_x += 0;
    character->position_y += -1;
  }
  if(touch_action == 's') {
    character->position_x += 0;
    character->position_y += 1;
  }
  if(touch_action == 'q') {
    character->position_x += -1;
    character->position_y += 0;
  }
  if(touch_action == 'd') {
    character->position_x += 1;
    character->position_y += 0;
  }
}
