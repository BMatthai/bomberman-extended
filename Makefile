CC=gcc
CFLAGS=
CFLAGSE=-W -Wall -Werror -pedantic -std=c99
LDFLAGS=
EXEC=bomberman

all: $(EXEC)

bomberman: bomberman.o level_generation.o character_creation.o display_level.o action.o bomb_manager.o time_manager.o level_manager.o menu_manager.o game_manager.o client_manager.o server_manager.o ai_manager.o color_manager.o
	$(CC) -o bomberman bomberman.o level_generation.o character_creation.o display_level.o action.o bomb_manager.o time_manager.o level_manager.o menu_manager.o game_manager.o client_manager.o server_manager.o ai_manager.o color_manager.o $(LDFLAGS)

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

client_manager.o: client_manager.c
	$(CC) -o client_manager.o -c client_manager.c $(CFLAGS)

server_manager.o: server_manager.c
	$(CC) -o server_manager.o -c server_manager.c $(CFLAGS)

ai_manager.o: ai_manager.c
	$(CC) -o ai_manager.o -c ai_manager.c $(CFLAGS)

color_manager.o: color_manager.c
	$(CC) -o color_manager.o -c color_manager.c $(CFLAGS)


clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
