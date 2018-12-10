#ifndef T_GAME_DATA
#define T_GAME_DATA
#include "struct_game_data.h"
#endif

#include "game_constants.h"
#include "game_manager.h"
#include "level_generation.h"
#include "time_manager.h"
#include "action.h"
#include "level_generation.h"
#include "display_level.h"
#include "action.h"
#include "game_constants.h"
#include "bomb_manager.h"
#include "menu_manager.h"
#include "game_manager.h"
#include "character_creation.h"

#include "time_manager.h"
#include "ai_manager.h"

#include <poll.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int game_state(t_game_data *game_data) {
  if(game_data->playable_character->heal_points < CHARACTER_ALIVE) {
      return GAME_PLAYABLE_CHARACTER_IS_DEAD;
  }
  else if (game_data->level->characters[1].state == CHARACTER_DEAD && game_data->level->characters[2].state == CHARACTER_DEAD && game_data->level->characters[3].state == CHARACTER_DEAD) {
    return GAME_IS_WON;
  }
return GAME_IS_RUNNING;
}

int launch_game_SDL() {


  SDL_Event event;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow("Bomberman",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

 Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

 SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, render_flags);

 SDL_Rect dstrect = { 5, 5, 320, 240 };




 SDL_Surface * image = SDL_LoadBMP("resources/free.bmp");
 if(!image) {
     printf("Erreur de chargement de l'image : %s",SDL_GetError());
     return -1;
 }

 SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

  int is_running = YES;
  while (is_running)
  {
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_RenderPresent(renderer);
    SDL_WaitEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        is_running = NO;
        break;
    }
    //display_screen_SDL(renderer);
  }

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(image);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;



  // t_game_data *game_data = NULL;
  //
  // game_data = malloc(sizeof(t_game_data));
  //
  // if (game_data == NULL) {
  //   return -1;
  // }
  //
  // game_data->level = generate_level_from_file("./level/testlevel.lvl");
  //
  // struct termios termios_p;
  // tcgetattr(1, &termios_p);
  // termios_p.c_lflag &= ~ICANON;
  // termios_p.c_lflag &= ~ECHO;
  // tcsetattr(1, 0, &termios_p);
  //
  // char buf[1];
  // struct pollfd fds[1];
  //
  // fds[0].fd = 0;
  // fds[0].events = POLLIN;
  //
  // t_character *playable_character = game_data->playable_character = &game_data->level->characters[0];
  // t_character *character_2 = &game_data->level->characters[1];
  // t_character *character_3 = &game_data->level->characters[2];
  // t_character *character_4 = &game_data->level->characters[3];
  //
  // t_level *cur_level = game_data->level;
  //
  // int time_to_reload = get_time();
  // int time_to_redisplay = get_time();
  // write(1,"\033[2J\n",sizeof("\033[2J\n"));
  // while(game_state(game_data) != GAME_PLAYABLE_CHARACTER_IS_DEAD && game_state(game_data) != GAME_IS_WON) {
  //   if (poll(fds, 1, 50) > 0) {
  //     if(fds[0].revents & POLLIN) {
  //       read(0, buf, 1);
  //       action(cur_level, playable_character, buf[0]);
  //     }
  //   }
  //
  //   if (ai == 2){
  //     if (get_time() - time_to_reload > TIME_TO_REPLAY_IA) {
  //       ai_play(cur_level, character_2);
  //       ai_play(cur_level, character_3);
  //       ai_play(cur_level, character_4);
  //       time_to_reload = get_time();
  //     }
  //   }
  //
  //   if (get_time() - time_to_redisplay > TIME_TO_REDISPLAY) {
  //     write(1,"\033[2J\n",sizeof("\033[2J\n"));
  //
  //     reset_character_state(playable_character);
  //     reset_character_state(character_2);
  //     reset_character_state(character_3);
  //     reset_character_state(character_4);
  //
  //     check_bombs_timer(cur_level);
  //     display_screen(game_data);
  //     time_to_redisplay = get_time();
  //   }
  // }
  // sleep(3);
  // write(1,"\033[2J\n",sizeof("\033[2J\n"));
  // if (game_state(game_data) == GAME_PLAYABLE_CHARACTER_IS_DEAD) {
  //   write(1,"Game is lost",sizeof("Game is lost"));
  // }
  // else if (game_state(game_data) == GAME_IS_WON) {
  //   write(1,"You won the game",sizeof("You won the game"));
  // }
  // free(game_data);
  // sleep(3);
  // launch_menu();
  // return 1;
}



int launch_game(int ai) {
  t_game_data *game_data = NULL;

  game_data = malloc(sizeof(t_game_data));

  if (game_data == NULL) {
    return -1;
  }

  game_data->level = generate_level_from_file("./level/testlevel.lvl");

  struct termios termios_p;
  tcgetattr(1, &termios_p);
  termios_p.c_lflag &= ~ICANON;
  termios_p.c_lflag &= ~ECHO;
  tcsetattr(1, 0, &termios_p);

  char buf[1];
  struct pollfd fds[1];

  fds[0].fd = 0;
  fds[0].events = POLLIN;

  t_character *playable_character = game_data->playable_character = &game_data->level->characters[0];
  t_character *character_2 = &game_data->level->characters[1];
  t_character *character_3 = &game_data->level->characters[2];
  t_character *character_4 = &game_data->level->characters[3];

  t_level *cur_level = game_data->level;

  int time_to_reload = get_time();
  int time_to_redisplay = get_time();
  write(1,"\033[2J\n",sizeof("\033[2J\n"));
  while(game_state(game_data) != GAME_PLAYABLE_CHARACTER_IS_DEAD && game_state(game_data) != GAME_IS_WON) {
    if (poll(fds, 1, 50) > 0) {
      if(fds[0].revents & POLLIN) {
        read(0, buf, 1);
        action(cur_level, playable_character, buf[0]);
      }
    }

    if (ai == 2){
      if (get_time() - time_to_reload > TIME_TO_REPLAY_IA) {
        ai_play(cur_level, character_2);
        ai_play(cur_level, character_3);
        ai_play(cur_level, character_4);
        time_to_reload = get_time();
      }
    }

    if (get_time() - time_to_redisplay > TIME_TO_REDISPLAY) {
      write(1,"\033[2J\n",sizeof("\033[2J\n"));

      reset_character_state(playable_character);
      reset_character_state(character_2);
      reset_character_state(character_3);
      reset_character_state(character_4);

      check_bombs_timer(cur_level);
      display_screen_ascii(game_data);
      time_to_redisplay = get_time();
    }
  }
  sleep(3);
  write(1,"\033[2J\n",sizeof("\033[2J\n"));
  if (game_state(game_data) == GAME_PLAYABLE_CHARACTER_IS_DEAD) {
    write(1,"Game is lost",sizeof("Game is lost"));
  }
  else if (game_state(game_data) == GAME_IS_WON) {
    write(1,"You won the game",sizeof("You won the game"));
  }
  free(game_data);
  sleep(3);
  launch_menu();
  return 1;
}
