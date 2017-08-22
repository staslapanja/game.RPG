#include "defines.h"
#include "global_handler.h"

void globals_default(struct globals *globals)
{
    //set global variables to default values
    globals->p_items_list       = NULL  ;
    globals->item_list_num      = 0     ;
    globals->p_select_item      = NULL  ;
    globals->select_item_num    = 0     ;
    globals->p_storage_item     = NULL  ;
    globals->storage_item_num   = 0     ;
    globals->p_use_item         = NULL  ;
    globals->monster_list_num   = 0     ;
    globals->p_monster_list     = NULL  ;
    globals->state              = _MAIN_MENU;
    globals->input_key          = 0x0   ;
    globals->input_mouse        = 0x0   ;
    globals->input_toggle       = 0     ;
    globals->cursor_pos.x       = 0     ;
    globals->cursor_pos.y       = 0     ;
    globals->dwSize.x           = CONSOLE_WIDTH;
    globals->dwSize.y           = CONSOLE_HEIGHT;
    globals->selWinSize.x       = SELECT_WINDOW_WIDTH;
    globals->selWinSize.y       = SELECT_WINDOW_HEIGHT;
    globals->statWinSize.x      = STATUS_WINDOW_WIDTH;
    globals->statWinSize.y      = STATUS_WINDOW_HEIGHT;
    globals->infoWinSize.x      = INFO_WINDOW_WIDTH;
    globals->infoWinSize.y      = INFO_WINDOW_HEIGHT;
    globals->p_selWinCharBuf    = NULL;
    globals->p_selWinColorBuf   = NULL;
    globals->p_statWinCharBuf   = NULL;
    globals->p_statWinColorBuf  = NULL;
    globals->p_infoWinCharBuf   = NULL;
    globals->p_infoWinColorBuf  = NULL;
    //menu
    globals->menu_sel           = NULL;
    //system specific
    globals->p_conhandles       = NULL;
    //log file
//    FILE *fp = NULL;
//    fp = fopen(LOG_FILE, "w+");
//    if ( fp == NULL ) {
//        exit(0);
//    }
//    globals->fp = fp;
    globals->fp = NULL;
	//game status
	globals->game_stat.skip_wait_keypress = 0;
	globals->game_stat.game_active = 0;
	globals->game_stat.shop_updated = 0 ;
	globals->game_stat.buy_mod = 1;
	globals->game_stat.sell_mod = 0.7;
	globals->game_stat.combat_phase = 0;
	globals->game_stat.game_over = 0;
	globals->game_stat.next_xp = 100;
	globals->game_stat.glb_count = 0;
	//character status
	strcpy(globals->char_stat.name,"");
	globals->char_stat.credits  = 0 ;
	globals->char_stat.damage   = 1 ;
	globals->char_stat.damage_mod = 1;
	globals->char_stat.defence  = 0 ;
	globals->char_stat.defence_mod = 1;
	globals->char_stat.max_health = 100;
	globals->char_stat.health = 100;
	globals->char_stat.health_mod = 1;
	globals->char_stat.level    = 1 ;
	globals->char_stat.xp       = 0 ;
	globals->char_stat.xp_mod   = 1 ;
	globals->char_stat.weight   = 0 ;
	globals->char_stat.max_weight = 10;
	globals->char_stat.max_weight_mod = 1;
	globals->char_stat.rep      = 0;
	globals->char_stat.rep_mod = 1;
}

void globals_reset_game(struct globals *globals)
{
	//game status
	globals->game_stat.game_active = 0;
	globals->game_stat.shop_updated = 0 ;
	globals->game_stat.buy_mod = 1;
	globals->game_stat.sell_mod = 0.7;
    globals->game_stat.combat_phase = 0;
	globals->game_stat.game_over = 0;
	globals->game_stat.next_xp = 100;
	globals->game_stat.glb_count = 0;
}

void globals_reset_char(struct globals *globals)
{
	//character status
	strcpy(globals->char_stat.name,"");
	globals->char_stat.credits  = 0 ;
	globals->char_stat.damage   = 1 ;
	globals->char_stat.damage_mod = 1;
	globals->char_stat.defence  = 0 ;
	globals->char_stat.defence_mod = 1;
	globals->char_stat.health = 100;
	globals->char_stat.health_mod = 1;
	globals->char_stat.level    = 1 ;
	globals->char_stat.xp       = 0 ;
	globals->char_stat.xp_mod   = 1 ;
	globals->char_stat.weight   = 0 ;
	globals->char_stat.max_weight = 10;
	globals->char_stat.max_weight_mod = 1;
	globals->char_stat.rep      = 0;
	globals->char_stat.rep_mod = 1;
}
