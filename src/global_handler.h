#ifndef GLOBALS_HANDLER_H
#define GLOBALS_HANDLER_H

#include <stdio.h>
#include <windows.h>

//global variables
struct xy{
    short x;
    short y;
};

struct game_stat{
    int skip_wait_keypress;
    int game_active;
    int shop_updated;
    float buy_mod;
    float sell_mod;
    int combat_phase;
    int game_over;
    float next_xp;
    int glb_count;
};

struct char_stat{
    char  name[19];
    float credits;
    float damage;
    float damage_mod;
    float defence;
    float defence_mod;
    float max_health;
    float health;
    float health_mod;
    int level;
    float xp;
    float xp_mod;
    float rep;
    float rep_mod;
    float max_weight;
    float max_weight_mod;
    float weight;
};

struct globals{
    //main variables
    struct  item_holder *p_items_list   ;
    int                 item_list_num   ;
    struct  item_holder *p_select_item  ;
    int                 select_item_num ;
    struct  item_holder *p_storage_item ;
    int                 storage_item_num;
    struct  item_holder *p_use_item     ;
    int                 monster_list_num;
    struct monster_object *p_monster_list   ;
    int                 state           ;
    short               input_key       ;
    short               input_mouse     ;
    short               input_toggle    ;
    struct  xy          cursor_pos      ;
    struct  xy          dwSize          ;
    struct  xy          selWinSize      ;
    struct  xy          statWinSize     ;
    struct  xy          infoWinSize     ;
    //draw buffers
    char                *p_selWinCharBuf    ;
    unsigned short      *p_selWinColorBuf   ;
    char                *p_statWinCharBuf   ;
    unsigned short      *p_statWinColorBuf  ;
    char                *p_infoWinCharBuf   ;
    unsigned short      *p_infoWinColorBuf  ;
    //menu
    struct menu_holder  *menu_sel       ;
    //system specific
    struct  console_handles *p_conhandles   ;
	//log file handle
	FILE                *fp             ;
	//game status
	struct game_stat    game_stat       ;
	//character status
	struct char_stat    char_stat       ;
};

void globals_default(struct globals *globals);
void globals_reset_game(struct globals *globals);
void globals_reset_char(struct globals *globals);

#endif /* GLOBALS_HANDLER_H */
