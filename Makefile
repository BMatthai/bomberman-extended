CC=gcc
CFLAGS=-W -Wall -Werror -pedantic -std=c99 -I/usr/include -L/usr/local/lib/cmake
LDFLAGS=
EXEC=bomberman



all: $(EXEC)

bomberman: bomberman.o level_generation.o character_creation.o display_level.o action.o bomb_manager.o time_manager.o level_manager.o menu_manager.o game_manager.o
	$(CC) -o bomberman bomberman.o level_generation.o character_creation.o display_level.o action.o bomb_manager.o time_manager.o level_manager.o menu_manager.o game_manager.o $(LDFLAGS)

display_level.o: display_level.c
	$(CC) -o display_level.o -c display_level.c $(CFLAGS)

level_generation.o: level_generation.c
	$(CC) -o level_generation.o -c level_generation.c $(CFLAGS)

character_creation.o: character_creation.c
	$(CC) -o character_creation.o -c character_creation.c $(CFLAGS)

bomberman.o: bomberman.c
	$(CC) -o bomberman.o -c bomberman.c $(CFLAGS)

action.o: action.c
	$(CC) -o action.o -c action.c $(CFLAGS)

bomb_manager.o: bomb_manager.c
	$(CC) -o bomb_manager.o -c bomb_manager.c $(CFLAGS)

time_manager.o: time_manager.c
	$(CC) -o time_manager.o -c time_manager.c $(CFLAGS)

level_manager.o: level_manager.c
	$(CC) -o level_manager.o -c level_manager.c $(CFLAGS)

menu_manager.o: menu_manager.c
	$(CC) -o menu_manager.o -c menu_manager.c $(CFLAGS)

game_manager.o: game_manager.c
	$(CC) -o game_manager.o -c game_manager.c $(CFLAGS)


clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
