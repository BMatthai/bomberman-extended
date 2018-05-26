#include "struct_level.h"
#include "display_level.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>

// int display_level(t_level my_level) {
//   for(int i = 0; i < my_level.lines; i++) {
//       write(1, my_level.terrain[i], my_level.columns);
//       write(1, "\n", strlen("\n"));
//   }
// }

int display_level(t_level my_level) {
  for(int i = 0; i < my_level.lines; i++) {
    for(int j = 0; j < my_level.columns; j++) {
        write(1, &my_level.terrain[i][j], 1);
    }
    write(1, "\n", strlen("\n"));
  }
  return 0;
}
