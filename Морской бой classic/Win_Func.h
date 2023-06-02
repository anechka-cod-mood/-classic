#pragma once
#include <windows.h>
#include <iostream>

extern std::pair<int, int> console_control();
extern void set_pos_cursor(int x, int y);
extern void set_color_console(int color);
//9 - волна
//7 - ориг