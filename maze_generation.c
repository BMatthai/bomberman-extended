#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif

#include "character_creation.h"
#include "game_constants.h"

#include <stdio.h>
#include <stdlib.h>

#include <time.h>


typedef struct s_element {
    int value;
    struct s_element *prev_elt;
    struct s_element *next_elt;
} t_element;

typedef struct s_set {
    struct s_element *first;
    struct s_set *prev_set;
    struct s_set *next_set;
} t_set;

int count_walls(int height, int width) {
  return (height * width) / 2;
}

int count_cells(int height, int width) {
  return (height * width) / 4;
}

void shuffle(int *elts, int nb_elts) {
  srand((unsigned)time(NULL));

  for (int i = 0; i < nb_elts - 1; i++) {
    int j = i + rand() / (RAND_MAX / (nb_elts - i) + 1);
    int t = elts[j];
    elts[j] = elts[i];
    elts[i] = t;
  }
}

// int isAChar(char tile) {
//   if (tile == 'A' || tile == 'B' ||  tile == 'C' ||  tile == 'D')
//     return 1;
//   return 0;
// }

int *list_cells(int height, int width) {
  int size = count_cells(height, width);
  int *cells = malloc(sizeof(int) * size);

  int cur_row;
  int value;

  for (int i = 0; i < size; i++) {
    cur_row = (2 * i) / width;
    value = ((2 * i + 1) % width) + (2 * cur_row * width);

    cells[i] = value;
  }
  return cells;
}

t_character *get_level_characters(t_level *level) {
  // int i;
  // int j;
  // int k;
  // int number_characters;
  // t_character *characters;
  //
  // number_characters = level->number_characters;
  // k = 0;
  // for(i = 0; i < level->lines; i++) {
  //   for(j = 0; j < level->columns; j++) {
  //     if (isAChar(level->terrain[i][j])) {
  //
  //       level->terrain[i][j] = ' ';
  //       k++;
  //     }
  //   }
  // }
  // return characters;

  int number_characters;
  t_character *characters = NULL;

  number_characters = level->number_characters;

  int height;
  int width;

  height = level->lines;
  width = level->columns;

  int *cells = list_cells(height, width);
  int nb_cells = count_cells(height, width);

  characters = malloc(sizeof(t_character) * number_characters);
  shuffle(cells, nb_cells);

  int x_cur;
  int y_cur;

  for (int i = 0; i < number_characters; i++) {
    x_cur = cells[i] / width;
    y_cur = cells[i] % width;
    printf("x : %d et y : %d\n", x_cur, y_cur);
    characters[i] = create_character(TILE_WITH_PLAYER_A + i, x_cur, y_cur);
  }
  return characters;
}

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



t_element *get_head(t_set *set) {
  t_element *cur_elt = NULL;

  cur_elt = set->first;

  while (cur_elt->prev_elt != NULL) {
    printf("Inf\n");
    cur_elt = cur_elt->prev_elt;
  }
  return cur_elt;
}

int is_same_set(t_set *set1, t_set *set2) {
  printf("Testons si les deux sets sont le même\n");
  if (set1 == NULL || set2 == NULL) {
    return NO;
  }

  if (set1 == set2) {
    printf("Valeur sets : %d et %d\n", set1->first->value, set2->first->value);
    return YES;
  }

  t_element *cur_elt1 = NULL;
  t_element *cur_elt2 = NULL;

  cur_elt1 = get_head(set1);

  cur_elt2 = set2->first;

  //int value_elt1 = cur_elt1->value;
  int value_elt2 = cur_elt2->value;

  //printf("Valeur souhaitée : %d\n", value_elt2);

  while (cur_elt1->next_elt != NULL) {
    printf("Cur value : %d", cur_elt1->value);
    if (cur_elt1->value == value_elt2) {
      return YES;
    }
    else {

    }
    cur_elt1 = cur_elt1->next_elt;
  }
  return NO;
}

void list_elt_of_set(t_set *set) {
  if (set == NULL ) {
    return;
  }

  t_element *cur_elt = NULL;

  cur_elt = set->first;

  while(cur_elt != NULL) {
    printf("%d ;", cur_elt->value);

    cur_elt = cur_elt->next_elt;

  }
  printf("\n");
}

void list_all_sets(t_set *sets) {
  t_set *cur_set = NULL;
  int i = 0;
  cur_set = sets;

  while (cur_set->next_set != NULL) {
    printf("Set %d :\n      ", i);

    list_elt_of_set(cur_set);
    cur_set = cur_set->next_set;
    i++;
  }

}


