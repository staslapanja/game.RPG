
#include "win_func.h"

void create_console(struct globals *globals){
    COORD dwSize;
    DWORD lpMode;
    HANDLE console_handle;
    SMALL_RECT rect;


	console_handle = CreateConsoleScreenBuffer(GENERIC_READ|GENERIC_WRITE,0, NULL,CONSOLE_TEXTMODE_BUFFER,NULL);
    //disable automatic wrap at end of line because it will otherwise scroll the whole buffer
	//for one line when the lowest right character is written
	GetConsoleMode(console_handle, &lpMode);
	SetConsoleMode(console_handle, lpMode & ~ENABLE_WRAP_AT_EOL_OUTPUT);

    dwSize.X = globals->dwSize.x;
	dwSize.Y = globals->dwSize.y;

	rect.Top = 0;
	rect.Left = 0;
	rect.Bottom = dwSize.Y - 1;
	rect.Right = dwSize.X -1;
	SetConsoleScreenBufferSize(console_handle, dwSize);
    SetConsoleActiveScreenBuffer(console_handle);
	SetConsoleWindowInfo(console_handle,TRUE,&rect);
	globals->p_conhandles->console_handle = console_handle;
}

void set_console_cursor(struct globals *globals){
    CONSOLE_CURSOR_INFO cursor_info;
 	cursor_info.dwSize = 1;
	cursor_info.bVisible = FALSE;
	SetConsoleCursorInfo(globals->p_conhandles->console_handle, &cursor_info);
}

void create_input_handle(struct globals *globals){
    HANDLE input_handle;

    input_handle=GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(input_handle, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
    globals->p_conhandles->input_handle = input_handle;
}

double get_time(void)
{
    struct timeb timebuffer;
    double seconds;
    double milliseconds;
    double sum;

    ftime( &timebuffer );

    seconds = (double) timebuffer.time;
    milliseconds = (double) timebuffer.millitm;

    sum = seconds + (milliseconds / 1000);

    return sum;
}
