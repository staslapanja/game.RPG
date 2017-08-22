
#include "draw_handler.h"
#include "win_func.h"

void init_draw(struct globals* glb)
{
    create_selectWindowChar_buf(glb);
    create_selectWindowColor_buf(glb);
    clear_selectWindow_buf(glb);
    create_statusWindowChar_buf(glb);
    create_statusWindowColor_buf(glb);
    clear_statusWindow_buf(glb);
    create_infoWindowChar_buf(glb);
    create_infoWindowColor_buf(glb);
    clear_infoWindow_buf(glb);
	create_console(glb);
	set_console_cursor(glb);
	reset_cursor(glb);
}

void create_selectWindowChar_buf(struct globals* glb)
{
    short a = glb->selWinSize.x;
    short b = glb->selWinSize.y;

    glb->p_selWinCharBuf = (char*)malloc(sizeof(char) * a * b);
}

void create_selectWindowColor_buf(struct globals* glb)
{
    short a = glb->selWinSize.x;
    short b = glb->selWinSize.y;

    glb->p_selWinColorBuf = (unsigned short*)malloc(sizeof(unsigned short) * a * b);
}

void create_statusWindowChar_buf(struct globals* glb)
{
    short a = glb->statWinSize.x;
    short b = glb->statWinSize.y;

    glb->p_statWinCharBuf = (char*)malloc(sizeof(char) * a * b);
}

void create_statusWindowColor_buf(struct globals* glb)
{
    short a = glb->statWinSize.x;
    short b = glb->statWinSize.y;

    glb->p_statWinColorBuf = (unsigned short*)malloc(sizeof(unsigned short) * a * b);
}

void create_infoWindowChar_buf(struct globals* glb)
{
    short a = glb->infoWinSize.x;
    short b = glb->infoWinSize.y;

    glb->p_infoWinCharBuf = (char*)malloc(sizeof(char) * a * b);
}

void create_infoWindowColor_buf(struct globals* glb)
{
    short a = glb->statWinSize.x;
    short b = glb->statWinSize.y;

    glb->p_infoWinColorBuf = (unsigned short*)malloc(sizeof(unsigned short) * a * b);
}

void clear_selectWindow_buf(struct globals* glb)
{
    short a = glb->selWinSize.x;
    short b = glb->selWinSize.y;
    memset(glb->p_selWinCharBuf,0,sizeof(char) * a * b);
    memset(glb->p_selWinColorBuf,FC_WHITE,sizeof(unsigned short) * a * b);
}

void clear_statusWindow_buf(struct globals* glb)
{
    short a = glb->statWinSize.x;
    short b = glb->statWinSize.y;
    memset(glb->p_statWinCharBuf,0,sizeof(char) * a * b);
    memset(glb->p_statWinColorBuf,FC_WHITE,sizeof(unsigned short) * a * b);
}

void clear_infoWindow_buf(struct globals* glb)
{
    short a = glb->infoWinSize.x;
    short b = glb->infoWinSize.y;
    memset(glb->p_infoWinCharBuf,0,sizeof(char) * a * b);
    memset(glb->p_infoWinColorBuf,FC_WHITE,sizeof(unsigned short) * a * b);
}