void free_elt_of_set(t_set *set) {
  if (set == NULL ) {
    return;
  }

  t_element *cur_elt = NULL;

  cur_elt = set->first;

  while(cur_elt != NULL) {
    cur_elt = cur_elt->next_elt;
    free(cur_elt->prev_elt);
  }
  free(cur_elt);
}
void free_all_sets(t_set *sets) {
  t_set *cur_set = NULL;
  int i = 0;
  cur_set = sets;

  while (cur_set->next_set != NULL) {

    free_elt_of_set(cur_set);
    cur_set = cur_set->next_set;
    free(cur_set->prev_set);
    i++;
  }

}

// void list_all_sets(t_set *sets) {
//
//   t_set *cur_set = NULL;
//   t_element *cur_elt = NULL;
//
//   cur_set = sets;
//   cur_elt = cur_set->first;
//   while(cur_set->next_set != NULL) {
//     printf("First : %d\n", cur_set->first->value);
//     cur_set = cur_set->next_set;
//   }
// }

t_element *last_of_set(t_set *set) {
  t_element *cur_elt = NULL;

  cur_elt = set->first;

  while (cur_elt->next_elt != NULL) {
    cur_elt = cur_elt->next_elt;
  }

  return cur_elt;
}

void delete_set(t_set *set) {
  t_set *prev_set = NULL;
  t_set *next_set = NULL;

  prev_set = set->prev_set;
  next_set = set->next_set;

  if (set->next_set != NULL && prev_set != NULL) {
    prev_set->next_set = set->next_set;
  }

  if (set->prev_set != NULL && next_set != NULL) {
    next_set->prev_set = set->prev_set;
  }

  free(set);
}

void merge_sets(t_set *set1, t_set *set2) {
  if (set1 == NULL || set2 == NULL) {
    return;
  }
  printf("On va merger %d et %d.\n", set1->first->value, set2->first->value);

  t_element *cur_elt = NULL;

  cur_elt = last_of_set(set1);

  cur_elt->next_elt = set2->first;

  set2->first->prev_elt = cur_elt;
  printf("FOZOKF\n");

  printf("First value : %d\n", set1->first->value);
  printf("AHBAHCLA\n");
  delete_set(set2);

}

// void merge_sets(t_set *set1, t_set *set2) {
//
//   // printf("Procédure merge\n");
//
//   if (set1 == NULL || set2 == NULL) {
//     return;
//   }
//
//   printf("--------\nOn va merger ");
//   // printf("i : %d\n", i);
//   list_set(set1);
//   printf(" et ");
//   list_set(set2);
//   printf("--------\n");
//
//   t_element *cur_elt = NULL;
//
//   cur_elt = set1->first;
//
//   while (cur_elt->next_elt != NULL) {
//         cur_elt = cur_elt->next_elt;
//   }
//
//   cur_elt->next_elt = set2->first;
//   set2->first->prev_elt = cur_elt;
//   //set2->first = set1->first;
// }



void fill_array(char **maze, int height, int width) {
  int size = count_walls(height, width);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (i % 2 == 0 && j % 2 == 1) {
        maze[j][i] = ' ';
      }
      else {
        maze[j][i] = '0';
      }
    }
  }
}

int *list_walls(int height, int width) {
  int size = count_walls(height, width);
  int *walls = malloc(sizeof(int) * size);

  for (int i = 0; i < size; i++) {
    if (((i * 2 / width) % 2) == 0) {
      walls[i] = i * 2;
    }
    else {
      walls[i] = i * 2 + 1;
    }
  }
  return walls;
}





int init_cell(int height, int width, int i) {
  int cur_row;
  int value;

  cur_row = (2 * i) / width;
  value = ((2 * i + 1) % width) + (2 * cur_row * width);

  return value;
}

t_set *init_sets(int height, int width) {
  int size = count_cells(height, width);

  int i = 0;

  t_set *cur_set = NULL;
  t_set *prev_set = NULL;

  t_set *first_set = NULL;
  first_set = malloc(sizeof(t_set));
  first_set->prev_set = NULL;
  first_set->first = malloc(sizeof(t_element));
  first_set->first->value = init_cell(height, width, i);
  first_set->first->next_elt = NULL;
  first_set->first->prev_elt = NULL;

  prev_set = first_set;

  for (i = 1; i < size; i++) {
    cur_set = malloc(sizeof(t_set));
    cur_set->first = malloc(sizeof(t_element));
    cur_set->first->value = init_cell(height, width, i);

    cur_set->first->next_elt = NULL;
    cur_set->first->prev_elt = NULL;

    cur_set->prev_set = prev_set;
    cur_set->prev_set->next_set = cur_set;
    prev_set = cur_set;
  }
  cur_set->next_set = NULL;




  return first_set;
}


