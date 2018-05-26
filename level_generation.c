#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

int get_one_dim(int fd);
char **get_level_layer(int fd, int lines, int columns);

t_level generate_level_from_file(char *path) {
  int fd;
  t_level level;

  fd = open(path, O_RDONLY);

  level.lines = get_one_dim(fd);
  level.columns = get_one_dim(fd);
  level.terrain = get_level_layer(fd, level.lines, level.columns);
  level.bonus = get_level_layer(fd, level.lines, level.columns);
  close(fd);
  return level;
}

int get_one_dim(int fd) {
  char str[2];
  read(fd, str, 2);
  lseek(fd, 1, SEEK_CUR);
  return atoi(str);
}

char **get_level_layer(int fd, int lines, int columns) {
  char **terrain_layer;

  terrain_layer = malloc(lines * sizeof(char*));
  for (int i = 0; i < lines; i++) {
    terrain_layer[i] = malloc(sizeof(char) * columns);
    read(fd, terrain_layer[i], columns);
    lseek(fd, 1, SEEK_CUR);
  }
  return terrain_layer;
}
