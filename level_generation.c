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

//Generate a level from a file
t_level generate_level_from_file(char *file) {

  int fd;
  t_level level;

  char lines;
  char columns;

  fd = open("./level/testlevel.lvl", O_RDONLY);

  level.lines = get_one_dim(fd);
  level.columns = get_one_dim(fd);
  level.terrain = get_level_layer(fd, lines, columns);

  return level;
}

int get_one_dim(int fd) {
  char *str;
  read(fd, str, 2);
  lseek(fd, 1, SEEK_CUR);
  return atoi(str);
}

char **get_level_layer(int fd, int lines, int columns) {
  char **terrain = null;

  terrain = malloc(lines * sizeof(char*));
  for (int i = 0; i < level.lines; i++) {
    level.terrain[i] = malloc(sizeof(char) * level.columns);
    read(fd, level.terrain[i], level.columns);
    lseek(fd, 1, SEEK_CUR);
  }
  return terrain;
}






//Generetate level
// t_level generate_level_randomly(int width, int height) {
//
// }
//
// int free_level(t_level *level) {
//
// }
//
// char *read_file_line(int fd) {
//   read();
// }