// t_set *create_sets(int height, int width) {
//   int size = count_cells(height, width);
//
//   t_set *set = NULL;
//   set = malloc(size * sizeof(t_set));
//
//   int cur_row;
//   int value;
//   for (int i = 0; i < size; i++) {
//     cur_row = (2 * i) / width;
//     value = ((2 * i + 1) % width) + (2 * cur_row * width);
//     set[i].first = malloc(sizeof(t_element));
//     set[i].first->value = value;
//     set[i].first->next = NULL;
//     set[i].first->prev = NULL;
//   }
//   return set;
// }


char **generate_empty_layer(int height, int width) {
  char **layer;

  layer = malloc(height * sizeof(char*));
  for (int i = 0; i < height; i++) {
    layer[i] = malloc(sizeof(char) * width);
  }
  return layer;
}

void remove_wall(char **maze, int height, int width, int value) {
  int i;
  int j;

  i = value / width;
  j = value % width;
  maze[j][i] = ' ';
}

t_set *set_from_value(t_set *sets, int value, int height, int width) {
  t_set *cur_set = NULL;
  int val_first;
  cur_set = sets;

  while (cur_set->next_set != NULL) {
    printf("Show first\n");
    val_first = cur_set->first->value;
    printf("Showed first\n");
    if (val_first == value) {
      return cur_set;
    }
    cur_set = cur_set->next_set;
  }
  return  NULL;
}

// t_set *set_from_value(t_set *sets, int value, int height, int width) {
//   if (value < 0 || value >= (height * width)) {
//     return NULL;
//   }
//
//   t_set *cur_set = NULL;
//   t_element *cur_elt = NULL;
//
//   cur_set = sets;
//   cur_elt = cur_set->first;
//   while(cur_set->next_set != NULL) {
//
//     while(cur_elt != NULL) {
//
//       //printf("Valeur actuelle : %d et valeur souhaitée : %d\n", cur_elt->value, value);
//       if (cur_elt->value == value) {
//         return cur_set;
//       }
//
//       cur_elt = cur_elt->next_elt;
//
//     }
//
//
//       cur_set = cur_set->next_set;
//       cur_elt = cur_set->first;
//
//   }
//
//   return NULL;
// }

// t_set *set_from_value(t_set *sets, int value, int height, int width) {
//   int size = count_cells(height, width);
//
//   t_element *cur_elt;
//   for (int i = 0; i < size; i++) {
//     cur_elt = sets[i].first;
//     if (cur_elt->value == value) {
//       if (cur_elt->prev == NULL) {
//         return &sets[i];
//       }
//     }
//   }
//   return NULL;
// }

void dig_walls(char **maze, int *walls, int height, int width) {
  int size = count_walls(height, width);

  //t_set *sets = create_sets(height, width);
  t_set *sets = init_sets(height, width);
  //list_all_sets(sets);


  int is_even;
  int wall_index;

  for (int i = 0; i < size; i++) {
    wall_index = walls[i];
    is_even = ((wall_index / width) % 2) == 1 ? NO : YES;
    t_set *set1 = NULL;
    t_set *set2 = NULL;

    int cell_side_A;
    int cell_side_B;

    if (is_even == YES) {
      cell_side_A = wall_index - 1;
      cell_side_B = wall_index + 1;
      printf("%d et %d\n", wall_index - 1, wall_index + 1);
    }
    else {
      cell_side_A = wall_index - width;
      cell_side_B = wall_index + width;
      printf("%d et %d\n", wall_index - width, wall_index + width);
    }

    printf("Mur : %d\n", wall_index);

    set1 = set_from_value(sets, cell_side_A, height, width);
    set2 = set_from_value(sets, cell_side_B, height, width);

    if (set1 == NULL) {
      printf("Cell at %d null (Set 1)\n", cell_side_A);
    }
    if (set2 == NULL) {
      printf("Cell at %d null (Set 2)\n", cell_side_B);
    }

    if (set1 != NULL && set2 != NULL) {
      printf("Les sets ne sont pas nuls\n");
      printf("Val first set 1 : %d\n", set1->first->value);
      printf("Val first set 2 : %d\n", set2->first->value);

      if (is_same_set(set1, set2) == NO) {
        remove_wall(maze, height, width, wall_index);
        merge_sets(set1, set2);
      }
      else {
        printf("C'est déjà le même set...\n");
      }
    }
  }
  //free_all_sets(sets);

}

char **generate_maze(int height, int width) {
  char **maze;

  maze = generate_empty_layer(height, width);
  fill_array(maze, height, width);

  int *walls = list_walls(height, width);

  // for(int i=0;i< count_walls(height, width); i++) {
  //   printf("%d - ", walls[i]);
  // }
  // printf("\n");

  int nb_walls;

  nb_walls = count_walls(height,width);
  shuffle(walls, nb_walls);

  // for(int i=0;i< count_walls(height, width); i++) {
  //   printf("%d - ", walls[i]);
  // }

  dig_walls(maze, walls, height, width);
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
  level->number_characters = 2;
  level->characters = get_level_characters(level);

  return level;
}
