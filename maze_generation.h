void fill_array_with_wall(char **maze, int width, int height);
int *list_walls(int width, int height);
// int *list_cells(int width, int height);
char **generate_empty_layer(t_game_settings *settings);
char **generate_maze_layer(t_game_settings *settings);
char **generate_bomb_layer(t_game_settings *settings);
char **generate_bonus_layer(t_game_settings *settings);
t_level *generate_maze_level(t_game_settings *settings);
