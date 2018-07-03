#ifndef T_GAME_DATA
#define T_GAME_DATA
#include "struct_game_data.h"
#endif

#include "game_constants.h"
#include "game_manager.h"

int game_state(t_game_data *game_data) {
  if(game_data->playable_character->heal_points >= CHARACTER_ALIVE) {
    return GAME_IS_RUNNING;
  }
  return GAME_PLAYABLE_CHARACTER_IS_DEAD;
}
