void fill_array_with_wall(char **maze, int width, int height);
int *list_walls(int width, int height);
char **generate_empty_layer(int width, int height);
char **generate_maze_layer(int width, int height);
char **generate_bomb_layer(int width, int height);
char **generate_bonus_layer(int width, int height);
t_level *generate_maze_level(int width, int height);
