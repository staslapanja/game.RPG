
#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <windows.h>
#include "global_handler.h"
#include "win_func.h"

void init_input(struct globals *globals);
void get_input_key_win_cosole(struct globals *globals);
void get_input_key(struct globals *globals);

#endif

