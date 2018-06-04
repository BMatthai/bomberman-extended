//#include "action.h"
#include "stdio.h"
#include "struct_character.h"
#include <unistd.h>



void put_bomb();
void move(t_character character, int x, int y);
void action(t_character character, char touch_action);


void put_bomb() {
  printf("Poser bombe sans effet");
}

void move(t_character character, int x, int y){
  write(1, "salut", s)
  character.position_x = character.position_x + x;
  character.position_y = character.position_y + y;
}

void action(t_character character, char touch_action){
  if(touch_action == 'z')
    move(character, 0,-1);
  if(touch_action == 's')
    move(character, 0,1);
  if(touch_action == 'q')
    move(character, -1,0);
  if(touch_action == 'd')
    move(character, 1,0);
  if(touch_action == 'd')
    put_bomb();
}
