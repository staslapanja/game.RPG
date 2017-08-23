#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//include files
#include "defines.h"
#include "global_handler.h"
#include "item_handler.h"
#include "draw_handler.h"
#include "input_handler.h"
#include "win_func.h"
#include "menu_handler.h"
#include "main_game.h"
#include "monster_handler.h"

void refresh_delay()
{
    Sleep(50);
}

void start_game()
{

    //initialize random with time
    srand(time(NULL));

    //create the struct holder with all the main global variables and pointers
    struct globals *glb = (struct globals*)malloc(sizeof(struct globals));
    //assign default values to the globals struct
    globals_default(glb);
    //init console
    glb->p_conhandles = (struct console_handles*)malloc(sizeof(struct console_handles));
    init_draw(glb);
    init_input(glb);

    //initial screen, do not wait for key press
    glb->game_stat.skip_wait_keypress = 1;
    draw_splash_screen(glb);
    glb->game_stat.skip_wait_keypress = 0;

    //draw initial framework
    draw_framework(glb);

    //display the main menu
    display_main_menu_window(glb);

}

void display_main_menu_window(struct globals *glb)
{
    int menu_pos, draw_pos;

    if (glb->game_stat.game_active == 1){
        menu_pos = 0;
    } else {
        menu_pos = 1;
    }

    //loop
    while (TRUE){

        //draw main menu
        draw_pos=0;
        clear_selectWindow_buf(glb);
        if (glb->game_stat.game_active == 1){
            if (menu_pos == 0){
                text_selectWindow_buf(2,draw_pos,"RESUME GAME",BCI_CYAN,glb);
            } else {
                text_selectWindow_buf(2,draw_pos,"RESUME GAME",FCI_CYAN,glb);
            }
            draw_pos++;
        }
        if (menu_pos == 1){
            text_selectWindow_buf(2,draw_pos,"NEW GAME",BCI_CYAN,glb);
        } else {
            text_selectWindow_buf(2,draw_pos,"NEW GAME",FCI_CYAN,glb);
        }
        draw_pos++;
        if (menu_pos == 2){
            text_selectWindow_buf(2,draw_pos,"OPTIONS",BCI_CYAN,glb);
        } else {
            text_selectWindow_buf(2,draw_pos,"OPTIONS",FCI_CYAN,glb);
        }
        draw_pos++;
        if (menu_pos == 3){
            text_selectWindow_buf(2,draw_pos,"QUIT",BCI_CYAN,glb);
        } else {
            text_selectWindow_buf(2,draw_pos,"QUIT",FCI_CYAN,glb);
        }

        //display version of the game
        text_selectWindow_buf(2,glb->selWinSize.y-1,"v",FCI_CYAN,glb);
        text_selectWindow_buf(3,glb->selWinSize.y-1,GAME_VERSION,FCI_CYAN,glb);

        refresh_selWin(glb);

        //update status screen
        if (glb->game_stat.game_active == 1){
            update_stat_screen(glb);
        } else {
            clear_statusWindow_buf(glb);
            refresh_statWin(glb);
        }

        //set info panel
        clear_infoWindow_buf(glb);
        text_infoWindow_buf(0,0,"ARROW KEYS = MOVE, ENTER = SELECT",FCI_CYAN,glb);
        text_infoWindow_buf(0,1,"ESC = RETURN",FCI_CYAN,glb);
        refresh_infoWin(glb);

        //react to input
        short input_key;
        get_input_key(glb);
        input_key = glb->input_key;
        switch(input_key)
        {
        case KEY_DOWN:
            if (menu_pos < 3){
                menu_pos++;
            }
            break;
        case KEY_UP:
            if (glb->game_stat.game_active == 1){
                if (menu_pos > 0){
                    menu_pos--;
                }
            } else {
                if (menu_pos > 1){
                    menu_pos--;
                }
            }
            break;
        case KEY_RETURN:
            switch(menu_pos)
            {
            case 0:
                display_main_game_screen(glb);
                break;
            case 1:
                run_new_game(glb);
                display_main_game_screen(glb);
                break;
            case 2:
                display_options(glb);
                break;
            case 3:
                exit_game(glb);
                break;
            default:
                break;
            }
        case KEY_ESCAPE:
            //quit menu???
            break;
        default:
            break;
        }

        refresh_delay();
    }
}

void display_main_game_screen(struct globals *glb)
{
    int menu_pos;
    int exit_menu;

    struct menu_holder *menu_sel;
    struct menu_holder *menu_shop = create_menu_item();
    struct menu_holder *menu_camp = create_menu_item();
    struct menu_holder *menu_monhunt = create_menu_item();
    struct menu_holder *menu_property = create_menu_item();

    //connect_menu_item(menu,down,up,left,right);
    connect_menu_item(menu_shop     ,menu_camp      ,NULL           ,NULL           ,menu_property  );
    connect_menu_item(menu_camp     ,NULL           ,menu_shop      ,NULL           ,menu_monhunt   );
    connect_menu_item(menu_monhunt  ,NULL           ,menu_property  ,menu_camp      ,NULL           );
    connect_menu_item(menu_property ,menu_monhunt   ,NULL           ,menu_shop      ,NULL           );

    menu_pos = 0;
    exit_menu = 0;
    menu_sel = menu_shop;

    //loop
    while (!exit_menu){

        //draw main game menu
        clear_selectWindow_buf(glb);
        //background
        draw_main_game_background(glb);
        //menus

        if (menu_sel == menu_shop){
            text_selectWindow_buf(3,5,"SHOP",BCI_CYAN,glb);
            menu_pos = 0;
        }
        if (menu_sel == menu_camp){
            text_selectWindow_buf(10,17,"CAMP",BCI_CYAN,glb);
            menu_pos = 1;
        }
        if (menu_sel == menu_monhunt){
            text_selectWindow_buf(40,16,"MONSTER HUNT",BCI_CYAN,glb);
            menu_pos = 2;
        }
        if (menu_sel == menu_property){
            text_selectWindow_buf(22,4,"PROPERTY",BCI_CYAN,glb);
            menu_pos = 3;
        }
        refresh_selWin(glb);

        //react to input
        short input_key;
        get_input_key(glb);
        input_key = glb->input_key;
        switch(input_key)
        {
        case KEY_DOWN:
            if (menu_sel->menu_down != NULL){
                menu_sel = menu_sel->menu_down;
            }
            break;
        case KEY_UP:
            if (menu_sel->menu_up != NULL){
                menu_sel = menu_sel->menu_up;
            }
            break;
        case KEY_LEFT:
            if (menu_sel->menu_left != NULL){
                menu_sel = menu_sel->menu_left;
            }
            break;
        case KEY_RIGHT:
            if (menu_sel->menu_right != NULL){
                menu_sel = menu_sel->menu_right;
            }
            break;
        case KEY_RETURN:
            switch(menu_pos)
            {
            case 0:
                display_shop_items(glb);
                break;
            case 1:
                display_camp_screen(glb);
                break;
            case 2:
                display_monster_hunt_screen(glb);
                break;
            case 4:
                //property screen
                break;
            default:
                break;
            }
            break;
        case KEY_ESCAPE:
            exit_menu = 1;
            break;
        default:
            break;
        }

        if (glb->game_stat.game_over == 1){
            exit_menu = 1;
        }

        //set info panel
        clear_infoWindow_buf(glb);
        text_infoWindow_buf(0,0,"ARROW KEYS = MOVE, ENTER = SELECT",FCI_CYAN,glb);
        text_infoWindow_buf(0,1,"ESC = RETURN",FCI_CYAN,glb);
        refresh_infoWin(glb);

        refresh_delay();
    }
}

