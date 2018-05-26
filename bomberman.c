#include "struct_level.h"
#include "level_generation.h"
#include "display_level.h"

int main(int argc, char **argv) {

    t_level my_level;

    my_level = generate_level_from_file("test");

    display_level(my_level);



}
