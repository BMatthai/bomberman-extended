#ifndef T_LEVEL
#define T_LEVEL
#include "../include/struct_level.h"
#endif

#include "../include/test.h"
#include "../include/struct_game_settings.h"
#include "../include/maze_generation.h"
#include <stdlib.h>
#include <stdio.h>

void test_generate_mazes_exhaustive() {
  t_game_settings *settings = NULL;
  settings = malloc(sizeof(t_game_settings));

  for(int i = 8; i < 64; i++) {
    printf("Tests maze largeur %d : ", i);
    for(int j = 8; j < 48; j++) {
      printf("%d\n, ", j);
      for(int k = 0; k < 105; k+=5) {
        for(int l = 0; l < 105; l+=5) {
          settings->width = i;
          settings->height = j;
          settings->proba_destr_wall = k;
          settings->proba_empty = l;
          generate_maze_level(settings);
        }
      }
    }
    printf("\n");
  }
}

void test_generate_mazes() {

  t_game_settings *settings = NULL;
  settings = malloc(sizeof(t_game_settings));

  for (int i = 0; i < 10000; i++) {
    settings->width = (rand() % 60) + 5;
    settings->height = (rand() % 44) + 5;
    settings->proba_destr_wall = 5 * (rand() % 21);
    settings->proba_empty = 5 * (rand() % 21);
    generate_maze_level(settings);
    printf("Labyrinthe(%d, %d, %d, %d)\n", settings->width, settings->height, settings->proba_destr_wall, settings->proba_empty);
  }
  printf("10000 mazes have been randomly generated. Considering generation is OK\n");
}

void test_count_wall() {
  if (count_walls(7,11) != 22) {
      printf("Comptage de wall pas ok (7, 11)\n");
  }
  else if (count_walls(8,11) != 27) {
      printf("Comptage de wall pas ok (8, 11)\n");

  }
  else {
    printf("Comptage wall ok\n");

  }
}

void test_count_cells() {
  if (count_cells(7,11) != 15) {
      printf("Comptage de cells pas ok (7, 11)\n");
  }
  else if (count_cells(8,11) != 15) {
      printf("Comptage de cells pas ok (8, 11)\n");
  }
  else {
    printf("Comptage cells ok\n");
  }
}

void test_list_walls() {
 int walls[27] = {10, 12, 14, 17, 19, 21, 26, 28, 30, 33, 35, 37, 42, 44, 46, 49, 51, 53 ,58 , 60, 62, 65, 67, 69, 74, 76, 78};

 int *walls2 = list_walls(8, 11);

  for(int i = 0; i < 27; i++) {
    if (walls[i] != walls2[i]) {
      printf("Il y a un problème à l'indice %d : %d est différent de %d\n", i, walls[i], walls2[i]);
    }
  }
  printf("test walls OK\n");

}

void test_list_cells() {
  int cells[15] = {9, 11, 13, 25, 27, 29, 41, 43, 45, 57, 59, 61, 73, 75, 77};

  int *cells2 = list_cells(8, 11);

  for(int i = 0; i < 15; i++) {
    if (cells[i] != cells[i]) {
      printf("Il y a un problème à l'indice %d : %d est différent de %d", i, cells[i], cells2[i]);
    }
  }
  printf("test cells OK\n");
}

void test_procedure() {
  test_count_wall();
  test_count_cells();
  test_list_walls();
  test_list_cells();
  // test_generate_mazes();
  // test_generate_mazes_exhaustive();
}