void display_shop_items(struct globals *glb)
{

    reset_cursor(glb);
    if (glb->game_stat.shop_updated == 0){
        create_item_list(glb);
        glb->game_stat.shop_updated = 1;
    }
    int item_num;
    item_num = glb->item_list_num;

    struct  item_holder *p_select_item;

    char cost_val[7];
    int draw_row;
    int cursor_pos_y;
    int exit_shop = 0;
    cursor_pos_y = 0;

    //loop
    while (!exit_shop){

        p_select_item = glb->p_items_list;
        clear_selectWindow_buf(glb);
        draw_row = 0;
        while(p_select_item != NULL){
            sprintf(cost_val, "%6d",p_select_item->cost);
            if (draw_row == cursor_pos_y){
                text_selectWindow_buf(0,draw_row,p_select_item->name,BCI_CYAN,glb);
                text_selectWindow_buf(47,draw_row,cost_val,BCI_CYAN,glb);
            } else {
                text_selectWindow_buf(0,draw_row,p_select_item->name,FCI_CYAN,glb);
                text_selectWindow_buf(47,draw_row,cost_val,FCI_CYAN,glb);
            }
            draw_row++;
            p_select_item = p_select_item->next_item;
        }
        refresh_selWin(glb);

        //react to input
        get_input_key(glb);
        short input_key;
        input_key = glb->input_key;
        switch(input_key)
        {
        case KEY_DOWN:
            if (cursor_pos_y < (item_num-1)){
                cursor_pos_y++;
            }
            break;
        case KEY_UP:
            if (cursor_pos_y > 0){
                cursor_pos_y--;
            }
            break;
        case KEY_RETURN:
            glb->select_item_num = cursor_pos_y;
            display_shop_item_details(glb);
            cursor_pos_y = 0;
            break;
        case KEY_ESCAPE:
            //let the shop refresh the items
            glb->game_stat.shop_updated = 0;
            remove_list(glb);
            exit_shop = 1;
            break;
        default:
            break;
        }

        refresh_delay();
    }
}

void display_shop_item_details(struct globals *glb)
{
    //get selected item
    struct  item_holder *p_select_item;
    //get item list pointer
    p_select_item = glb->p_items_list;
    //set counter
    int cnt = glb->select_item_num;
    //find the selected struct
    while((p_select_item != NULL) && (cnt > 0)){
        p_select_item = p_select_item->next_item;
        cnt--;
    }

    if (p_select_item == NULL){
        clear_selectWindow_buf(glb);
        text_selectWindow_buf(0,0,"Error. Item not found.",FCI_RED,glb);
        refresh_selWin(glb);
        Sleep(2000);
    } else {
        int exit_item_display = 0;
        int enough_credits = 0;

        while (!exit_item_display){
            //display
            char val[20];
            clear_selectWindow_buf(glb);
            text_selectWindow_buf(0,0,"Item:",FCI_CYAN,glb);
            text_selectWindow_buf(0,1,"  Name    : ",FCI_CYAN,glb);
            text_selectWindow_buf(0,2,"  Cost    : ",FCI_CYAN,glb);
            text_selectWindow_buf(0,3,"  Category: ",FCI_CYAN,glb);
            text_selectWindow_buf(0,4,"  Damage  : ",FCI_CYAN,glb);
            text_selectWindow_buf(0,5,"  Defence : ",FCI_CYAN,glb);
            text_selectWindow_buf(0,6,"  Weight  : ",FCI_CYAN,glb);

            text_selectWindow_buf(12,1,p_select_item->name,FCI_WHITE,glb);
            sprintf(val, "%.0f",( p_select_item->cost * glb->game_stat.buy_mod ) );
            text_selectWindow_buf(12,2,val,FCI_WHITE,glb);
            text_selectWindow_buf(12,3,p_select_item->category,FCI_WHITE,glb);
            sprintf(val, "%.0f",p_select_item->stat[0]);
            text_selectWindow_buf(12,4,val,FCI_WHITE,glb);
            sprintf(val, "%.0f",p_select_item->stat[1]);
            text_selectWindow_buf(12,5,val,FCI_WHITE,glb);
            sprintf(val, "%.0f",p_select_item->stat[2]);
            text_selectWindow_buf(12,6,val,FCI_WHITE,glb);

            enough_credits = ( glb->char_stat.credits >= ( p_select_item->cost * glb->game_stat.buy_mod ) );

            //do red text if currency to low
            if ( enough_credits ){
                text_selectWindow_buf(0,8,"BUY",BCI_CYAN,glb);
            } else {
                text_selectWindow_buf(0,8,"BUY",FCI_RED,glb);
            }

            refresh_selWin(glb);

            //react to input
            get_input_key(glb);
            short input_key;
            input_key = glb->input_key;
            switch(input_key)
            {
            case KEY_RETURN:
                //BUY ITEM
                if ( enough_credits ){
                    shop_buy_item(p_select_item,glb);
                } else {
                    clear_selectWindow_buf(glb);
                    text_selectWindow_buf(0,2,"Item too expensive. Can not buy.",FCI_RED,glb);
                    refresh_selWin(glb);
                    Sleep(2000);
                }
                exit_item_display = 1;
                break;
            case KEY_ESCAPE:
                //EXIT ITEM DETAILS
                exit_item_display = 1;
                break;
            default:
                break;
            }

            refresh_delay();
        }
    }
}

