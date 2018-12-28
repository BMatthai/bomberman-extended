#define STANDARD_TILE_WIDTH 16
#define STANDARD_TILE_HEIGHT 16
#define STANDARD_WIN_WIDTH 1024
#define STANDARD_WIN_HEIGHT 768

#define MOVE_DISTANCE 0.03


#define ACTION_UP 1
#define ACTION_DOWN 2
#define ACTION_LEFT 3
#define ACTION_RIGHT 4
#define ACTION_BOMB 5

#define CHARACTER_HEAL_POINT 5
#define CHARACTER_BOMB_RANGE 2
#define CHARACTER_BOMB_DAMAGE 1
#define CHARACTER_NUMBER_BOMB 1
#define CHARACTER_MOVEMENT_SPEED 10
#define CHARACTER_TIME_TO_BOMB_EXPLODE 3000
#define CHARACTER_DEAD 0
#define CHARACTER_ALIVE 1
#define CHARACTER_HITTED 2
#define CHARACTER_TIME_HITTED 500

#define BOMB_IS_NOT_PLACED 0
#define BOMB_IS_PLACED_ON_GROUND 1
#define BOMB_IS_EXPLODING 2
#define BOMB_HAS_EXPLODED 3
#define BOMB_IS_UNSTABLE 4
#define BOMB_TIME_BLAST_EXPLOSION 500
#define BOMB_UNSTABLE_DURATION 500

#define WALL_INDESTRUCTIBLE 48
#define WALL_SQUISHY 49
#define WALL_STRONG 57

#define TILE_FREE 32
#define TILE_WITH_WALL_ZERO 48
#define TILE_WITH_WALL_ONE 49
#define TILE_WITH_WALL_TWO 50
#define TILE_WITH_WALL_THREE 51
#define TILE_WITH_WALL_FOUR 52
#define TILE_WITH_WALL_FIVE 53
#define TILE_WITH_WALL_SIX 54
#define TILE_WITH_WALL_SEVEN 55
#define TILE_WITH_WALL_HEIGHT 56
#define TILE_WITH_WALL_NINE 57
#define TILE_WITH_BOMB_ORIGIN 79
#define TILE_WITH_BOMB 64
#define TILE_WITH_BOMB_EXP_DOWN 118
#define TILE_WITH_BOMB_EXP_UP 94
#define TILE_WITH_BOMB_EXP_LEFT 60
#define TILE_WITH_BOMB_EXP_RIGHT 62
#define TILE_WITH_PLAYER_A 65
#define TILE_WITH_PLAYER_B 66
#define TILE_WITH_PLAYER_C 67
#define TILE_WITH_PLAYER_D 68
#define TILE_WITH_BONUS_1 43
#define TILE_WITH_BONUS_2 42
#define TILE_WITH_BONUS_3 35

#define GAME_IS_NOT_EXISTING 0
#define GAME_IS_WILL_BEGIN 1
#define GAME_IS_RUNNING 2
#define GAME_PLAYABLE_CHARACTER_IS_DEAD 3
#define GAME_ALL_CHARACTERS_ARE_DEAD 4
#define GAME_IS_WON 5
#define GAME_IS_ENDED 6

#define IS_SAFE 0
#define IS_IN_BOMB_RANGE 1

#define YES 1
#define NO 0

#define EVEN 1
#define ODD 0

#define MOVE_POSSIBLE 1
#define MOVE_IMPOSSIBLE 0

#define TIME_TO_REPLAY_IA 200 //Default 200
#define TIME_TO_REDISPLAY 40 //Default 50

#define PROBA_EMPTY 00
#define PROBA_DESTRUCTIBLE 00

#define MENU_MONOPLAYER 0
#define MENU_MULTIPLAYER 1
#define MENU_QUIT 2

#define PATH_LEVEL = "./level/"
