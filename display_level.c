#include "struct_level.h"
#include "display_level.h"
#include <unistd.h>

#include <stdio.h>
int display_level(t_level my_level) {
  for(int i = 0; i < sizeof(my_level.terrain); i++) {
      write(1, my_level.terrain[i], my_level.columns);
  }
}