void shop_buy_item(struct item_holder *item, struct globals *glb)
{
    //ask to confirm
    char val[20];
    clear_selectWindow_buf(glb);
    text_selectWindow_buf(0,2,"Buying item ",FCI_CYAN,glb);
    text_selectWindow_buf(12,2,item->name,FCI_WHITE,glb);
    text_selectWindow_buf(0,3,"Value ",FCI_CYAN,glb);
    sprintf(val, "%.0f",( item->cost * glb->game_stat.buy_mod) );
    text_selectWindow_buf(6,3,val,FCI_WHITE,glb);
    text_selectWindow_buf(2,5,"CONFIRM",BCI_CYAN,glb);
    refresh_selWin(glb);
    int exit_display;
    exit_display = 0;
    while (!exit_display){
        get_input_key(glb);
        short input_key;
        input_key = glb->input_key;
        switch(input_key)
        {
        case KEY_RETURN:
            //BUY
            //deduct from credits the item value
            glb->char_stat.credits -= ( item->cost * glb->game_stat.buy_mod);
            update_stat_screen(glb);
            //copy item to storage
            copy_to_storage(item,glb);
            glb->storage_item_num++;
            //remove item from item_list
            remove_from_item_list(item,glb);
            exit_display = 1;
            break;
        case KEY_ESCAPE:
            //EXIT
            exit_display = 1;
            break;
        default:
            break;
        }

        refresh_delay();
    }
}

void display_camp_screen(struct globals *glb)
{
    int draw_row = 0;
    int cursor_pos_y = 0;
    int exit_display = 0;
    short input_key;

    while (!exit_display){

        draw_row = 0;
        //display
        clear_selectWindow_buf(glb);

        if (cursor_pos_y == 0){
            text_selectWindow_buf(0,draw_row,"ITEM STORAGE",BCI_CYAN,glb);
        } else {
            text_selectWindow_buf(0,draw_row,"ITEM STORAGE",FCI_CYAN,glb);
        }
        draw_row++;
        if (cursor_pos_y == 1){
            text_selectWindow_buf(0,draw_row,"SKILLS",BCI_CYAN,glb);
        } else {
            text_selectWindow_buf(0,draw_row,"SKILLS",FCI_CYAN,glb);
        }
        draw_row++;
        if (cursor_pos_y == 2){
            text_selectWindow_buf(0,draw_row,"HEAL",BCI_CYAN,glb);
        } else {
            text_selectWindow_buf(0,draw_row,"HEAL",FCI_CYAN,glb);
        }
        refresh_selWin(glb);

        //react to input
        get_input_key(glb);
        input_key = glb->input_key;
        switch(input_key)
        {
        case KEY_DOWN:
            if (cursor_pos_y < 2){
                cursor_pos_y++;
            }
            break;
        case KEY_UP:
            if (cursor_pos_y > 0){
                cursor_pos_y--;
            }
            break;
        case KEY_RETURN:
            switch(cursor_pos_y)
            {
            case 0:
                display_storage_items(glb);
                break;
            case 1:
                display_skills_screen(glb);
                break;
            case 2:
                heal_char(glb);
                break;
            default:
                break;
            }
            cursor_pos_y = 0;
            break;
        case KEY_ESCAPE:
            exit_display = 1;
            break;
        default:
            break;
        }
    }

}

void display_skills_screen(struct globals *glb)
{

    int cursor_pos_y = 0;
    int cursor_pos_x = 0;
    int exit_display = 0;
    short input_key;

    while (!exit_display){

        //display
        clear_selectWindow_buf(glb);
        text_selectWindow_buf(2,2,"Upgrade your skills with reputation:",FCI_WHITE,glb);

        text_selectWindow_buf(4, 4,"Cost   :   10 REP   100 REP   1000 REP",FCI_WHITE,glb);
        text_selectWindow_buf(4, 6,"Health :",FCI_WHITE,glb);
        text_selectWindow_buf(4, 8,"Damage :",FCI_WHITE,glb);
        text_selectWindow_buf(4,10,"Defence:",FCI_WHITE,glb);
        text_selectWindow_buf(4,12,"Weight :",FCI_WHITE,glb);

        if ((cursor_pos_y == 0) && (cursor_pos_x == 0)){
            text_selectWindow_buf(16,6,"+10",BCI_CYAN,glb);
        } else {
            text_selectWindow_buf(16,6,"+10",FCI_CYAN,glb);
        }
        if ((cursor_pos_y == 0) && (cursor_pos_x == 1)){
            text_selectWindow_buf(25,6,"+100",BCI_CYAN,glb);
        } else {
            text_selectWindow_buf(25,6,"+100",FCI_CYAN,glb);
        }
        if ((cursor_pos_y == 0) && (cursor_pos_x == 2)){
            text_selectWindow_buf(35,6,"+1000",BCI_CYAN,glb);
        } else {
            text_selectWindow_buf(35,6,"+1000",FCI_CYAN,glb);
        }
        if ((cursor_pos_y == 1) && (cursor_pos_x == 0)){
            text_selectWindow_buf(16,8,"+1",BCI_CYAN,glb);
        } else {
            text_selectWindow_buf(16,8,"+1",FCI_CYAN,glb);
        }
        if ((cursor_pos_y == 1) && (cursor_pos_x == 1)){
            text_selectWindow_buf(25,8,"+10",BCI_CYAN,glb);
        } else {
            text_selectWindow_buf(25,8,"+10",FCI_CYAN,glb);
        }
        if ((cursor_pos_y == 1) && (cursor_pos_x == 2)){
            text_selectWindow_buf(35,8,"+100",BCI_CYAN,glb);
        } else {
            text_selectWindow_buf(35,8,"+100",FCI_CYAN,glb);
        }
        if ((cursor_pos_y == 2) && (cursor_pos_x == 0)){
            text_selectWindow_buf(16,10,"+1",BCI_CYAN,glb);
        } else {
            text_selectWindow_buf(16,10,"+1 ",FCI_CYAN,glb);
        }
        if ((cursor_pos_y == 2) && (cursor_pos_x == 1)){
            text_selectWindow_buf(25,10,"+10",BCI_CYAN,glb);
        } else {
            text_selectWindow_buf(25,10,"+10 ",FCI_CYAN,glb);
        }
        if ((cursor_pos_y == 2) && (cursor_pos_x == 2)){
            text_selectWindow_buf(35,10,"+100",BCI_CYAN,glb);
        } else {
            text_selectWindow_buf(35,10,"+100 ",FCI_CYAN,glb);
        }
        if ((cursor_pos_y == 3) && (cursor_pos_x == 0)){
            text_selectWindow_buf(16,12,"+3",BCI_CYAN,glb);
        } else {
            text_selectWindow_buf(16,12,"+3",FCI_CYAN,glb);
        }
        if ((cursor_pos_y == 3) && (cursor_pos_x == 1)){
            text_selectWindow_buf(25,12,"+30",BCI_CYAN,glb);
        } else {
            text_selectWindow_buf(25,12,"+30",FCI_CYAN,glb);
        }
        if ((cursor_pos_y == 3) && (cursor_pos_x == 2)){
            text_selectWindow_buf(35,12,"+300",BCI_CYAN,glb);
        } else {
            text_selectWindow_buf(35,12,"+300",FCI_CYAN,glb);
        }

        refresh_selWin(glb);

        //react to input
        get_input_key(glb);
        input_key = glb->input_key;
        switch(input_key)
        {
        case KEY_DOWN:
            if (cursor_pos_y < 3){
                cursor_pos_y++;
            }
            break;
        case KEY_UP:
            if (cursor_pos_y > 0){
                cursor_pos_y--;
            }
            break;
        case KEY_RIGHT:
            if (cursor_pos_x < 2){
                cursor_pos_x++;
            }
            break;
        case KEY_LEFT:
            if (cursor_pos_x > 0){
                cursor_pos_x--;
            }
            break;
        case KEY_RETURN:
            switch(cursor_pos_y)
            {
            case 0:
                if ((glb->char_stat.rep >= 10 ) && (cursor_pos_x == 0)){
                    glb->char_stat.max_health+=10;
                    glb->char_stat.rep-=10;
                } else if ((glb->char_stat.rep >= 100 ) && (cursor_pos_x == 1)){
                    glb->char_stat.max_health+=100;
                    glb->char_stat.rep-=100;
                } else if ((glb->char_stat.rep >= 1000 ) && (cursor_pos_x == 2)){
                    glb->char_stat.max_health+=1000;
                    glb->char_stat.rep-=1000;
                }
                break;
            case 1:
                if ((glb->char_stat.rep >= 10 ) && (cursor_pos_x == 0)){
                    glb->char_stat.damage+=1;
                    glb->char_stat.rep-=10;
                } else if ((glb->char_stat.rep >= 100 ) && (cursor_pos_x == 1)){
                    glb->char_stat.damage+=10;
                    glb->char_stat.rep-=100;
                } else if ((glb->char_stat.rep >= 1000 ) && (cursor_pos_x == 2)){
                    glb->char_stat.damage+=100;
                    glb->char_stat.rep-=1000;
                }
                break;
            case 2:
                if ((glb->char_stat.rep >= 10 ) && (cursor_pos_x == 0)){
                    glb->char_stat.defence+=1;
                    glb->char_stat.rep-=10;
                } else if ((glb->char_stat.rep >= 100 ) && (cursor_pos_x == 1)){
                    glb->char_stat.defence+=10;
                    glb->char_stat.rep-=100;
                } else if ((glb->char_stat.rep >= 1000 ) && (cursor_pos_x == 2)){
                    glb->char_stat.defence+=100;
                    glb->char_stat.rep-=1000;
                }
                break;
            case 3:
                if ((glb->char_stat.rep >= 10 ) && (cursor_pos_x == 0)){
                    glb->char_stat.max_weight+=3;
                    glb->char_stat.rep-=10;
                } else if ((glb->char_stat.rep >= 100 ) && (cursor_pos_x == 1)){
                    glb->char_stat.max_weight+=30;
                    glb->char_stat.rep-=100;
                } else if ((glb->char_stat.rep >= 1000 ) && (cursor_pos_x == 2)){
                    glb->char_stat.max_weight+=300;
                    glb->char_stat.rep-=1000;
                }
                break;
            default:
                break;
            }

            break;
        case KEY_ESCAPE:
            exit_display = 1;
            break;
        default:
            break;
        }

        update_stat_screen(glb);

    }
}

