#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#include "global_handler.h"

void refresh_delay();
void start_game();
void display_main_menu_window(struct globals *glb);
void display_main_game_screen(struct globals *glb);
void display_shop_items(struct globals *glb);
void display_shop_item_details(struct globals *glb);
void shop_buy_item(struct item_holder *item, struct globals *glb);
void display_camp_screen(struct globals *glb);
void display_skills_screen(struct globals *glb);
void heal_char(struct globals *glb);
void display_storage_items(struct globals *glb);
void display_storage_item_details(struct globals *glb);
void char_use_item(struct item_holder* item, struct globals *glb);
void char_remove_item(struct item_holder *item, struct globals *glb);
void storage_sell_item(struct item_holder *item, struct globals *glb);
void display_monster_hunt_screen(struct globals *glb);
void monster_encounter(int monster_sel, struct globals *glb);
void add_to_textbuf(char text[],char *textbuf, int *p, int h, struct globals *glb);
void display_textbuf(int x, int y, char *textbuf, int p, int h, struct globals *glb);
short make_rand_key();
void draw_key_request(int x, int y, short rand_key, unsigned short color, struct globals *glb);
void game_over_screen(struct globals *glb);
void update_stat_screen(struct globals *glb);
void run_new_game(struct globals *glb);
void set_next_xp(struct globals *glb);
void display_options(struct globals *glb);
void exit_game(struct globals *glb);

#endif
