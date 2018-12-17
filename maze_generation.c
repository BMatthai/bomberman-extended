#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif

#include "character_creation.h"

#include <stdio.h>
#include <stdlib.h>



int isAChar(char tile) {
  if (tile == 'A' || tile == 'B' ||  tile == 'C' ||  tile == 'D')
    return 1;
  return 0;
}

t_character *get_level_characters(t_level *level) {
  int i;
  int j;
  int k;
  int number_characters;
  t_character *characters;

  number_characters = level->number_characters;
  characters = malloc(sizeof(t_character) * number_characters);
  k = 0;
  for(i = 0; i < level->lines; i++) {
    for(j = 0; j < level->columns; j++) {
      if (isAChar(level->terrain[i][j])) {
        characters[k] = create_character(level->terrain[i][j], j, i);
        level->terrain[i][j] = ' ';
        k++;
      }
    }
  }
  return characters;
}

int count_characters(t_level *level) {
  int i;
  int j;
  int number_characters;

  number_characters = 0;
  for(i = 0; i < level->lines; i++) {
    for(j = 0; j < level->columns; j++) {
      if (isAChar(level->terrain[i][j]))
        number_characters++;
    }
  }
  level->number_characters = number_characters;
  return number_characters;
}

void fill_array_with_wall(char **maze, int height, int width) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      maze[j][i] = '0';
    }
  }
}

// void shuffle() {
//
// }

int *list_walls(int height, int width) {
  int size_needed = (height * width) / 2;
  int *walls = malloc(sizeof(int) * size_needed);

  for (int i = 0; i < size_needed; i++) {
    if (((i * 2 / width) % 2) == 0) {
      walls[i] = i * 2;
    }
    else {
      walls[i] = i * 2 + 1;
    }
    printf("%d\n", walls[i]);
  }
  return walls;
}

// Create a list of all walls, and create a set for each cell, each containing just that one cell.
// For each wall, in some random order:
// If the cells divided by this wall belong to distinct sets:
// Remove the current wall.
// Join the sets of the formerly divided cells.

char **generate_empty_layer(int height, int width) {
  char **layer;

  layer = malloc(height * sizeof(char*));
  for (int i = 0; i < height; i++) {
    layer[i] = malloc(sizeof(char) * width);
  }
  return layer;
}

char **generate_maze(int height, int width) {
  char **maze;

  maze = generate_empty_layer(height, width);
  fill_array_with_wall(maze, height, width);

  int *index = list_walls(height, width);

  return maze;
}

t_level *generate_maze_level(int height, int width) {
  t_level *level;
  level = malloc(sizeof(t_level));

  if (level == NULL) {
    return NULL;
  }

  level->lines = height;
  level->columns = width;
  level->terrain = generate_maze(height, width);
  level->bonus = generate_empty_layer(level->lines, level->columns);
  level->bomb = generate_empty_layer(level->lines, level->columns);
  level->number_characters = count_characters(level);
  level->characters = get_level_characters(level);

  return level;
}
