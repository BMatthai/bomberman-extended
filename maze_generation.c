

void fill_array_with_wall(char **maze, int height, int width) {
  for (int i = 0; i < height, i++) {
    for (int j = 0; j < width, j++) {
      maze[j][i] = '0';
    }
  }
}

void shuffle() {

}

wall *list_walls() {
  
}

char **generate_empty_layer(int height, int width) {
  char **layer;

  layer = malloc(lines * sizeof(char*));
  for (int i = 0; i < lines; i++) {
    layer[i] = malloc(sizeof(char) * columns);
  }
  return layer;
}

char **generate_maze(int height, int width) {
  char **maze;

  maze = generate_empty_layer(height, width);


}
