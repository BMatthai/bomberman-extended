#ifndef T_LEVEL
#define T_LEVEL
#include "struct_level.h"
#endif

#include "character_creation.h"
#include "game_constants.h"

#include <stdio.h>
#include <stdlib.h>



int isAChar(char tile) {
  if (tile == 'A' || tile == 'B' ||  tile == 'C' ||  tile == 'D')
    return 1;
  return 0;
}

t_character *get_level_characters(t_level *level) {
  int i;
  int j;
  int k;
  int number_characters;
  t_character *characters;

  number_characters = level->number_characters;
  characters = malloc(sizeof(t_character) * number_characters);
  k = 0;
  for(i = 0; i < level->lines; i++) {
    for(j = 0; j < level->columns; j++) {
      if (isAChar(level->terrain[i][j])) {
        characters[k] = create_character(level->terrain[i][j], j, i);
        level->terrain[i][j] = ' ';
        k++;
      }
    }
  }
  return characters;
}

int count_characters(t_level *level) {
  int i;
  int j;
  int number_characters;

  number_characters = 0;
  for(i = 0; i < level->lines; i++) {
    for(j = 0; j < level->columns; j++) {
      if (isAChar(level->terrain[i][j]))
        number_characters++;
    }
  }
  level->number_characters = number_characters;
  return number_characters;
}

typedef struct s_element {
    int value;
    struct s_element *next;
} t_element;

typedef struct s_set {
    struct s_element *first;
} t_set;

int is_same_set(t_set *set1, t_set *set2) {
  if (set1 == NULL || set2 == NULL) {
    return NO;
  }

  t_element *cur_elt1 = NULL;
  t_element *cur_elt2 = NULL;

  cur_elt1 = set1->first;
  cur_elt2 = set2->first;

  int value_elt1 = cur_elt1->value;
  int value_elt2 = cur_elt2->value;

  while (cur_elt1 != NULL) {
    // printf("%d et %d\n", cur_elt1->value, value_elt2);
    if (cur_elt1->value == value_elt2) {
      return YES;
    }
    cur_elt1 = cur_elt1->next;
  }

  while(cur_elt2 != NULL) {
    if (cur_elt2->value == value_elt1) {
      return YES;
    }
    cur_elt2 = cur_elt2->next;
  }
  return NO;
}

void merge_sets(t_set *set1, t_set *set2) {
  if (set1 == NULL || set2 == NULL) {
    return;
  }

  t_element *cur_elt = NULL;

  cur_elt = set1->first;
  while(cur_elt != NULL) {
    cur_elt = cur_elt->next;
  };
  cur_elt->next = set2->first;
}

int count_walls(int height, int width) {
  return (height * width) / 2;
}

int count_cells(int height, int width) {
  return (height * width) / 4;
}

void fill_array_with_wall(char **maze, int height, int width) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      maze[j][i] = '0';
    }
  }
}

void shuffle(int *walls, int height, int width) {
  int size = count_walls(height, width);

  if (size > 1) {
      int i;
      for (i = 0; i < size - 1; i++) {
        int j = i + rand() / (RAND_MAX / (size - i) + 1);
        int t = walls[j];
        walls[j] = walls[i];
        walls[i] = t;
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

t_set *create_sets(int height, int width) {
  int size = count_cells(height, width);

  t_set *set = NULL;
  set = malloc(size * sizeof(t_set));

  int cur_row;
  int value;
  for (int i = 0; i < size; i++) {
    cur_row = (2 * i) / width;
    value = ((2 * i + 1) % width) + (2 * cur_row * width);
    set[i].first = malloc(sizeof(t_element));
    set[i].first->value = value;

    set[i].first->next = NULL;
  }
  return set;
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
  maze[j][i] = ' ';
}

t_set *set_from_value(t_set *sets, int value, int height, int width) {
  int size = count_cells(height, width);

  t_element *cur_elt;
  for (int i = 0; i < size; i++) {
    cur_elt = sets[i].first;
    while (cur_elt != NULL) {
      if (cur_elt->value == value) {
        return &sets[i];
      }
      cur_elt = cur_elt->next;
    }
  }
  return NULL;
}

void dig_walls(char **maze, int *walls, int height, int width) {
  int size = count_walls(height, width);

  t_set *sets = create_sets(height, width);

  int is_even;
  int wall_index;

  for (int i = 0; i < size; i++) {
    wall_index = walls[i];
    is_even = ((wall_index / width) % 2) == 1 ? NO : YES;
    t_set *set1 = NULL;
    t_set *set2 = NULL;

    // printf("%d est pair ? %d\n", wall_index, is_even);
    if (is_even == YES) {
      // printf("%d et %d\n", wall_index - 1, wall_index + 1);
      set1 = set_from_value(sets, wall_index - 1, height, width);
      set2 = set_from_value(sets, wall_index + 1, height, width);
    }
    else {
      // printf("%d et %d\n", wall_index - width, wall_index + width);
      set1 = set_from_value(sets, wall_index - width, height, width);
      set2 = set_from_value(sets, wall_index + width, height, width);
    }

    if (is_same_set(set1, set2) == NO) {
      remove_wall(maze, height, width, wall_index);
      merge_sets(set1, set2);
    }
  }
}

char **generate_maze(int height, int width) {
  char **maze;

  maze = generate_empty_layer(height, width);
  fill_array_with_wall(maze, height, width);

  int *walls = list_walls(height, width);

  // for(int i=0;i< count_walls(height, width); i++) {
  //   printf("%d \n", walls[i]);
  // }



  shuffle(walls, height, width);

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
  level->number_characters = count_characters(level);
  level->characters = get_level_characters(level);

  return level;
}
