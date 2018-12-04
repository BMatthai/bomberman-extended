CC=gcc
CFLAGS=
CFLAGSE=-W -Wall -Werror -pedantic -std=c99
LDFLAGS=
EXEC=bomberman
BUILD_DIR=./build
BIN_DIR=./bin
SOURCE_DIR=./src

all: $(EXEC)

bomberman: $(BUILD_DIR)/bomberman.o $(BUILD_DIR)/level_generation.o $(BUILD_DIR)/character_creation.o $(BUILD_DIR)/display_level.o $(BUILD_DIR)/action.o $(BUILD_DIR)/bomb_manager.o $(BUILD_DIR)/time_manager.o $(BUILD_DIR)/level_manager.o $(BUILD_DIR)/menu_manager.o $(BUILD_DIR)/game_manager.o $(BUILD_DIR)/client_manager.o $(BUILD_DIR)/server_manager.o $(BUILD_DIR)/ai_manager.o
	$(CC) -o bomberman $(BUILD_DIR)/bomberman.o $(BUILD_DIR)/level_generation.o $(BUILD_DIR)/character_creation.o $(BUILD_DIR)/display_level.o $(BUILD_DIR)/action.o $(BUILD_DIR)/bomb_manager.o $(BUILD_DIR)/time_manager.o $(BUILD_DIR)/level_manager.o $(BUILD_DIR)/menu_manager.o $(BUILD_DIR)/game_manager.o $(BUILD_DIR)/client_manager.o $(BUILD_DIR)/server_manager.o $(BUILD_DIR)/ai_manager.o $(LDFLAGS)

display_level.o: $(SOURCE_DIR)/display_level.c
	$(CC) -o $(BUILD_DIR)/display_level.o -c $(SOURCE_DIR)/display_level.c $(CFLAGS)

level_generation.o: $(SOURCE_DIR)/level_generation.c
	$(CC) -o $(BUILD_DIR)/level_generation.o -c $(SOURCE_DIR)/level_generation.c $(CFLAGS)

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

level_manager.o: $(SOURCE_DIR)/level_manager.c
	$(CC) -o $(BUILD_DIR)/level_manager.o -c $(SOURCE_DIR)/level_manager.c $(CFLAGS)

menu_manager.o: $(SOURCE_DIR)/menu_manager.c
	$(CC) -o $(BUILD_DIR)/menu_manager.o -c $(SOURCE_DIR)/menu_manager.c $(CFLAGS)

game_manager.o: $(SOURCE_DIR)/game_manager.c
	$(CC) -o $(BUILD_DIR)/game_manager.o -c $(SOURCE_DIR)/game_manager.c $(CFLAGS)

client_manager.o: $(SOURCE_DIR)/client_manager.c
	$(CC) -o $(BUILD_DIR)/client_manager.o -c $(SOURCE_DIR)/client_manager.c $(CFLAGS)

server_manager.o: $(SOURCE_DIR)/server_manager.c
	$(CC) -o $(BUILD_DIR)/server_manager.o -c $(SOURCE_DIR)/server_manager.c $(CFLAGS)

ai_manager.o: $(SOURCE_DIR)/ai_manager.c
	$(CC) -o $(BUILD_DIR)/ai_manager.o -c $(SOURCE_DIR)/ai_manager.c $(CFLAGS)


clean:
	rm -rf $(BUILD_DIR)/*.o

mrproper: clean
	rm -rf $(EXEC)
