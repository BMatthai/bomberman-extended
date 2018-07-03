t_level *generate_level_from_file(char *file);
int get_one_dim(int fd);
char **get_level_layer_raw(int fd, int lines, int columns);
char **get_bomb_layer(int lines, int columns);
int count_characters(t_level *level);
void init_characters(t_level *level);
t_character *get_level_characters(t_level *level);
