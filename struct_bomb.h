typedef struct s_bomb {
  char symbol;
  int range;
  int position_x;
  int position_y;
  int time_placed;
  int time_to_explode;
  struct s_bomb *next_bomb;
  struct s_bomb *prev_bomb;
} t_bomb;
