#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif

#include "game_constants.h"
#include "character_creation.h"
#include "action.h"
#include "ai_manager.h"
#include "bomb_manager.h"
#include "level_manager.h"

#include <math.h>
#include <stdlib.h>


t_character *choose_target(t_level *level, t_character *character) {
	int target_player_number;
	t_character *target;
	target = &level->characters[0];

	while (1) {
		target_player_number = rand() % level->number_characters;
		target = &level->characters[target_player_number];
		if (target != character && target->state != CHARACTER_DEAD) {
			return target;
		}
	}
}

void chase_target(t_level *level, t_character *character, int target_pos_x, int target_pos_y) {
	int r;

	int character_pos_x = character->position_x;
	int character_pos_y = character->position_y;

	if (tile_is_destructible_wall(level, character_pos_x + 1, character_pos_y)
		|| tile_is_destructible_wall(level, character_pos_x - 1, character_pos_y)
		|| tile_is_destructible_wall(level, character_pos_x, character_pos_y - 1)
		|| tile_is_destructible_wall(level, character_pos_x, character_pos_y + 1))
		{
			put_bomb(level, character);
		}

	if (tile_is_character(level, character_pos_x + 1, character_pos_y)
		|| tile_is_character(level, character_pos_x - 1, character_pos_y)
		|| tile_is_character(level, character_pos_x, character_pos_y - 1)
		|| tile_is_character(level, character_pos_x, character_pos_y + 1))
		{
		put_bomb(level, character);
	}
	else {
		int did_moved;
		int dir;
		r = rand() % 7;
		if (r < 3) {
			if (character_pos_x > target_pos_x && is_position_in_any_bomb_range(level, character_pos_x - 1, character_pos_y) == IS_SAFE) {
				dir = 2;
				did_moved = move_to_dir(level, character, 2);
			}
			else if (character_pos_x < target_pos_x && is_position_in_any_bomb_range(level, character_pos_x + 1, character_pos_y) == IS_SAFE) {
				dir = 3;
				did_moved = move_to_dir(level, character, 3);
			}
		}
		else if (r < 6) {
			if (character_pos_y > target_pos_y && is_position_in_any_bomb_range(level, character_pos_x, character_pos_y - 1) == IS_SAFE) {
				dir = 0;
				did_moved = move_to_dir(level, character, 0);
			}
			else if (character_pos_y < target_pos_y  && is_position_in_any_bomb_range(level, character_pos_x, character_pos_y + 1) == IS_SAFE) {
				dir = 1;
				did_moved = move_to_dir(level, character, 1);
			}
		}
		if (did_moved == MOVE_IMPOSSIBLE) {
			if (dir == 2 || dir == 0)
				did_moved = move_to_dir(level, character, (dir + 2 + (rand() % 2)) % 4);
			else if (dir == 1 || dir == 3)
					did_moved = move_to_dir(level, character, (dir + 1 + (rand() % 2)) % 4);
		}
	}
}

void ai_play(t_level *level, t_character *character) {
	int cur_position_x;
	int cur_position_y;

	int new_pos_x;
	int new_pos_y;
	int r;

	if (character->state != CHARACTER_DEAD) {
		cur_position_x = character->position_x;
		cur_position_y = character->position_y;

	t_character *target = choose_target(level, character);
	if (is_character_in_bomb_range(level, character) == IS_IN_BOMB_RANGE) {

			r = rand() % 4;
			move_to_dir(level, character, r);
	}
	else {
		if (rand() % 20 == 0) {
			target = choose_target(level, character);
		}

		chase_target(level, character, target->position_x, target->position_y);
	}
	}
}
