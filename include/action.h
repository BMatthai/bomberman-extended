void put_bomb();
void set_velocity_character(t_character *character, int velocity_x, int velocity_y);
void move(t_level *level, t_character *character, int direction);
void action(t_level *level, t_character *character, int touch_action);
void move_char(t_level *level, t_character *character);
void adjust_char(t_character *character);
void motion_char(t_level *level, t_character *character);
void put_bomb(t_level *level, t_character *character);
void pick_item(t_level *level, t_character *character);
