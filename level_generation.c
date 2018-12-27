// #ifndef T_LEVEL
// #define T_LEVEL
// #include "struct_level.h"
// #include "character_creation.h"
// #include "level_generation.h"
// #endif
//
//
// #include "tile_manager.h"
// #include "log_manager.h"
//
// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <unistd.h>
//
// #include <stdio.h>
//
// #include <time.h>
//
//
// int isAChar(char tile);
//
// void CarveMaze(char **maze, int width, int height, int x, int y) {
//
//    int x1, y1;
//    int x2, y2;
//    int dx, dy;
//    int dir, count;
//
//    dir = rand() % 4;
//    count = 0;
//    while(count < 3) {
//       dx = 0; dy = 0;
//       switch(dir) {
//       case 0:  dx = 1;  break;
//       case 1:  dy = 1;  break;
//       case 2:  dx = -1; break;
//       default: dy = -1; break;
//       }
//       x1 = x + dx;
//       y1 = y + dy;
//       x2 = x1 + dx;
//       y2 = y1 + dy;
//       if(   x2 > 0 && x2 < width && y2 > 0 && y2 < height
//          && maze[x1][y1] == '0' && maze[x2][y2] == '0') {
//          maze[x1][y1] = ' ';
//          maze[x2][y2] = ' ';
//          x = x2; y = y2;
//          dir = rand() % 4;
//          count = 0;
//       } else {
//          dir = (dir + 1) % 4;
//          count += 1;
//       }
//    }
//
// }
//
//
// t_level *generate_level_random() {
//   t_level *level;
//
//   level = malloc(sizeof(t_level));
//
//   if (level == NULL) {
//     return NULL;
//   }
//
//
//   int lines = 21;
//   int columns = 21;
//   level->lines = lines;
//   level->columns = columns;
//
//    char **empty_level = generate_empty_layer(lines, columns);
//    for(int i = 0; i < lines; i++) {
//       for(int j = 0; j < columns; j++) {
//         empty_level[j][i] = '0';
//       }
//    }
//
//    srand(time(0));
//    for(int i = 0; i < lines; i++) {
//       for(int j = 0; j < columns; j++) {
//         CarveMaze(empty_level, columns, lines, j, i);
//       }
//
//    }
//
//     for(int i = 0; i < lines; i++) {
//      empty_level[0][i] = '0';
//      empty_level[columns - 1][i] = '0';
//     }
//
//     for(int i = 0; i < columns; i++) {
//      empty_level[i][0] = '0';
//      empty_level[i][lines - 1] = '0';
//     }
//
//    empty_level[4][4] = 'A';
//    empty_level[5][5] = 'B';
//
//    level->terrain = empty_level;
//
//    level->bonus = generate_empty_layer(level->columns, level->lines);
//
//    level->bomb = generate_empty_layer(level->columns, level->lines);
//
//    level->number_characters = count_characters(level);
//    level->characters = get_level_characters(level);
//
//   // level->bonus = generate_empty_layer(40, 64);
//   //
//   //
//   // level->bomb = generate_empty_layer(level->columns, level->lines);
//   // level->number_characters = 4;
//   //level->characters = get_level_characters(level);
//
//   return level;
// }
//
//
// t_level *generate_level_from_file(char *path) {
//   int fd;
//   t_level *level;
//
//   fd = open(path, O_RDONLY);
//
//   level = malloc(sizeof(t_level));
//
//   if (level == NULL) {
//     return NULL;
//   }
//
//   level->lines = get_one_dim(fd);
//   level->columns = get_one_dim(fd);
//   level->terrain = get_level_layer_raw(fd, level->columns, level->lines);
//   level->bonus = get_level_layer_raw(fd, level->columns, level->lines);
//   level->bomb = generate_empty_layer(level->columns, level->lines);
//   level->number_characters = count_characters(level);
//   level->characters = get_level_characters(level);
//
//   close(fd);
//   return level;
// }
//
// //To read the first line of the level file (number of lines, number of columns)
// int get_one_dim(int fd) {
//   char str[2];
//   read(fd, str, 2);
//   lseek(fd, 1, SEEK_CUR);
//   return atoi(str);
// }
//
// char **get_level_layer_raw(int fd, int lines, int columns) {
//   char **terrain_layer;
//
//   terrain_layer = malloc(lines * sizeof(char*));
//   for (int i = 0; i < lines; i++) {
//     terrain_layer[i] = malloc(sizeof(char) * columns);
//     read(fd, terrain_layer[i], columns);
//     lseek(fd, 1, SEEK_CUR);
//   }
//   return terrain_layer;
// }
//
// //Count the number of characters in the level.
// int count_characters(t_level *level) {
//   int i;
//   int j;
//   int number_characters;
//
//   number_characters = 0;
//   for(i = 0; i < level->lines; i++) {
//     for(j = 0; j < level->columns; j++) {
//       if (isAChar(level->terrain[i][j]))
//         number_characters++;
//     }
//   }
//   level->number_characters = number_characters;
//   return number_characters;
// }
//
// t_character *get_level_characters(t_level *level) {
//   int i;
//   int j;
//   int k;
//   int number_characters;
//   t_character *characters;
//
//   number_characters = level->number_characters;
//   characters = malloc(sizeof(t_character) * number_characters);
//   k = 0;
//   for(i = 0; i < level->lines; i++) {
//     for(j = 0; j < level->columns; j++) {
//       if (isAChar(level->terrain[i][j])) {
//         characters[k] = create_character(level->terrain[i][j], j, i);
//         level->terrain[i][j] = ' ';
//         k++;
//       }
//     }
//   }
//   return characters;
// }
//
// char **generate_empty_layer(int lines, int columns) {
//   char **layer;
//
//   layer = malloc(lines * sizeof(char*));
//   for (int i = 0; i < lines; i++) {
//     layer[i] = malloc(sizeof(char) * columns);
//   }
//   return layer;
// }
//
// int isAChar(char tile) {
//   if (tile == 'A' || tile == 'B' ||  tile == 'C' ||  tile == 'D')
//     return 1;
//   return 0;
// }
