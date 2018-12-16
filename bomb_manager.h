int is_in_bomb_range(t_level *level, t_bomb *bomb, int position_x, int position_y);
int is_position_in_any_bomb_range(t_level *level, int position_x, int position_y);
void explode_bomb(t_level *level, t_bomb *bomb);
void bomb_has_exploded(t_level *level, t_bomb *bomb);
void check_bombs_timer(t_level *level);
t_bomb *bomb_at_pos(t_level *level, int position_x, int position_y);
void damage_tile(t_level *level, int position_x, int position_y);
void remove_bomb_from_list(t_level *level, t_bomb *bomb);
void set_exploding_routine(t_level *level, t_bomb *bomb);
