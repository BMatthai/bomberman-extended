#ifndef T_LEVEL;
#define T_LEVEL
#include "level.h"
#endif


//Generetate level
t_level generate_level_randomly(int width, int height) {

}

//Generate a level from a file
t_level generate_level_from_file(char *file) {

  int fd;
  t_level level;

  char lines;
  char columns;

  *level.terrain = malloc(lines * sizeof(char*));
  fd = open("./level/testlevel.lvl", O_RDONLY);

  lines = 10;
  columns = 14;

  for (int i = 0; i < lines; i++) {
    *level.terrain[i] = malloc(sizeof(char) * columns);
    read(fd, *level.terrain[i], count);
    lseek(fd, 1, SEEK_CUR);
  }
  return level;
}

int free_level(t_level *level) {

}

char *read_file_line(int fd) {
  read();
}
