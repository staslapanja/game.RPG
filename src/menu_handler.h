
#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include "global_handler.h"

struct menu_holder
{
    struct menu_holder* menu_down;
    struct menu_holder* menu_up;
    struct menu_holder* menu_left;
    struct menu_holder* menu_right;
};

struct menu_holder* create_menu_item();
void connect_menu_item(struct menu_holder *menu,struct menu_holder *down,struct menu_holder *up,struct menu_holder *left,struct menu_holder *right);

#endif
