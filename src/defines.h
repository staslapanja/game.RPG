#ifndef DEFINES_H
#define DEFINES_H

//menu states
#define _MAIN_MENU 1
#define _SHOP_MENU 2
#define _STORAGE_MENU 3
#define _PLAY_SCREEN 4
#define _SHOW_ITEM 5

//define screen
#define SELECT_WINDOW_WIDTH 53
#define SELECT_WINDOW_HEIGHT 21

#define INFO_WINDOW_WIDTH SELECT_WINDOW_WIDTH
#define INFO_WINDOW_HEIGHT 2

#define STATUS_WINDOW_WIDTH 20
#define STATUS_WINDOW_HEIGHT SELECT_WINDOW_HEIGHT + 2 + INFO_WINDOW_HEIGHT - 1

#define CONSOLE_WIDTH 2 + SELECT_WINDOW_WIDTH + 3 + STATUS_WINDOW_WIDTH + 2
#define CONSOLE_HEIGHT 2 + STATUS_WINDOW_HEIGHT + 2

//item struct parameters
#define STAT_NUM 3
#define NAME_SIZE 46
#define CAT_SIZE 20

//log file
#define LOG_FILE "run.log"

//version
#define GAME_VERSION "0.9.00"

#endif