void heal_char(struct globals *glb)
{
    clear_selectWindow_buf(glb);
    text_selectWindow_buf(2,2,"You take a moment to rest.",FCI_WHITE,glb);
    text_selectWindow_buf(2,4,"Full health",FCI_WHITE,glb);
    text_selectWindow_buf(2,5,"XP modifier reset.",FCI_WHITE,glb);
    refresh_selWin(glb);

    glb->char_stat.health = glb->char_stat.max_health;
    glb->char_stat.xp_mod = 1;

    update_stat_screen(glb);

    Sleep(2000);
}

void display_storage_items(struct globals *glb)
{

    reset_cursor(glb);
    int item_num;
    item_num = glb->storage_item_num;

    struct  item_holder *p_select_item;

    int draw_row;
    int cursor_pos_y;
    int exit_storage = 0;
    cursor_pos_y = 0;

    //loop
    while (!exit_storage){

        p_select_item = glb->p_storage_item;
        clear_selectWindow_buf(glb);
        draw_row = 0;
        if (p_select_item == NULL){
            text_selectWindow_buf(0,0,"No items in the storage.",FCI_CYAN,glb);
        } else {
        while(p_select_item != NULL){
            if (draw_row == cursor_pos_y){
                text_selectWindow_buf(0,draw_row,p_select_item->name,BCI_CYAN,glb);
            } else {
                text_selectWindow_buf(0,draw_row,p_select_item->name,FCI_CYAN,glb);
            }
            draw_row++;
            p_select_item = p_select_item->next_item;
        }
        }
        refresh_selWin(glb);

        //react to input
        get_input_key(glb);
        short input_key;
        input_key = glb->input_key;
        switch(input_key)
        {
        case KEY_DOWN:
            if (cursor_pos_y < (item_num-1)){
                cursor_pos_y++;
            }
            break;
        case KEY_UP:
            if (cursor_pos_y > 0){
                cursor_pos_y--;
            }
            break;
        case KEY_RETURN:
            glb->storage_item_num = cursor_pos_y;
            display_storage_item_details(glb);
            cursor_pos_y = 0;
            break;
        case KEY_ESCAPE:
            exit_storage = 1;
            break;
        default:
            break;
        }

        refresh_delay();
    }
}

