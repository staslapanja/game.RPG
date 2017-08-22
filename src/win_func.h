#ifndef WIN_CONSOLE_H
#define WIN_CONSOLE_H

#include <windows.h>
#include <sys/timeb.h>
#include "global_handler.h"

#define FC_RED      FOREGROUND_RED
#define FC_BLUE     FOREGROUND_BLUE
#define FC_GREEN    FOREGROUND_GREEN
#define FC_YELLOW   FOREGROUND_GREEN  | FOREGROUND_RED
#define FC_CYAN     FOREGROUND_GREEN  | FOREGROUND_BLUE
#define FC_MAGENTA  FOREGROUND_RED    | FOREGROUND_BLUE
#define FC_WHITE    FOREGROUND_RED    | FOREGROUND_BLUE   | FOREGROUND_GREEN
#define FC_BLACK    0
#define FCI_RED     FOREGROUND_INTENSITY    | FOREGROUND_RED
#define FCI_BLUE    FOREGROUND_INTENSITY    | FOREGROUND_BLUE
#define FCI_GREEN   FOREGROUND_INTENSITY    | FOREGROUND_GREEN
#define FCI_YELLOW  FOREGROUND_INTENSITY    | FOREGROUND_GREEN  | FOREGROUND_RED
#define FCI_CYAN    FOREGROUND_INTENSITY    | FOREGROUND_GREEN  | FOREGROUND_BLUE
#define FCI_MAGENTA FOREGROUND_INTENSITY    | FOREGROUND_RED    | FOREGROUND_BLUE
#define FCI_WHITE   FOREGROUND_INTENSITY    | FOREGROUND_RED    | FOREGROUND_BLUE   | FOREGROUND_GREEN
#define FCI_BLACK   0
#define BC_RED      BACKGROUND_RED
#define BC_BLUE     BACKGROUND_BLUE
#define BC_GREEN    BACKGROUND_GREEN
#define BC_YELLOW   BACKGROUND_GREEN  | BACKGROUND_RED
#define BC_CYAN     BACKGROUND_GREEN  | BACKGROUND_BLUE
#define BC_MAGENTA  BACKGROUND_RED    | BACKGROUND_BLUE
#define BC_WHITE    BACKGROUND_RED    | BACKGROUND_BLUE   | BACKGROUND_GREEN
#define BC_BLACK    0
#define BCI_RED     BACKGROUND_INTENSITY    | BACKGROUND_RED
#define BCI_BLUE    BACKGROUND_INTENSITY    | BACKGROUND_BLUE
#define BCI_GREEN   BACKGROUND_INTENSITY    | BACKGROUND_GREEN
#define BCI_YELLOW  BACKGROUND_INTENSITY    | BACKGROUND_GREEN  | BACKGROUND_RED
#define BCI_CYAN    BACKGROUND_INTENSITY    | BACKGROUND_GREEN  | BACKGROUND_BLUE
#define BCI_MAGENTA BACKGROUND_INTENSITY    | BACKGROUND_RED    | BACKGROUND_BLUE
#define BCI_WHITE   BACKGROUND_INTENSITY    | BACKGROUND_RED    | BACKGROUND_BLUE   | BACKGROUND_GREEN
#define BCI_BLACK    0

#define KEY_DOWN    VK_DOWN
#define KEY_UP      VK_UP
#define KEY_LEFT    VK_LEFT
#define KEY_RIGHT   VK_RIGHT
#define KEY_RETURN  VK_RETURN
#define KEY_ESCAPE  VK_ESCAPE
#define MOUSE_LCLK  VK_LBUTTON

struct console_handles {
    HANDLE  console_handle  ;
	HANDLE  input_handle    ;
};

void create_console(struct globals *globals);
void set_console_cursor(struct globals *globals);
void create_input_handle(struct globals *globals);
double get_time(void);

#endif