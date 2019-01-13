typedef struct s_bomb {
  int state;
  int range;
  int position_x;
  int position_y;
  int time_state_has_changed;
  int time_to_explode_millis;
  struct s_bomb *next_bomb;
  struct s_bomb *prev_bomb;
} t_bomb;
