typedef struct s_bomb {
  char symbol;
  int range;
  int position_x;
  int position_y;
  int time_placed;
  int time_to_explode;
  struct s_bomb *next_bomb;
} t_bomb;
