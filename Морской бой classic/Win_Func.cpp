#include "Win_Func.h"

void set_color_console(int color) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

std::pair<int, int> console_control() {

    HANDLE          hInstance = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD    input_record;
    DWORD		    events;

    /*Запретить выделение консоли*/
    DWORD prev_mode;
    GetConsoleMode(hInstance, &prev_mode);
    SetConsoleMode(hInstance, ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
    SetConsoleMode(hInstance, ENABLE_MOUSE_INPUT); // разрешаем обработку мыши    

    COORD		 coord;

    while (true) {

        ReadConsoleInput(hInstance, &input_record, 1, &events);

        if (input_record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) { // левая кнопка

            coord.X = input_record.Event.MouseEvent.dwMousePosition.X;
            coord.Y = input_record.Event.MouseEvent.dwMousePosition.Y;

            return std::make_pair(coord.X, coord.Y);            

        }
        /*else if (input_record.EventType == KEY_EVENT && input_record.Event.KeyEvent.bKeyDown) {
            if (input_record.Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {
                std::cout << "Enter\n";
                break;
            }
        }*/

    }
}

void set_pos_cursor(int x, int y) {

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(console, pos);

}