void display_storage_item_details(struct globals *glb)
{

    //get selected item
    struct  item_holder *p_select_item;
    //get item list pointer
    p_select_item = glb->p_storage_item;
    //set counter
    int cnt = glb->storage_item_num;
    //find the selected struct
    while((p_select_item != NULL) && (cnt > 0)){
        p_select_item = p_select_item->next_item;
        cnt--;
    }

    if (p_select_item == NULL){
        clear_selectWindow_buf(glb);
        text_selectWindow_buf(0,2,"Error. Item not found.",FCI_RED,glb);
        refresh_selWin(glb);
        Sleep(2000);
    } else {
        int exit_item_display = 0;
        int cursor_pos_y;
        cursor_pos_y = 0;

        while (!exit_item_display){
            //display
            char val[20];
            clear_selectWindow_buf(glb);
            text_selectWindow_buf(0,0,"Item:",FCI_CYAN,glb);
            text_selectWindow_buf(0,1,"  Name    : ",FCI_CYAN,glb);
            text_selectWindow_buf(0,2,"  Value   : ",FCI_CYAN,glb);
            text_selectWindow_buf(0,3,"  Category: ",FCI_CYAN,glb);
            text_selectWindow_buf(0,4,"  Damage  : ",FCI_CYAN,glb);
            text_selectWindow_buf(0,5,"  Defence : ",FCI_CYAN,glb);
            text_selectWindow_buf(0,6,"  Weight  : ",FCI_CYAN,glb);
            text_selectWindow_buf(0,7,"  Equipped: ",FCI_CYAN,glb);

            text_selectWindow_buf(12,1,p_select_item->name,FCI_WHITE,glb);
            sprintf(val, "%.0f",( p_select_item->cost * glb->game_stat.sell_mod) );
            text_selectWindow_buf(12,2,val,FCI_WHITE,glb);
            text_selectWindow_buf(12,3,p_select_item->category,FCI_WHITE,glb);
            sprintf(val, "%.0f",p_select_item->stat[0]);
            text_selectWindow_buf(12,4,val,FCI_WHITE,glb);
            sprintf(val, "%.0f",p_select_item->stat[1]);
            text_selectWindow_buf(12,5,val,FCI_WHITE,glb);
            sprintf(val, "%.0f",p_select_item->stat[2]);
            text_selectWindow_buf(12,6,val,FCI_WHITE,glb);
            if (p_select_item->equiped == 1){
                text_selectWindow_buf(12,7,"YES",FCI_WHITE,glb);
            } else {
                text_selectWindow_buf(12,7,"NO",FCI_WHITE,glb);
            }

            if (cursor_pos_y == 0){
                if (p_select_item->equiped == 1){
                    text_selectWindow_buf(0,8,"REMOVE",BCI_CYAN,glb);
                } else {
                    text_selectWindow_buf(0,8,"USE",BCI_CYAN,glb);
                }
            } else {
                if (p_select_item->equiped == 1){
                    text_selectWindow_buf(0,8,"REMOVE",FCI_CYAN,glb);
                } else {
                    text_selectWindow_buf(0,8,"USE",FCI_CYAN,glb);
                }
            }
            if (cursor_pos_y == 1){
                text_selectWindow_buf(0,9,"SELL",BCI_CYAN,glb);
            } else {
                text_selectWindow_buf(0,9,"SELL",FCI_CYAN,glb);
            }

            refresh_selWin(glb);

            //react to input
            get_input_key(glb);
            short input_key;
            input_key = glb->input_key;
            switch(input_key)
            {
            case KEY_DOWN:
                if (cursor_pos_y < 1){
                    cursor_pos_y++;
                }
                break;
            case KEY_UP:
                if (cursor_pos_y > 0){
                    cursor_pos_y--;
                }
                break;
            case KEY_RETURN:
                if (cursor_pos_y == 0){
                    if (p_select_item->equiped == 1){
                        //USE ITEM
                        char_remove_item(p_select_item,glb);
                    } else {
                        //REMOVE ITEM
                        char_use_item(p_select_item,glb);
                    }
                }
                if (cursor_pos_y == 1){
                    //SELL ITEM
                    storage_sell_item(p_select_item,glb);
                    exit_item_display = 1;
                }
                break;
            case KEY_ESCAPE:
                //EXIT ITEM DETAILS
                exit_item_display = 1;
                break;
            default:
                break;
            }

            refresh_delay();
        }
    }
}

void char_use_item(struct item_holder *item, struct globals *glb)
{
    //wearable items
    //check if the new item is not too heavy
    if ((glb->char_stat.weight + item->stat[2]) <= (glb->char_stat.max_weight * glb->char_stat.max_weight_mod)){
        //update status
        item->equiped = 1;
        glb->char_stat.damage += item->stat[0];
        glb->char_stat.defence += item->stat[1];
        glb->char_stat.weight += item->stat[2];
        update_stat_screen(glb);
    } else {
        clear_selectWindow_buf(glb);
        text_selectWindow_buf(0,2,"Item too heavy. Can not equip.",FCI_RED,glb);
        refresh_selWin(glb);
        Sleep(2000);
    }
}

void char_remove_item(struct item_holder *item, struct globals *glb)
{
    //update status
    item->equiped = 0;
    glb->char_stat.damage -= item->stat[0];
    glb->char_stat.defence -= item->stat[1];
    glb->char_stat.weight -= item->stat[2];
    update_stat_screen(glb);
}

void storage_sell_item(struct item_holder *item, struct globals *glb)
{
    //ask to confirm
    char val[20];
    clear_selectWindow_buf(glb);
    text_selectWindow_buf(0,2,"Selling item ",FCI_CYAN,glb);
    text_selectWindow_buf(13,2,item->name,FCI_WHITE,glb);
    text_selectWindow_buf(0,3,"Value ",FCI_CYAN,glb);
    sprintf(val, "%.0f",( item->cost * glb->game_stat.sell_mod) );
    text_selectWindow_buf(6,3,val,FCI_WHITE,glb);
    text_selectWindow_buf(2,5,"CONFIRM",BCI_CYAN,glb);
    refresh_selWin(glb);
    int exit_display;
    exit_display = 0;
    while (!exit_display){
        get_input_key(glb);
        short input_key;
        input_key = glb->input_key;
        switch(input_key)
        {
        case KEY_RETURN:
            //SELL
            //remove from character
            if (item->equiped == 1) {
                char_remove_item(item,glb);
            }
            //add currency
            glb->char_stat.credits += ( item->cost * glb->game_stat.sell_mod);
            //remove item from storage_list
            remove_from_storage_list(item,glb);
            update_stat_screen(glb);
            exit_display = 1;
            break;
        case KEY_ESCAPE:
            //EXIT
            exit_display = 1;
            break;
        default:
            break;
        }

        refresh_delay();
    }
}

