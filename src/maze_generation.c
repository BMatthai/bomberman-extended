#ifndef T_LEVEL
#define T_LEVEL
#include "../include/struct_level.h"
#endif

#include "../include/struct_game_settings.h"

#include "../include/character_creation.h"
#include "../include/game_constants.h"

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

int count_walls_separator(int width, int height) {
  return (((height - 1) * (width - 1)) - 1) / 2;
}

int count_walls(int width, int height) {
  if ((width % 2) == 1 && (height % 2) == 1) {
    return ((height * width) + 1) / 2;
  }
  else {
    return (height * width) / 2;
  }
}

int count_cells(int width, int height) {
  int count_cells;

  count_cells = (height * width) / 4;
  if (width % 2 == 1 && height % 2 == 0) {
    count_cells += height / 2;
  }
  // if  (width % 2 == 0 && height % 2 == 1) {
  //   count_cells += width / 2;
  // }
  // if  (width % 2 == 1 && height % 2 == 1) {
  //   count_cells += 1;
  // }


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

int *list_walls(int width, int height) {
  int size = count_walls(width, height);
  int *walls = malloc(sizeof(int) * size);

  int k = 0;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
        if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) {
            walls[k] = i * width + j;
            k++;
        }
      }
    }
    return walls;
  }

int *list_cells(int width, int height) {
  int size = count_cells(width, height);
  int *cells = malloc(sizeof(int) * size);

  int k = 0;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (i % 2 == 1 && j % 2 == 0) {
          cells[k] = i * width + j;
          k++;
      }
    }
  }
  return cells;
}


t_character *get_level_characters(t_level *level) {

  int number_characters;
  t_character *characters = NULL;

  number_characters = level->number_characters;

  int height;
  int width;

  height = level->height;
  width = level->width;

  int *cells = list_cells(width, height);
  int nb_cells = count_cells(width, height);

  characters = malloc(sizeof(t_character) * number_characters);
  shuffle(cells, nb_cells);

  int x_cur;
  int y_cur;

  for (int i = 0; i < number_characters; i++) {
    y_cur = cells[i] / width;
    x_cur = cells[i] % width;
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
    // printf("%d - ",cur_elt->value);

    cur_elt = cur_elt->next_elt;
  }
  printf("\n");


}

