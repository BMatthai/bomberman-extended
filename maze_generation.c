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

int count_walls_separator(int height, int width) {
  return (((height - 1) * (width - 1)) - 1) / 2;
}

int count_walls(int height, int width) {

  return (height * width) / 2;
}

int count_cells(int height, int width) {
  int count_cells;

  count_cells = (height * width) / 4;
  return count_cells;
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
    characters[i] = create_character(TILE_WITH_PLAYER_A + i, x_cur, y_cur);
  }
  return characters;
}

t_element *get_head(t_set *set) {
  t_element *cur_elt = NULL;

  cur_elt = set->first;

  while (cur_elt->prev_elt != NULL) {
    cur_elt = cur_elt->prev_elt;
  }
  return cur_elt;
}

int is_same_set(t_set *set1, t_set *set2) {
  if (set1 == NULL || set2 == NULL) {
    return NO;
  }

  if (set1 == set2) {
    return YES;
  }

  t_element *cur_elt1 = NULL;
  t_element *cur_elt2 = NULL;

  cur_elt1 = get_head(set1);

  cur_elt2 = set2->first;

  int value_elt2 = cur_elt2->value;

  while (cur_elt1->next_elt != NULL) {
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
    // printf("%d ;", cur_elt->value);

    cur_elt = cur_elt->next_elt;

  }
  // printf("\n");
}

void list_all_sets(t_set *sets) {
  t_set *cur_set = NULL;
  int i = 0;
  cur_set = sets;

  while (cur_set != NULL) {

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

  if (prev_set == NULL) {
    set->prev_set = NULL;
  }

  if (next_set == NULL) {
    set->next_set = NULL;
  }

  if (set->next_set != NULL && prev_set != NULL) {
    prev_set->next_set = next_set;
  }

  if (set->prev_set != NULL && next_set != NULL) {
    next_set->prev_set = set->prev_set;
  }
}

void merge_sets(t_set *set1, t_set *set2) {
  if (set1 == NULL || set2 == NULL) {
    return;
  }

  t_element *last_set1 = NULL;
  t_element *first_set2 = NULL;

  last_set1 = last_of_set(set1);
  first_set2 = get_head(set2);


  last_set1->next_elt = first_set2;
  first_set2->prev_elt = last_set1;


  delete_set(set2);
}

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

int is_wall_separator(int wall_index, int height, int width) {
int row;
int col;

row = wall_index / width;
col = wall_index % width;

  if (row == height - 1) {
    return NO;
  }
  if (col == 0) {
    return NO;
  }
  return YES;
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

  int rand_number = (rand() % (100 - 0 + 1));

  if (rand_number > PROBA_EMPTY)
    maze[j][i] = ' ';
  else 
    maze[j][i] = '1';
}

void set_wall_content(char **maze, int height, int width, int wall_index) {
  int i;
  int j;

  i = wall_index / width;
  j = wall_index % width;


  int rand_number = (rand() % (100 - 0 + 1));

  if (rand_number > PROBA_EMPTY)
    maze[j][i] = ' ';
  else if (rand_number > PROBA_DESTRUCTIBLE)
    maze[j][i] = '1';
}

int is_a_cell(int value, int height, int width) {
  int cur_row;
  int cur_value;

  for (int i = 0; i < count_cells(height, width); i++) {
    cur_row = (2 * i) / width;
    cur_value = ((2 * i + 1) % width) + (2 * cur_row * width);
      if (cur_value == value) {
        return YES;
      }
  }
  return NO;
}

t_set *set_from_value(t_set *sets, int value, int height, int width) {

  if (value >= (height * width)) {
    return NULL;
  }

  t_set *cur_set = NULL;
  t_element *cur_elt = NULL;

  cur_set = sets;

  t_element *first = NULL;

  while (cur_set != NULL) {

    cur_elt = get_head(cur_set);

    while (cur_elt != NULL) {
      if (cur_elt->value == value) {
        return cur_set;
      }
      else {
      }
      cur_elt = cur_elt->next_elt;
    }
    cur_set = cur_set->next_set;
  }
  return  NULL;
}


void dig_walls(char **maze, int *walls, int height, int width) {
  int size = count_walls(height, width);

  t_set *sets = init_sets(height, width);

  int is_even;
  int is_separator;
  int wall_index;


  for (int i = 0; i < size; i++) {
    wall_index = walls[i];

    is_separator = is_wall_separator(wall_index, height, width);
    if (is_separator) {
      is_even = ((wall_index / width) % 2) == 1 ? NO : YES;
      t_set *set1 = NULL;
      t_set *set2 = NULL;

      int cell_side_A;
      int cell_side_B;

      if (is_even == YES) {
        cell_side_A = wall_index - 1;
        cell_side_B = wall_index + 1;
      }
      else {
        cell_side_A = wall_index - width;
        cell_side_B = wall_index + width;
      }

      set1 = set_from_value(sets, cell_side_A, height, width);
      set2 = set_from_value(sets, cell_side_B, height, width);

      if (set1 != NULL && set2 != NULL) {

        if (is_same_set(set1, set2) == NO) {
          remove_wall(maze, height, width, wall_index);
          merge_sets(set1, set2);
          // printf("-------\n");
          // list_all_sets(sets);
          // printf("-------\n");
        }
        else {
          set_wall_content(maze, height, width, wall_index);
        }
      }
      else {
      }
    }
    else {
    }
  }
  // printf("-------\n");
  // list_all_sets(sets);
  // printf("-------\n");
}



char **generate_maze(int height, int width) {
  char **maze;

  maze = generate_empty_layer(height, width);
  fill_array(maze, height, width);

  int *walls = list_walls(height, width);

  int nb_walls;

  nb_walls = count_walls(height,width);
  shuffle(walls, nb_walls);

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
  level->number_characters = 4;
  level->characters = get_level_characters(level);

  return level;
}
