

int display_level(my_level) {

  for(int i = 0; i < my_level.terrain; i++) {
      write(1, my_level.terrain[i]);
  }
  return 2;
}