void update_stat_screen(struct globals *glb)
{
    clear_statusWindow_buf(glb);

    char text[19];
    int row;
    //name
    row = 0;
    text_statusWindow_buf(0,row,"Name:",FCI_CYAN,glb);
    text_statusWindow_buf(2,row+1,glb->char_stat.name,FCI_WHITE,glb);

    //level
    row += 2;
    text_statusWindow_buf(0,row,"Level:",FCI_CYAN,glb);
    sprintf(text, "%d",glb->char_stat.level);
    text_statusWindow_buf(2,row+1,text,FCI_WHITE,glb);

    //Experience
    row += 2;
    text_statusWindow_buf(0,row,"XP:",FCI_CYAN,glb);
    if (glb->char_stat.xp_mod > 1.0f) {
        sprintf(text, "x %.1f", glb->char_stat.xp_mod );
        text_statusWindow_buf(8,row,text,FCI_WHITE,glb);
    }
    sprintf(text, "%.0f/%.0f", glb->char_stat.xp, glb->game_stat.next_xp );
    text_statusWindow_buf(2,row+1,text,FCI_WHITE,glb);

    //Reputation
    row += 2;
    text_statusWindow_buf(0,row,"Reputation:",FCI_CYAN,glb);
    sprintf(text, "%.0f", glb->char_stat.rep );
    text_statusWindow_buf(2,row+1,text,FCI_WHITE,glb);

    //Credits
    row += 2;
    text_statusWindow_buf(0,row,"Gold:",FCI_CYAN,glb);
    sprintf(text, "%.0f", glb->char_stat.credits );
    text_statusWindow_buf(2,row+1,text,FCI_WHITE,glb);

    row += 1;

    //Health
    row += 2;
    text_statusWindow_buf(0,row,"Health:",FCI_CYAN,glb);
    sprintf(text, "%.0f/%.0f",( glb->char_stat.health * glb->char_stat.health_mod ),( glb->char_stat.max_health * glb->char_stat.health_mod ) );
    text_statusWindow_buf(2,row+1,text,FCI_WHITE,glb);

    //Damage
    row += 2;
    text_statusWindow_buf(0,row,"Damage:",FCI_CYAN,glb);
    sprintf(text, "%.0f",( glb->char_stat.damage * glb->char_stat.damage_mod ) );
    text_statusWindow_buf(2,row+1,text,FCI_WHITE,glb);

    //Defence
    row += 2;
    text_statusWindow_buf(0,row,"Defence:",FCI_CYAN,glb);
    sprintf(text, "%.0f",( glb->char_stat.defence * glb->char_stat.defence_mod ) );
    text_statusWindow_buf(2,row+1,text,FCI_WHITE,glb);

    //Weight
    row += 2;
    text_statusWindow_buf(0,row,"Weight:",FCI_CYAN,glb);
    sprintf(text, "%.0f/%.0f",glb->char_stat.weight, glb->char_stat.max_weight );
    text_statusWindow_buf(2,row+1,text,FCI_WHITE,glb);

    refresh_statWin(glb);
}

void display_monster_hunt_screen(struct globals *glb)
{
    //create monsters
    int monster_num;
    create_monster_list(glb);
    monster_num = glb->monster_list_num;
    //display

    int draw_row, exit_disp, cursor_pos_y;
    struct  monster_object *p_monster;
    float dmg_check;

    //set info panel
    clear_infoWindow_buf(glb);
    text_infoWindow_buf(0,0,"ARROW KEYS = MOVE, ENTER = SELECT, ESC = RETURN",FCI_CYAN,glb);
    text_infoWindow_buf(0,1,"RED NAME = CAN NOT BE DAMAGED!",FCI_CYAN,glb);
    refresh_infoWin(glb);

    exit_disp = 0;
    cursor_pos_y = 1;
    //loop
    while (!exit_disp){

        clear_selectWindow_buf(glb);
        text_selectWindow_buf(0,0,"You find these monsters:",FCI_CYAN,glb);
        draw_row = 1;
        p_monster = glb->p_monster_list;
        while(p_monster != NULL){
            dmg_check = (glb->char_stat.damage * glb->char_stat.damage_mod) - (p_monster->defence * p_monster->defence_mod);
            if (draw_row == cursor_pos_y){
                if (dmg_check <= 0) {
                    text_selectWindow_buf(0,draw_row,p_monster->name,BCI_RED,glb);
                } else {
                    text_selectWindow_buf(0,draw_row,p_monster->name,BCI_CYAN,glb);
                }
            } else {
                if (dmg_check <= 0) {
                    text_selectWindow_buf(0,draw_row,p_monster->name,FCI_RED,glb);
                } else {
                    text_selectWindow_buf(0,draw_row,p_monster->name,FCI_CYAN,glb);
                }
            }
            draw_row++;
            p_monster = p_monster->next_monster;
        }
        refresh_selWin(glb);

        //react to input
        get_input_key(glb);
        short input_key;
        input_key = glb->input_key;
        switch(input_key)
        {
        case KEY_DOWN:
            if (cursor_pos_y < (monster_num)){
                cursor_pos_y++;
            }
            break;
        case KEY_UP:
            if (cursor_pos_y > 1){
                cursor_pos_y--;
            }
            break;
        case KEY_RETURN:
            monster_encounter(cursor_pos_y-1,glb);
            remove_monster_list(glb);
            exit_disp = 1;
            break;
        case KEY_ESCAPE:
            remove_monster_list(glb);
            exit_disp = 1;
            break;
        default:
            break;
        }

        refresh_delay();
    }
}

