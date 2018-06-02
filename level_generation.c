#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#include "character_creation.h"
#include "level_generation.h"
#endif

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

//To read a level layer (wall/bonus)
//char **get_level_layer_raw(int fd, int lines, int columns);

t_level generate_level_from_file(char *path) {
  int fd;
  t_level level;

  fd = open(path, O_RDONLY);

  level.lines = get_one_dim(fd);
  level.columns = get_one_dim(fd);
  level.terrain = get_level_layer_raw(fd, level.lines, level.columns);
  level.bonus = get_level_layer_raw(fd, level.lines, level.columns);
  level.characters = get_level_characters(level);
  close(fd);
  return level;
}

//To read the first line of the level file (number of lines, number of columns)
int get_one_dim(int fd) {
  char str[2];
  read(fd, str, 2);
  lseek(fd, 1, SEEK_CUR);
  return atoi(str);
}

char **get_level_layer_raw(int fd, int lines, int columns) {
  char **terrain_layer;

  terrain_layer = malloc(lines * sizeof(char*));
  for (int i = 0; i < lines; i++) {
    terrain_layer[i] = malloc(sizeof(char) * columns);
    read(fd, terrain_layer[i], columns);
    lseek(fd, 1, SEEK_CUR);
  }
  return terrain_layer;
}

//Count the number of characters in the level.
int count_characters(t_level level) {
  int i;
  int j;
  int number_characters;

  number_characters = 0;
  for(i = 0; i < level.lines; i++) {
    for(j = 0; j < level.columns; j++) {
      if (level.terrain[i][j] == 'A')
        number_characters++;
    }
  }
  level.number_characters = number_characters;
  return number_characters;
}

t_character *get_level_characters(t_level level) {
  int i;
  int j;
  int k;
  int number_characters;
  t_character *characters;

  number_characters = level.number_characters;
  characters = malloc(sizeof(t_character) * number_characters);
  for(i = 0; i < level.lines; i++) {
    for(j = 0; j < level.columns; j++) {
      if (level.terrain[i][j] == 'A')
        for(k = 0; k < number_characters; k++)
          characters[k] = create_character(level.terrain[i][j], i, j);
        level.terrain[i][j] = ' ';
    }
  }
  return characters;
}