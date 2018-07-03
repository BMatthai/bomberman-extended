
#include "menu_manager.h"

#include <string.h>

int main(int argc, char **argv) {

    if (argc == 2 && strcmp(argv[1], "term") == 0){
      launch_menu();
    }
    return 0;

}
