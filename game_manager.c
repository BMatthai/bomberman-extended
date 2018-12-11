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
#include "level_manager.h"

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
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, STANDARD_WIN_WIDTH, STANDARD_WIN_HEIGHT, 0);

 Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

 SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, render_flags);

 SDL_Surface *image_free = SDL_LoadBMP("resources/free.bmp");
 SDL_Surface *image_wall = SDL_LoadBMP("resources/wall.bmp");

 SDL_Surface *image_char1 = SDL_LoadBMP("resources/char1.bmp");
 SDL_Surface *image_char2 = SDL_LoadBMP("resources/char2.bmp");
 SDL_Surface *image_char3 = SDL_LoadBMP("resources/char3.bmp");
 SDL_Surface *image_char4 = SDL_LoadBMP("resources/char4.bmp");

 if(!image_free) {
     printf("Erreur de chargement de l'image : %s",SDL_GetError());
     return -1;
 }

 SDL_Texture *texture_free = SDL_CreateTextureFromSurface(renderer, image_free);
 SDL_Texture *texture_wall = SDL_CreateTextureFromSurface(renderer, image_wall);

 SDL_Texture *texture_char1 = SDL_CreateTextureFromSurface(renderer, image_char1);
 SDL_Texture *texture_char2 = SDL_CreateTextureFromSurface(renderer, image_char2);
 SDL_Texture *texture_char3 = SDL_CreateTextureFromSurface(renderer, image_char3);
 SDL_Texture *texture_char4 = SDL_CreateTextureFromSurface(renderer, image_char4);

 SDL_Texture *texture_chars[4] = {texture_char1, texture_char2, texture_char3, texture_char4};

 t_game_data *game_data = NULL;
 game_data = malloc(sizeof(t_game_data));
 if (game_data == NULL) {
   return -1;
 }
 game_data->level = generate_level_from_file("./level/testlevel.lvl");
 game_data->playable_character = &game_data->level->characters[0];
 t_character *playable_character = game_data->playable_character;
 t_character *character_2 = &game_data->level->characters[1];
 t_character *character_3 = &game_data->level->characters[2];
 t_character *character_4 = &game_data->level->characters[3];

 t_level *level = game_data->level;
 int lines = level->lines;
 int columns = level->columns;

  int is_running = YES;
  int offset_x = ((STANDARD_WIN_WIDTH / 2) - ((columns * STANDARD_TILE_WIDTH) / 2));
  int offset_y = STANDARD_WIN_HEIGHT - (lines * STANDARD_TILE_HEIGHT);

  int time_to_reload = get_time();

  while (is_running)
  {

    SDL_PollEvent(&event);
    SDL_RenderClear(renderer);

    switch (event.type)
    {
      case SDL_QUIT:
        is_running = NO;
        break;
      case SDL_KEYDOWN:
          switch (event.key.keysym.sym)
          {
              case SDLK_LEFT:  action(level, playable_character, ACTION_LEFT); break;
              case SDLK_RIGHT: action(level, playable_character, ACTION_RIGHT); break;
              case SDLK_UP:    action(level, playable_character, ACTION_UP); break;
              case SDLK_DOWN:  action(level, playable_character, ACTION_DOWN); break;
          }
        break;
      //
      // case SDL_KEYUP:
      //   action(level, playable_character, ACTION_RIGHT);
      //   break;
    }
    SDL_Rect location;


    SDL_Rect dstrect;
    for (int i = 0; i < lines; i++) {
      for (int j = 0; j < columns; j++) {
        location.h = STANDARD_TILE_HEIGHT;
        location.w = STANDARD_TILE_WIDTH;
        location.x = STANDARD_TILE_WIDTH * j + offset_x;
        location.y = STANDARD_TILE_HEIGHT * i + offset_y;
        // //dstrect = { j * STANDARD_TILE_WIDTH, i * STANDARD_TILE_HEIGHT, STANDARD_TILE_WIDTH, STANDARD_TILE_HEIGHT };
        // //SDL_Rect dstrect = { 5, 5, 320, 240 };
        //SDL_RenderCopy(renderer, texture_free, NULL, &location);

        if (tile_is_wall(level, j, i) == YES) {
          SDL_RenderCopy(renderer, texture_wall, NULL, &location);
        }
        else {
          SDL_RenderCopy(renderer, texture_free, NULL, &location);
        }
      }

      location.h = STANDARD_TILE_HEIGHT;
      location.w = STANDARD_TILE_WIDTH;
      location.x = STANDARD_TILE_WIDTH * level->characters[0].position_x + offset_x;
      location.y = STANDARD_TILE_HEIGHT * level->characters[0].position_y + offset_y;

      SDL_RenderCopy(renderer, texture_char1, NULL, &location);


      // for (int k = 0; k < level->number_characters; k++) {
      //
      // }



      // if (get_time() - time_to_reload > TIME_TO_REPLAY_IA) {
      //       //ai_play(level, character_2);
      //       ai_play(level, character_3);
      //       // ai_play(level, character_4);
      //       time_to_reload = get_time();
      // }




    }

    SDL_RenderPresent(renderer);

  }

  SDL_DestroyTexture(texture_free);
  SDL_DestroyTexture(texture_wall);

  SDL_FreeSurface(image_free);
  SDL_FreeSurface(image_wall);

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
