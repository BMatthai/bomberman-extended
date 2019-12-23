typedef struct s_character {
  int heal_points;
  int bomb_damage;
  int symbol;
  char bomb_range;
  char number_bomb_planted;
  char stock_bomb;
  char movement_speed;
  int time_to_bomb_explode_millis;
  float position_x;
  float position_y;

  int velocity_x;
  int velocity_y;

  int state;
  int time_state_has_changed;
}   t_character;
