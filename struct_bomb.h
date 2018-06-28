typedef struct s_bomb {
  int range;
  int position_x;
  int position_y;
  int tte; //time to explode;
  t_bomb *next_bomb;
} t_bomb;
