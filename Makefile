CC=gcc
CFLAGS=-W -Wall -Werror -pedantic -std=c99
LDFLAGS=-I./include -lSDL2_ttf -lSDL2
EXEC=bomberman
BUILD_DIR=./build
BIN_DIR=
SOURCE_DIR=./src

all: $(EXEC)

bomberman: bomberman.o character_creation.o action.o bomb_manager.o time_manager.o tile_manager.o game_manager.o log_manager.o maze_generation.o display_game.o display_menu.o init_display.o
	$(CC) -o bomberman $(BUILD_DIR)/bomberman.o $(BUILD_DIR)/character_creation.o $(BUILD_DIR)/action.o $(BUILD_DIR)/bomb_manager.o $(BUILD_DIR)/time_manager.o $(BUILD_DIR)/tile_manager.o $(BUILD_DIR)/game_manager.o $(BUILD_DIR)/log_manager.o $(BUILD_DIR)/maze_generation.o $(BUILD_DIR)/display_game.o $(BUILD_DIR)/display_menu.o $(BUILD_DIR)/init_display.o $(LDFLAGS)

maze_generation.o: $(SOURCE_DIR)/maze_generation.c
	$(CC) -o $(BUILD_DIR)/maze_generation.o -c $(SOURCE_DIR)/maze_generation.c $(CFLAGS)

character_creation.o: $(SOURCE_DIR)/character_creation.c
	$(CC) -o $(BUILD_DIR)/character_creation.o -c $(SOURCE_DIR)/character_creation.c $(CFLAGS)

bomberman.o: $(SOURCE_DIR)/bomberman.c
	$(CC) -o $(BUILD_DIR)/bomberman.o -c $(SOURCE_DIR)/bomberman.c $(CFLAGS)

action.o: $(SOURCE_DIR)/action.c
	$(CC) -o $(BUILD_DIR)/action.o -c $(SOURCE_DIR)/action.c $(CFLAGS)

bomb_manager.o: $(SOURCE_DIR)/bomb_manager.c
	$(CC) -o $(BUILD_DIR)/bomb_manager.o -c $(SOURCE_DIR)/bomb_manager.c $(CFLAGS)

time_manager.o: $(SOURCE_DIR)/time_manager.c
	$(CC) -o $(BUILD_DIR)/time_manager.o -c $(SOURCE_DIR)/time_manager.c $(CFLAGS)

tile_manager.o: $(SOURCE_DIR)/tile_manager.c
	$(CC) -o $(BUILD_DIR)/tile_manager.o -c $(SOURCE_DIR)/tile_manager.c $(CFLAGS)

game_manager.o: $(SOURCE_DIR)/game_manager.c
	$(CC) -o $(BUILD_DIR)/game_manager.o -c $(SOURCE_DIR)/game_manager.c $(CFLAGS)

log_manager.o: $(SOURCE_DIR)/log_manager.c
	$(CC) -o $(BUILD_DIR)/log_manager.o -c $(SOURCE_DIR)/log_manager.c $(CFLAGS)

display_game.o: $(SOURCE_DIR)/display_game.c
	$(CC) -o $(BUILD_DIR)/display_game.o -c $(SOURCE_DIR)/display_game.c $(CFLAGS)

display_menu.o: $(SOURCE_DIR)/display_menu.c
	$(CC) -o $(BUILD_DIR)/display_menu.o -c $(SOURCE_DIR)/display_menu.c $(CFLAGS)

init_display.o: $(SOURCE_DIR)/init_display.c
	$(CC) -o $(BUILD_DIR)/init_display.o -c $(SOURCE_DIR)/init_display.c $(CFLAGS)


clean:
	rm -rf $(BUILD_DIR)/*.o

mrproper: clean
	rm -rf $(EXEC)