void monster_encounter(int monster_sel, struct globals *glb)
{
    //get selected monster
    struct monster_object *p_select_monster;
    //get item list pointer
    p_select_monster = glb->p_monster_list;
    //find the selected monster
    int cnt;
    cnt = monster_sel;
    while((p_select_monster != NULL) && (cnt > 0)){
        p_select_monster = p_select_monster->next_monster;
        cnt--;
    }

    int end_encounter;
    int victory;
    int run_away;
    int player_action;
    float char_hp, monster_hp, char_hp_start, monster_hp_start;
    float char_dmg, monster_dmg;
    float char_def, monster_def;
    float monster_hp_ratio;
    int i;
    float damage;
    char text_holder[20];
    short key_act, key_act_reg = 0;
    short rand_key;
    int next_rand_key;
    double time0, time1, diff_time;
    double monster_act_delay = 3.0f;
    short input_key = 0x0;

    //text buffer
    int textbuf_h = glb->selWinSize.y-2-6;

    //create a text buffer and set it to zeroes
    char *textbuf = calloc(1,sizeof(char) * (glb->selWinSize.x * (textbuf_h + 1)));
    int p = 0;

    //set combat phase
    glb->game_stat.combat_phase = 1;

    //set info panel
    clear_infoWindow_buf(glb);
    text_infoWindow_buf(0,0,"ATTACK BY PRESSING THE CORRECT ARROW KEY",FCI_CYAN,glb);
    text_infoWindow_buf(0,1,"ESC - RUN AWAY, LOSE ALL REP AND GOLD",FCI_CYAN,glb);
    refresh_infoWin(glb);

    end_encounter = 0;
    victory = 0;
    run_away = 0;
    player_action = 0;
    char_hp_start = glb->char_stat.health * glb->char_stat.health_mod;
    char_hp = char_hp_start;
    char_dmg = glb->char_stat.damage * glb->char_stat.damage_mod;
    char_def = glb->char_stat.defence * glb->char_stat.defence_mod;
    monster_hp_start = p_select_monster->health * p_select_monster->health_mod;
    monster_hp = monster_hp_start;
    monster_dmg = p_select_monster->damage * p_select_monster->damage_mod;
    monster_def = p_select_monster->defence * p_select_monster->defence_mod;

    time0 = get_time();

    next_rand_key = 1;

    glb->game_stat.skip_wait_keypress = 1;
    while(!end_encounter){

        clear_selectWindow_buf(glb);

        //display monster name
        text_selectWindow_buf(2,0,p_select_monster->name,FCI_RED,glb);

        //select the next key if required
        if (next_rand_key == 1){
            rand_key = make_rand_key();
            next_rand_key = 0;
        }

        //draw the key box
        draw_key_request(46,16,rand_key,glb);

        //react to input
        get_input_key(glb);
        input_key = glb->input_key;
        key_act = glb->input_toggle;
        switch(input_key)
        {
        case KEY_DOWN:
            player_action = 1;
            break;
        case KEY_UP:
            player_action = 1;
            break;
        case KEY_LEFT:
            player_action = 1;
            break;
        case KEY_RIGHT:
            player_action = 1;
            break;
        case KEY_ESCAPE:
            player_action = 0;
            run_away = 1;
            break;
        default:
            player_action = 0;
            break;
        }

        if ((player_action == 1) && (key_act == 1) && (key_act_reg == 0)) {
        //check player action (on arrow key press, ignore held button)
            if (input_key == rand_key) {
            //if correct key pressed, do player calculations
                damage = char_dmg - monster_def;
                if (damage < 0) damage = 0;
                sprintf(text_holder, "%s dealt %.0f damage",glb->char_stat.name,damage );
                add_to_textbuf(text_holder,textbuf,&p,textbuf_h,glb);
                monster_hp = monster_hp - damage;
            } else {
                sprintf(text_holder, "%s missed!",glb->char_stat.name );
                add_to_textbuf(text_holder,textbuf,&p,textbuf_h,glb);
            }
            player_action = 0;
            next_rand_key = 1;
        }

        //remember if key was pressed
        key_act_reg = key_act;

        time1 = get_time();

        diff_time = time1 - time0;

        if (diff_time > monster_act_delay ){
        //monster attacks once per set time delay
            damage = monster_dmg - char_def;
            if (damage < 0) damage = 0;
            sprintf(text_holder, "%s dealt %.0f damage",p_select_monster->name,damage );
            add_to_textbuf(text_holder,textbuf,&p,textbuf_h,glb);
            char_hp = char_hp - damage;
            time0 = get_time();
        }

        //draw attack bar
        text_selectWindow_buf(2,16,"ATTACK: ",FCI_WHITE,glb);
        for (i = 0; i < 30; i++){
            double calc =   (double)i  * 1/30 * monster_act_delay;
            if (calc < diff_time ){
                text_selectWindow_buf(10+i,16," ",BCI_WHITE,glb);
            } else {
                text_selectWindow_buf(10+i,16," ",BC_BLUE,glb);
            }
        }


        //draw monster hp bar
        monster_hp_ratio = monster_hp / monster_hp_start;
        text_selectWindow_buf(2,18,"HP:     ",FCI_WHITE,glb);
        for (i = 0; i < 30; i++){
            float calc =   (float)i  * 1/30 ;
            if (calc < monster_hp_ratio ){
                text_selectWindow_buf(10+i,18," ",BCI_RED,glb);
            } else {
                text_selectWindow_buf(10+i,18," ",BC_RED,glb);
            }
        }

        //defeat
        if (char_hp <= 0) {
            game_over_screen(glb);
            glb->game_stat.game_over = 1;
            glb->game_stat.game_active = 0;
            end_encounter = 1;
        }

        //victory
        if ((monster_hp <= 0) && (char_hp > 0)){

            //transfer XP and REP from the monster to the player
            glb->char_stat.xp+=(p_select_monster->xp * glb->char_stat.xp_mod);
            glb->char_stat.rep+=(p_select_monster->xp * glb->char_stat.xp_mod);
            //transfer gold
            glb->char_stat.credits+=p_select_monster->credits;
            //transfer item(s)

            //increase xp modifier by 10%
            glb->char_stat.xp_mod+= 0.1;
            //update stats
            update_stat_screen(glb);

            glb->game_stat.combat_phase = 0;
            end_encounter = 1;
            victory = 1;
        }

        //leave combat
        if (run_away){
            //remove all credits
            glb->char_stat.credits = 0;
            //remove all rep
            glb->char_stat.rep = 0;
            //reset xp modifier
            glb->char_stat.xp_mod = 1;
            end_encounter = 1;
        }

        //display text window
        display_textbuf(2, 2, textbuf, p, textbuf_h, glb);

        refresh_selWin(glb);
        glb->char_stat.health = char_hp;
        update_stat_screen(glb);

        Sleep(20);
    }
    glb->game_stat.skip_wait_keypress = 0;
    //release the memory used for the text buffer
    free(textbuf);

    if (victory) {
        clear_selectWindow_buf(glb);
        text_selectWindow_buf(4,4,"VICTORY!",FCI_WHITE,glb);
        sprintf(text_holder, "Gained %.0f XP",(p_select_monster->xp * glb->char_stat.xp_mod) );
        text_selectWindow_buf(4,6,text_holder,FCI_WHITE,glb);
        sprintf(text_holder, "Gained %.0f GOLD",p_select_monster->credits );
        text_selectWindow_buf(4,7,text_holder,FCI_WHITE,glb);
        text_selectWindow_buf(4,9,"XP modifier +10%",FCI_WHITE,glb);

        refresh_selWin(glb);

        Sleep(1000);

        //check if character leveled up
        while (glb->char_stat.xp >= glb->game_stat.next_xp){
            //level up
            glb->char_stat.level++;
            glb->char_stat.max_health += 20;
            glb->char_stat.damage += 2;
            glb->char_stat.defence += 2;
            glb->char_stat.max_weight += 5;
            update_stat_screen(glb);

            //display
            clear_selectWindow_buf(glb);
            text_selectWindow_buf(2,2,"LEVEL UP!",FCI_WHITE,glb);

            text_selectWindow_buf(2,4,"You are now lvl ",FCI_WHITE,glb);
            sprintf(text_holder, "%d",glb->char_stat.level );
            text_selectWindow_buf(18,4,text_holder,FCI_WHITE,glb);

            text_selectWindow_buf(4, 6,"Health : +20",FCI_WHITE,glb);
            text_selectWindow_buf(4, 7,"Damage : + 2",FCI_WHITE,glb);
            text_selectWindow_buf(4, 8,"Defence: + 2",FCI_WHITE,glb);
            text_selectWindow_buf(4, 9,"Weight : + 5",FCI_WHITE,glb);

            //set next xp limit
            set_next_xp(glb);

            refresh_selWin(glb);
            update_stat_screen(glb);

            Sleep(2000);
        }
    }

    if (run_away) {
        clear_selectWindow_buf(glb);
        text_selectWindow_buf(4,4,"RAN AWAY!",FCI_WHITE,glb);
        text_selectWindow_buf(4,6,"All gold lost!",FCI_WHITE,glb);
        text_selectWindow_buf(4,7,"All reputation lost!",FCI_WHITE,glb);
        text_selectWindow_buf(4,8,"XP modifier reset",FCI_WHITE,glb);

        refresh_selWin(glb);

        Sleep(1000);
    }

    //set info panel
    clear_infoWindow_buf(glb);
    text_infoWindow_buf(0,0,"ARROW KEYS = MOVE, ENTER = SELECT",FCI_CYAN,glb);
    text_infoWindow_buf(0,1,"ESC = RETURN",FCI_CYAN,glb);
    refresh_infoWin(glb);

}

