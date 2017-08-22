
#include "menu_handler.h"

struct menu_holder* create_menu_item()
{
    struct menu_holder* menu = (struct menu_holder*)malloc(sizeof(struct menu_holder));
    menu->menu_down = NULL;
    menu->menu_up = NULL;
    menu->menu_left = NULL;
    menu->menu_right = NULL;
    return menu;
}

void connect_menu_item(struct menu_holder *menu,struct menu_holder *down,struct menu_holder *up,struct menu_holder *left,struct menu_holder *right)
{
    menu->menu_down = down;
    menu->menu_up = up;
    menu->menu_left = left;
    menu->menu_right = right;
}