void draw_framework_win_console(struct globals *globals)
{
    HANDLE console_handle;
    COORD dwSize;
    COORD dwPosition;
    DWORD written;
    int x,y;
    int split_pos_x,split_pos_y;
    char ch;

    split_pos_x = 2 + globals->selWinSize.x + 2;
    split_pos_y = 2 + globals->selWinSize.y + 2;
    console_handle = globals->p_conhandles->console_handle;
    dwSize.X = globals->dwSize.x;
    dwSize.Y = globals->dwSize.y;
	dwPosition.X = 0;
	dwPosition.Y = 0;
	SetConsoleTextAttribute(console_handle,FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	//clear screen
	for (y=0; y < dwSize.Y; y++){
	    for (x=0; x < dwSize.X; x++){
            dwPosition.X = x;
            dwPosition.Y = y;
            SetConsoleCursorPosition(console_handle, dwPosition);
            WriteFile(console_handle, " ",1, &written, NULL);
	    }
	}
	//draw box
    for (y=0; y < dwSize.Y; y++){
        if ((y == 0) || (y == (dwSize.Y-1))){
            for (x=0; x < dwSize.X; x++){
                dwPosition.X = x;
                dwPosition.Y = y;
                ch = 0xcd;
                SetConsoleCursorPosition(console_handle, dwPosition);
                WriteFile(console_handle, &ch,1, &written, NULL);
            }
        } else if (y == (split_pos_y-1)) {
            dwPosition.Y = y;
            dwPosition.X = 0;
            ch = 0xba;
            SetConsoleCursorPosition(console_handle, dwPosition);
            WriteFile(console_handle, &ch,1, &written, NULL);
            for (x=1; x < split_pos_x-1; x++){
                dwPosition.X = x;
                ch = 0xcd;
                SetConsoleCursorPosition(console_handle, dwPosition);
                WriteFile(console_handle, &ch,1, &written, NULL);
            }
            dwPosition.X = dwSize.X-1;
            ch = 0xba;
            SetConsoleCursorPosition(console_handle, dwPosition);
            WriteFile(console_handle, &ch,1, &written, NULL);
        } else {
            dwPosition.Y = y;
            dwPosition.X = 0;
            ch = 0xba;
            SetConsoleCursorPosition(console_handle, dwPosition);
            WriteFile(console_handle, &ch,1, &written, NULL);
            dwPosition.X = split_pos_x-1;
            SetConsoleCursorPosition(console_handle, dwPosition);
            WriteFile(console_handle, &ch,1, &written, NULL);
            dwPosition.X = dwSize.X-1;
            SetConsoleCursorPosition(console_handle, dwPosition);
            WriteFile(console_handle, &ch,1, &written, NULL);
        }
	}
	//corner pieces
    dwPosition.Y = 0;
    dwPosition.X = 0;
    ch = 0xc9;
    SetConsoleCursorPosition(console_handle, dwPosition);
    WriteFile(console_handle, &ch,1, &written, NULL);
    dwPosition.X = split_pos_x-1;
    ch = 0xcb;
    SetConsoleCursorPosition(console_handle, dwPosition);
    WriteFile(console_handle, &ch,1, &written, NULL);
    dwPosition.X = dwSize.X-1;
    ch = 0xbb;
    SetConsoleCursorPosition(console_handle, dwPosition);
    WriteFile(console_handle, &ch,1, &written, NULL);

    dwPosition.Y = split_pos_y-1;
    dwPosition.X = 0;
    ch = 0xcc;
    SetConsoleCursorPosition(console_handle, dwPosition);
    WriteFile(console_handle, &ch,1, &written, NULL);
    dwPosition.X = split_pos_x-1;
    ch = 0xb9;
    SetConsoleCursorPosition(console_handle, dwPosition);
    WriteFile(console_handle, &ch,1, &written, NULL);

    dwPosition.Y = dwSize.Y-1;
    dwPosition.X = 0;
    ch = 0xc8;
    SetConsoleCursorPosition(console_handle, dwPosition);
    WriteFile(console_handle, &ch,1, &written, NULL);
    dwPosition.X = split_pos_x-1;
    ch = 0xca;
    SetConsoleCursorPosition(console_handle, dwPosition);
    WriteFile(console_handle, &ch,1, &written, NULL);
    dwPosition.X = dwSize.X-1;
    ch = 0xbc;
    SetConsoleCursorPosition(console_handle, dwPosition);
    WriteFile(console_handle, &ch,1, &written, NULL);
}

void reset_cursor(struct globals *glb)
{
    glb->cursor_pos.x = 0;
    glb->cursor_pos.y = 0;
};

void set_cursor(short x, short y, struct globals *glb)
{
    glb->cursor_pos.x = x;
    glb->cursor_pos.y = y;
};

void refresh_selWin_win_console(struct globals *glb)
{
    int w,h;
    char *p_chbuf = NULL;
    unsigned short *p_colbuf = NULL;
    HANDLE chandl;
    COORD dwPos;
    DWORD written;

    w = glb->selWinSize.x;
    h = glb->selWinSize.y;
    p_chbuf = glb->p_selWinCharBuf;
    p_colbuf = glb->p_selWinColorBuf;
    chandl = glb->p_conhandles->console_handle;

    int i,j;
    //draw line by line
    for (j=0; j < h; j++){
        dwPos.Y = j+2;
        //draw item by item
        for (i=0; i < w; i++){
            dwPos.X = i+2;
            SetConsoleCursorPosition(chandl, dwPos);
            SetConsoleTextAttribute(chandl, p_colbuf[(j*w)+i]);
            WriteFile(chandl, (p_chbuf + (j*w)+i), 1, &written, NULL);
        }
    }
}

void text_selectWindow_buf(int x, int y, char text[], unsigned short color, struct globals *glb)
{
    int w,h;
    char *cptr = NULL;
    unsigned short *colptr = NULL;
    w = glb->selWinSize.x;
    h = glb->selWinSize.y;
    cptr = glb->p_selWinCharBuf;
    colptr = glb->p_selWinColorBuf;

    int i, pos;
    if (y <= h) {
        for (i=0; i < strlen(text); i++){
            pos = (y*w)+x+i;
            if (x+i < w) {
                cptr[pos] = text[i];
                colptr[pos] = color;
            }
        }
    }
}

void refresh_statWin_win_console(struct globals *glb)
{
    int w_pos,w,h;
    char *p_chbuf = NULL;
    unsigned short *p_colbuf = NULL;
    HANDLE chandl;
    COORD dwPos;
    DWORD written;

    w_pos = 2 + glb->selWinSize.x + 3;
    w = glb->statWinSize.x;
    h = glb->statWinSize.y;
    p_chbuf = glb->p_statWinCharBuf;
    p_colbuf = glb->p_statWinColorBuf;
    chandl = glb->p_conhandles->console_handle;

    int i,j;
    //draw line by line
    for (j=0; j < h; j++){
        dwPos.Y = j+2;
        //draw item by item
        for (i=0; i < w; i++){
            dwPos.X = i+w_pos;
            SetConsoleCursorPosition(chandl, dwPos);
            SetConsoleTextAttribute(chandl, p_colbuf[(j*w)+i]);
            WriteFile(chandl, (p_chbuf + (j*w)+i), 1, &written, NULL);
        }
    }
}

void text_statusWindow_buf(int x, int y, char text[], unsigned short color, struct globals *glb)
{
    int w,h;
    char *cptr = NULL;
    unsigned short *colptr = NULL;
    w = glb->statWinSize.x;
    h = glb->statWinSize.y;
    cptr = glb->p_statWinCharBuf;
    colptr = glb->p_statWinColorBuf;

    int i, pos;
    if (y <= h) {
        for (i=0; i < strlen(text); i++){
            pos = (y*w)+x+i;
            if (x+i < w) {
                cptr[pos] = text[i];
                colptr[pos] = color;
            }
        }
    }
}

void refresh_infoWin_win_console(struct globals *glb)
{
    int w,h,pos;
    char *p_chbuf = NULL;
    unsigned short *p_colbuf = NULL;
    HANDLE chandl;
    COORD dwPos;
    DWORD written;

    w = glb->infoWinSize.x;
    h = glb->infoWinSize.y;
    pos = 2 + glb->selWinSize.y + 2;
    p_chbuf = glb->p_infoWinCharBuf;
    p_colbuf = glb->p_infoWinColorBuf;
    chandl = glb->p_conhandles->console_handle;

    int i,j;
    //draw line by line
    for (j=0; j < h; j++){
        dwPos.Y = j + pos;
        //draw item by item
        for (i=0; i < w; i++){
            dwPos.X = i+2;
            SetConsoleCursorPosition(chandl, dwPos);
            SetConsoleTextAttribute(chandl, p_colbuf[(j*w)+i]);
            WriteFile(chandl, (p_chbuf + (j*w)+i), 1, &written, NULL);
        }
    }
}

void text_infoWindow_buf(int x, int y, char text[], unsigned short color, struct globals *glb)
{
    int w,h;
    char *cptr = NULL;
    unsigned short *colptr = NULL;
    w = glb->infoWinSize.x;
    h = glb->infoWinSize.y;
    cptr = glb->p_infoWinCharBuf;
    colptr = glb->p_infoWinColorBuf;

    int i, pos;
    if (y <= h) {
        for (i=0; i < strlen(text); i++){
            pos = (y*w)+x+i;
            if (x+i < w) {
                cptr[pos] = text[i];
                colptr[pos] = color;
            }
        }
    }
}

void draw_main_game_background(struct globals *glb)
{
    char line_buf[54];
    //shop building
    text_selectWindow_buf(4,3,"/\\",FCI_WHITE,glb);
    text_selectWindow_buf(3,4,"/  \\",FCI_WHITE,glb);
    line_buf[0] = 0xb3;
    line_buf[1] = 0x24;
    line_buf[2] = 0xda;
    line_buf[3] = 0xb4;
    line_buf[4] = 0x0;
    text_selectWindow_buf(3,5,line_buf,FCI_WHITE,glb);
    line_buf[0] = 0xc0;
    line_buf[1] = '-';
    line_buf[2] = 0xc1;
    line_buf[3] = 0xd9;
    line_buf[4] = '\0';
    text_selectWindow_buf(3,6,line_buf,FCI_WHITE,glb);
    //storage camp
    text_selectWindow_buf(11,16,"/\\",FC_YELLOW,glb);
    text_selectWindow_buf(10,17,"/  \\",FC_YELLOW,glb);
    text_selectWindow_buf(9,18,"\"\"\"\"\"\"\"",FC_GREEN,glb);
    text_selectWindow_buf(11,19,"\"\"\"\"",FC_GREEN,glb);
    //monster hunt area
    text_selectWindow_buf(51,12,"/\\",FC_GREEN,glb);
    text_selectWindow_buf(51,13,"/\\",FC_GREEN,glb);
    text_selectWindow_buf(40,13,"/\\",FC_GREEN,glb);
    text_selectWindow_buf(40,14,"/\\",FC_GREEN,glb);
    text_selectWindow_buf(46,14,"/\\",FC_GREEN,glb);
    text_selectWindow_buf(46,15,"/\\",FC_GREEN,glb);
    text_selectWindow_buf(37,15,"/\\",FC_GREEN,glb);
    text_selectWindow_buf(37,16,"/\\",FC_GREEN,glb);
    text_selectWindow_buf(36,17,"/\\",FC_GREEN,glb);
    text_selectWindow_buf(36,18,"/\\",FC_GREEN,glb);
    text_selectWindow_buf(40,18,"/\\",FC_GREEN,glb);
    text_selectWindow_buf(40,19,"/\\",FC_GREEN,glb);
    text_selectWindow_buf(46,18,"/\\",FC_GREEN,glb);
    text_selectWindow_buf(46,19,"/\\",FC_GREEN,glb);
    text_selectWindow_buf(50,17,"/\\",FC_GREEN,glb);
    text_selectWindow_buf(50,18,"/\\",FC_GREEN,glb);
    //empty property
    text_selectWindow_buf(25,3,"\"\"\"",FC_GREEN,glb);
    text_selectWindow_buf(23,4,"\"\"  \"\"",FC_GREEN,glb);
    text_selectWindow_buf(24,5,"\"\"\"\"\"",FC_GREEN,glb);
    //lake
    text_selectWindow_buf(37,0,"~~~~~~~~~~~~~~~~",FCI_BLUE,glb);
    text_selectWindow_buf(38,1,"~~~~~~~~~~~~~~~",FCI_BLUE,glb);
    text_selectWindow_buf(40,2,"~~~~~~~~~~~~~",FCI_BLUE,glb);
    text_selectWindow_buf(42,3,"~~~",FCI_BLUE,glb);
    text_selectWindow_buf(47,3,"~~~~~~",FCI_BLUE,glb);
    text_selectWindow_buf(43,4,"~",FCI_BLUE,glb);
    text_selectWindow_buf(49,4,"~~~",FCI_BLUE,glb);
    //coast
    text_selectWindow_buf(35,0,"\"\"",FC_GREEN,glb);
    text_selectWindow_buf(36,1,"\"\"",FC_GREEN,glb);
    text_selectWindow_buf(38,2,"\"\"",FC_GREEN,glb);
    text_selectWindow_buf(40,3,"\"\"",FC_GREEN,glb);
    text_selectWindow_buf(45,3,"\"\"",FC_GREEN,glb);
    text_selectWindow_buf(41,4,"\"\"",FC_GREEN,glb);
    text_selectWindow_buf(44,4,"\"\"\"\"\"",FC_GREEN,glb);
    text_selectWindow_buf(52,4,"\"",FC_GREEN,glb);
    text_selectWindow_buf(42,5,"\"\"\"",FC_GREEN,glb);
    text_selectWindow_buf(48,5,"\"\"\"\"\"",FC_GREEN,glb);

}

void draw_splash_screen_win_console(struct globals *glb)
{

    HANDLE console_handle;
    COORD dwPosition;
    DWORD written;

    char *p_text = (char*)malloc(sizeof(char) * 51 * 8);
    char *p_text_name = (char*)malloc(sizeof(char) * 15);
    unsigned short *p_color = (unsigned short*)malloc(sizeof(unsigned short) * (51+4));
    unsigned short p_color_temp;

    //Note: backslashes "\" need to be escaped!
    p_text = "                              _____  _____   _____ "
             "                             |  __ \\|  __ \\ / ____|"
             "  __ _  __ _ _ __ ___   ___  | |__) | |__) | |  __ "
             " / _` |/ _` | '_ ` _ \\ / _ \\ |  _  /|  ___/| | |_ |"
             "| (_| | (_| | | | | | |  __/_| | \\ \\| |    | |__| |"
             " \\__, |\\__,_|_| |_| |_|\\___(_)_|  \\_\\_|     \\_____|"
             "  __/ |                                            "
             " |___/                                             ";



    p_text_name = "by Lapanja Stas";
    int i,j;
    for (i = 0; i < 51; i++){
        p_color[i] = FCI_CYAN;
    }
    p_color[51] = FC_CYAN;
    p_color[52] = FCI_CYAN;
    p_color[53] = FCI_WHITE;
    p_color[54] = FC_CYAN;

    console_handle = glb->p_conhandles->console_handle;
    SetConsoleTextAttribute(console_handle,FCI_CYAN);


    dwPosition.X = (glb->dwSize.x - 22) / 2;
	dwPosition.Y = glb->dwSize.y - 1;
	SetConsoleCursorPosition(console_handle, dwPosition);
	WriteFile(console_handle, "press any key to start",22, &written, NULL);

    int exit_screen;
    exit_screen = 0;
    while(!exit_screen){
        //letter shine

        dwPosition.Y = 2;
        for (j=0; j < 8; j++){
            dwPosition.X = (glb->dwSize.x - 51) / 2;
            for (i=0; i < 51; i++){
                SetConsoleCursorPosition(console_handle, dwPosition);
                SetConsoleTextAttribute(console_handle,p_color[i]);
                WriteFile(console_handle,p_text+i+(j*51),1,&written, NULL);
                dwPosition.X++;
            }
            dwPosition.Y++;
        }

        dwPosition.X = 50;
        dwPosition.Y = 12;
        SetConsoleCursorPosition(console_handle, dwPosition);
        for (i=0; i < 15; i++){
            SetConsoleTextAttribute(console_handle,p_color[36+i]);
            WriteFile(console_handle, p_text_name+i,1, &written, NULL);
        }

        //shift colours
        p_color_temp = p_color[54];
        for (i = 54; i > 0; i--){
            p_color[i] = p_color[i-1];
        }
        p_color[0] = p_color_temp;

        //react to input
        get_input_key(glb);
        if (glb->input_key != 0x0){
            exit_screen = 1;
        }

        Sleep(50);
    }

}

//select system specific calls
void draw_framework(struct globals *glb)
{
    draw_framework_win_console(glb);
}
void refresh_selWin(struct globals *glb)
{
    refresh_selWin_win_console(glb);
}
void refresh_statWin(struct globals *glb)
{
    refresh_statWin_win_console(glb);
}
void draw_splash_screen(struct globals *glb)
{
    draw_splash_screen_win_console(glb);
}
void refresh_infoWin(struct globals *glb)
{
    refresh_infoWin_win_console(glb);
}