void list_all_sets(t_set *sets) {
  t_set *cur_set = NULL;
  int i = 0;
  cur_set = sets;
  // printf("Liste des sets :\n");
  while (cur_set != NULL) {
    // printf("    Nouveau set :\n");
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

void fill_maze_default(int *cells, char **maze, int width, int height) {
  int size = count_cells(width, height);

  int cur_row;
  int cur_col;
  int value;

  for (int i = 0; i < height; i ++) {
    for (int j = 0; j < width; j ++) {
      maze[j][i] = '0';

    }
  }

  for(int k = 0; k < size; k++) {
    value = cells[k];
    cur_row = value / width;
    cur_col = value % width;

    maze[cur_col][cur_row] = ' ';
  }

}

int is_wall_separator(int wall_index, int width, int height) {
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

int init_cell(int width, int i) {
  int cur_row;
  int value;

  //voir curRow

  if (width % 2 == 0) {
    cur_row = (2 * i) / width;
    value = ((2 * i + 1) % width) + (2 * cur_row * width);
  }
  else {
    //voir currow ici
    cur_row = (2 * i) / width;
    value = ((2 * i + 1) % width) + (2 * cur_row * width);
  }

  return value;
}

t_set *init_sets(int *cells, int width, int height) {

  int size = count_cells(width, height);

  int i = 0;

  t_set *cur_set = NULL;
  t_set *prev_set = NULL;

  t_set *first_set = NULL;
  first_set = malloc(sizeof(t_set));
  first_set->prev_set = NULL;
  first_set->first = malloc(sizeof(t_element));
  first_set->first->value = cells[i];
  first_set->first->next_elt = NULL;
  first_set->first->prev_elt = NULL;

  prev_set = first_set;

  for (i = 1; i < size; i++) {
    cur_set = malloc(sizeof(t_set));
    cur_set->first = malloc(sizeof(t_element));
    cur_set->first->value = cells[i];

    cur_set->first->next_elt = NULL;
    cur_set->first->prev_elt = NULL;

    cur_set->prev_set = prev_set;
    cur_set->prev_set->next_set = cur_set;
    prev_set = cur_set;
  }
  cur_set->next_set = NULL;

  return first_set;
}

char **generate_empty_layer(int width, int height) {
  char **maze = NULL;

  maze = malloc(width * sizeof(char *));
  for (int i = 0; i < width; i++) {
    maze[i] = malloc(sizeof(char) * height);
  }
  return maze;
}

void remove_wall(char **maze, int wall_index, t_game_settings *settings) {
  int cur_row;
  int cur_col;
  int width = settings->width;
  int proba_destr_wall;
  int proba_empty;
  int rand_number;

  cur_row = wall_index / width;
  cur_col = wall_index % width;
  proba_destr_wall = settings->proba_destr_wall;
  proba_empty = settings->proba_empty;
  rand_number = (rand() % (101));

  if (rand_number <= proba_destr_wall)
    maze[cur_col][cur_row] = '1';
  else
    maze[cur_col][cur_row] = ' ';
}

void set_wall_content(char **maze, int wall_index, t_game_settings *settings) {
  int cur_row;
  int cur_col;
  int width = settings->width;
  int proba_destr_wall;
  int proba_empty;
  int rand_number;

  cur_row = wall_index / width;
  cur_col = wall_index % width;
  proba_destr_wall = settings->proba_destr_wall;
  proba_empty = settings->proba_empty;
  rand_number = (rand() % (101));

  if (rand_number <= proba_destr_wall)
    maze[cur_col][cur_row] = '1';
  else if (rand_number <= proba_empty + proba_destr_wall)
    maze[cur_col][cur_row] = ' ';
}

int is_a_cell(int value, int width, int height) {
  int cur_row;
  int cur_value;

  for (int i = 0; i < count_cells(width, height); i++) {
    cur_row = (2 * i) / width;
    cur_value = ((2 * i + 1) % width) + (2 * cur_row * width);
      if (cur_value == value) {
        return YES;
      }
  }
  return NO;
}

t_set *set_from_value(t_set *sets, int value, int width, int height) {

  if (value >= (height * width)) {
    return NULL;
  }

  t_set *cur_set = NULL;
  t_element *cur_elt = NULL;

  cur_set = sets;

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


void dig_walls(char **maze, int *cells, t_game_settings *settings) {
  int nb_walls;
  int width;
  int height;
  int *walls = NULL;
  t_set *sets = NULL;


  width = settings->width;
  height = settings->height;

  walls = list_walls(width, height);
  nb_walls = count_walls(width, height);
  sets = init_sets(cells, width, height);

  int is_cur_row_even;
  int wall_index;
  shuffle(walls, nb_walls);

  for (int i = 0; i < nb_walls; i++) {
    wall_index = walls[i];
    is_cur_row_even = ((wall_index / width) % 2) == 1 ? NO : YES;
    t_set *set1 = NULL;
    t_set *set2 = NULL;

    int cell_side_A;
    int cell_side_B;

    if (is_cur_row_even == YES) {
      cell_side_A = wall_index - width;
      cell_side_B = wall_index + width;

    }
    else {
      cell_side_A = wall_index - 1;
      cell_side_B = wall_index + 1;
    }
    set1 = set_from_value(sets, cell_side_A, width, height);
    set2 = set_from_value(sets, cell_side_B, width, height);

    if (set1 != NULL && set2 != NULL) {
      if (is_same_set(set1, set2) == NO) {
        remove_wall(maze, wall_index, settings);
        merge_sets(set1, set2);
      }
      else {
        set_wall_content(maze, wall_index, settings);
      }
    }
    else {
    }
  }
}

char **generate_maze_layer(t_game_settings *settings) {
  char **maze = NULL;
  int *cells = NULL;
  int width = settings->width;
  int height = settings->height;

  cells = list_cells(width, height);

  maze = generate_empty_layer(width, height);
  fill_maze_default(cells, maze, width, height);
  dig_walls(maze, cells, settings);
  return maze;
}

char **generate_bomb_layer(t_game_settings *settings) {
  char **maze = NULL;
  int width;
  int height;

  width = settings->width;
  height = settings->height;

  maze = generate_empty_layer(width, height);

  return maze;
}

char **generate_bonus_layer(t_game_settings *settings) {
  char **maze = NULL;
  int width;
  int height;

  width = settings->width;
  height = settings->height;

  maze = generate_empty_layer(width, height);

  return maze;
}

t_level *generate_maze_level(t_game_settings *settings) {
  t_level *level;
  level = malloc(sizeof(t_level));

  if (level == NULL) {
    return NULL;
  }

  int width = settings->width;
  int height = settings->height;

  level->width = width;
  level->height = height;

  level->terrain = generate_maze_layer(settings);
  level->bomb = generate_bomb_layer(settings);
  level->bonus = generate_bonus_layer(settings);
  level->first_bomb = NULL;

  level->number_characters = 4;
  level->characters = get_level_characters(level);

  return level;
}
