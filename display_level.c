#include "struct_level.h"
#include "display_level.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// int display_level(t_level my_level) {
//   for(int i = 0; i < my_level.lines; i++) {
//       write(1, my_level.terrain[i], my_level.columns);
//       write(1, "\n", strlen("\n"));
//   }
// }

char *level_to_display(t_level *my_level) {
  int i;
  int j;
  int k;
  int lines;
  int columns;
  char *level_to_display;

  lines = my_level->lines;
  columns = my_level->columns;

  level_to_display = malloc(sizeof(char) * lines * columns);

  for (i = 0; i < lines; i++) {
    for (j = 0; j < columns; j++) {
      level_to_display[i * columns + j] = my_level->terrain[i][j];
      if (my_level->bomb[i][j] == '^'
      || my_level->bomb[i][j] == 'v'
      || my_level->bomb[i][j] == '>'
      || my_level->bomb[i][j] == '<'
      || my_level->bomb[i][j] == '@'
      || my_level->bomb[i][j] == 'O')
        level_to_display[i * columns + j] = my_level->bomb[i][j];
    }
  }

  for (k = 0; k < my_level->number_characters; k++) {
    level_to_display[my_level->characters[k].position_y * columns + my_level->characters[k].position_x] = my_level->characters[k].symbol;
  }

  return level_to_display;
}


int display_level(t_level *my_level) {

  char *level = level_to_display(my_level);

  for(int i = 0; i < my_level->lines; i++) {
    for(int j = 0; j < my_level->columns; j++) {
        //write(1, &level_to_display[i][j], 1);
        write(1, &level[i * my_level->columns + j], 1);
    }
    write(1, "\n", strlen("\n"));
  }
  return 0;
}
