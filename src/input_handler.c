
#include "input_handler.h"

void init_input(struct globals *globals)
{
    create_input_handle(globals);
}

void get_input_key(struct globals *globals)
{
    get_input_key_win_cosole(globals);
}

void get_input_key_win_cosole(struct globals *globals)
{
    HANDLE input_handle;
    WORD key;
    WORD mouse;
    DWORD NumInputs = 0;
    DWORD cNumRead;
    INPUT_RECORD irInBuf[128];
    int key_toggle=0;

    input_handle = globals->p_conhandles->input_handle;

    if (globals->game_stat.skip_wait_keypress == 1) {
        GetNumberOfConsoleInputEvents(input_handle,&NumInputs);
    } else {
        NumInputs = 1;
    }
    //ReadConsoleInput waits until there is some activity
    //check first if any activity is present
    //this way the function will not wait for events
    //if such behaviour is required
    if (NumInputs > 0) {
        ReadConsoleInput(
                input_handle,// input buffer handle
                irInBuf,     // buffer to read into
                128,         // size of read buffer
                &cNumRead);
    } else {
        //make sure event is disabled
        irInBuf[0].EventType = 0;
    }
    key=0x0;
    mouse=0x0;

    switch(irInBuf[0].EventType)
    {
        case KEY_EVENT: // keyboard input
            if (irInBuf[0].Event.KeyEvent.bKeyDown){
                key=irInBuf[0].Event.KeyEvent.wVirtualKeyCode;
                FlushConsoleInputBuffer(input_handle);
                key_toggle=1;
            } else {
                key_toggle=0;
            }
            break;

        case MOUSE_EVENT: // mouse input
//            switch(irInBuf[0].Event.MouseEvent.dwEventFlags)
//            {
//                case 0: //mouse click
//                    if (irInBuf[0].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
//                        mouse = MOUSE_LCLK;
//                    }
//                    break;
//                default:
//                    break;
//            }
            break;

        case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
            break;

        case FOCUS_EVENT:  // disregard focus events

        case MENU_EVENT:   // disregard menu events
            break;

        default:
            break;
    }

    globals->input_key = key;
    globals->input_mouse = mouse;
    globals->input_toggle = key_toggle;
}
