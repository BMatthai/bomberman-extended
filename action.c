void put_bomb() {
  printf("Poser bombe sans effet");
}

void move(){
  printf("Déplacement sans effet");
}

action(char touch_action){
  if(touch_action == 'z')
    move(0,-1);
  if(touch_action == 's')
    move(0,1);
  if(touch_action == 'q')
    move(-1,0);
  if(touch_action == 'd')
    move(1,0);
  if(touch_action == 'd')
    put_bomb();
}