void add_to_textbuf(char text[],char *textbuf, int *p, int h, struct globals *glb)
{
    int i;
    int w = glb->selWinSize.x;

    //copy text into the memory
    for (i=0; i < strlen(text); i++){
        if (i < w) {
            textbuf[*p*w+i] = text[i];
        }
    }
    //if text is shorter that the width of the row
    //finish the string
    if (i < w){
        textbuf[*p*w+i] = '\0';
    }
    if (*p == h - 1){
        *p = 0;
    } else {
        *p = *p + 1;
    }

}

void display_textbuf(int x, int y, char *textbuf, int p, int h, struct globals *glb)
{
    int i,j,sel;
    int w = glb->selWinSize.x;
    char text[w+1];

    //make sure that the string is properly finished
    text[w] = '\0';

    //select one row before the pointer p
    if (p == 0) {
        sel = h - 1;
    } else {
        sel = p - 1;
    }
    for (i=0; i < h; i++){

        //copy text to local memory
        for (j=0; j < w; j++){
            text[j] = textbuf[sel*w+j];
        }
        text_selectWindow_buf(x,y+h-1-i,text,FCI_WHITE,glb);
        if (sel == 0) {
            sel = h - 1;
        } else {
            sel--;
        }
    }
}

short make_rand_key()
{
    short rand_key;
    //randomly select a number
    //add a levelizer - max 4
    int rand_num = rand() % 4;
    //transform the number to the key
    switch(rand_num)
    {
    case 0:
        rand_key = KEY_DOWN;
        break;
    case 1:
        rand_key = KEY_UP;
        break;
    case 2:
        rand_key = KEY_LEFT;
        break;
    case 3:
        rand_key = KEY_RIGHT;
        break;
    default:
        rand_key = 0x0;
        break;
    }
    return rand_key;
}

void draw_key_request(int x, int y, short rand_key, struct globals *glb)
{
    int i;
    char ch[2];
    //frame
    ch[1] = 0x0;
    ch[0] = 0xda;
    text_selectWindow_buf(x,y,ch,FC_WHITE,glb);
    text_selectWindow_buf(x+1,y,"-----",FC_WHITE,glb);
    ch[0] = 0xbf;
    text_selectWindow_buf(x+6,y,ch,FC_WHITE,glb);
    ch[0] = 0xb3;
    for (i=1; i < 4; i++){
        text_selectWindow_buf(x,y+i,ch,FC_WHITE,glb);
        text_selectWindow_buf(x+6,y+i,ch,FC_WHITE,glb);
    }
    ch[0] = 0xc0;
    text_selectWindow_buf(x,y+4,ch,FC_WHITE,glb);
    text_selectWindow_buf(x+1,y+4,"-----",FC_WHITE,glb);
    ch[0] = 0xd9;
    text_selectWindow_buf(x+6,y+4,ch,FC_WHITE,glb);

    //draw selected arrow
    switch(rand_key)
    {
    case KEY_DOWN:
        text_selectWindow_buf(x+3,y+1,"|",FC_WHITE,glb);
        text_selectWindow_buf(x+3,y+2,"|",FC_WHITE,glb);
        text_selectWindow_buf(x+3,y+3,"v",FC_WHITE,glb);
        break;
    case KEY_UP:
        text_selectWindow_buf(x+3,y+1,"^",FC_WHITE,glb);
        text_selectWindow_buf(x+3,y+2,"|",FC_WHITE,glb);
        text_selectWindow_buf(x+3,y+3,"|",FC_WHITE,glb);
        break;
    case KEY_LEFT:
        text_selectWindow_buf(x+2,y+2,"<--",FC_WHITE,glb);
        break;
    case KEY_RIGHT:
        text_selectWindow_buf(x+2,y+2,"-->",FC_WHITE,glb);
        break;
    default:
        break;
    }
}

void game_over_screen(struct globals *glb)
{
    clear_statusWindow_buf(glb);
    refresh_statWin(glb);
    clear_selectWindow_buf(glb);
    short w_pos, h_pos;
    w_pos = glb->selWinSize.x/2 - 4;
    h_pos = glb->selWinSize.y/2;
    text_selectWindow_buf(w_pos,h_pos,"GAME OVER",FCI_WHITE,glb);
    refresh_selWin(glb);
    Sleep(2000);
}

void run_new_game(struct globals *glb)
{
    if (glb->game_stat.game_active == 1){
    remove_list(glb);
    remove_storage_list(glb);
    }
    globals_reset_game(glb);
    glb->game_stat.game_active = 1;
    globals_reset_char(glb);
    strcpy(glb->char_stat.name,"Player1");

    update_stat_screen(glb);
}

void set_next_xp(struct globals *glb)
{
    float next_xp, old_xp, tmp_xp;
    int i;

    old_xp = 0;
    next_xp = 100;
    for(i=0; i < glb->char_stat.level; i++){
        tmp_xp = next_xp;
        next_xp = old_xp + next_xp;
        old_xp = tmp_xp;
    }
    glb->game_stat.next_xp = next_xp;
}

void display_options(struct globals *glb)
{
    clear_selectWindow_buf(glb);
    text_selectWindow_buf(0,2,"Buy DLC to activate options.",FCI_MAGENTA,glb);
    refresh_selWin(glb);
    Sleep(1000);
    text_selectWindow_buf(0,4,"Trololo ...",FCI_MAGENTA,glb);
    refresh_selWin(glb);
    Sleep(1000);
}

void exit_game(struct globals *glb)
{
    exit(0);
}

