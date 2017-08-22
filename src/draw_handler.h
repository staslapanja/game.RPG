
#ifndef DRAW_HANDLER_H
#define DRAW_HANDLER_H

#include "global_handler.h"
#include "input_handler.h"

void init_draw(struct globals* glb);
void create_selectWindowChar_buf(struct globals* glb);
void create_selectWindowColor_buf(struct globals* glb);
void create_statusWindowChar_buf(struct globals* glb);
void create_statusWindowColor_buf(struct globals* glb);
void create_infoWindowChar_buf(struct globals* glb);
void create_infoWindowColor_buf(struct globals* glb);
void clear_selectWindow_buf(struct globals* glb);
void clear_statusWindow_buf(struct globals* glb);
void clear_infoWindow_buf(struct globals* glb);
void draw_framework_win_console(struct globals *globals);
void reset_cursor(struct globals *globals);
void refresh_selWin_win_console(struct globals *glb);
void text_selectWindow_buf(int x, int y, char text[], unsigned short color, struct globals *glb);
void refresh_statWin_win_console(struct globals *glb);
void text_statusWindow_buf(int x, int y, char text[], unsigned short color, struct globals *glb);
void refresh_infoWin_win_console(struct globals *glb);
void text_infoWindow_buf(int x, int y, char text[], unsigned short color, struct globals *glb);
void draw_main_game_background(struct globals *glb);

void refresh_selWin(struct globals *glb);
void draw_framework(struct globals *glb);
void refresh_statWin(struct globals *glb);
void draw_splash_screen(struct globals *glb);
void refresh_infoWin(struct globals *glb);

#endif
