int is_move_possible(t_level *level, t_character *character, int x, int y);

int is_move_to_top_possible(t_level *level, t_character *character);
int is_move_to_bot_possible(t_level *level, t_character *character);
int is_move_to_left_possible(t_level *level, t_character *character);
int is_move_to_right_possible(t_level *level, t_character *character);
int number_of_direction_possible(t_level *level, t_character *character);
void put_bomb();
int move_to_dir(t_level *level, t_character *character, int dir);
int move(t_level *level, t_character *character, int x, int y);
void action(t_level *level, t_character *character, char touch_action);
