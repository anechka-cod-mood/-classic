#include "Clear_Console.h"

void clearConsole()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition = { 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

    GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
    DWORD consoleSize = consoleInfo.dwSize.X * consoleInfo.dwSize.Y;
    DWORD written;

    FillConsoleOutputCharacter(consoleHandle, ' ', consoleSize, cursorPosition, &written);
    FillConsoleOutputAttribute(consoleHandle, consoleInfo.wAttributes, consoleSize, cursorPosition, &written);
    SetConsoleCursorPosition(consoleHandle, cursorPosition);
}