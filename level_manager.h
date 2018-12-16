int tile_is_wall(t_level *level, int x, int y);
int tile_is_destructible_wall(t_level *level, int x, int y);
int tile_is_character(t_level *level, int x, int y);
int tile_is_bomb_planted(t_level *level, int x, int y);
int tile_is_bomb_exploding(t_level *level, int x, int y);
int tile_is_free(t_level *level, float x, float y);
int tile_character(t_level *level, int x, int y);
int tile_is_bonus(t_level *level, int x, int y);
int tile_is_bomb_blast(t_level *level, int x, int y);
int tile_content(t_level *level, int x, int y);
int tile_is_free_for_bomb(t_level *level, int x, int y);
int tile_is_free_bomb_blast(t_level *level, int x, int y);
int tile_exists(t_level *level, int x, int y);
