#include "color_manager.h"
#include "game_constants.h"

#include <unistd.h>
#include <string.h>

void set_color(char *color) {
  write(1, color, strlen(color));
}

void set_color_normal() {
  set_color("\e[0;0m");
}

void set_color_red() {
  set_color("\e[40;31m");
}

void set_color_green() {
  set_color("\e[40;32m");
}

void set_color_yellow() {
  set_color("\e[40;33m");
}

void set_color_blue() {
  set_color("\e[40;34m");
}

void set_color_magenta() {
  set_color("\e[40;35m");
}

void set_color_cyan() {
  set_color("\e[40;36m");
}

void set_color_black() {
  set_color("\e[30;40m");
}

void set_color_white() {
  set_color("\e[37;0m");
}

void set_color_light_gray() {
  set_color("\e[30;47;0m");
}

void set_color_dark_gray() {
  set_color("\e[37;47;1m");
}

void set_color_hud() {
  set_color("\e[30;43m");
}
