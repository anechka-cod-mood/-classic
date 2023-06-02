#include <iostream>
#include <windows.h>
#include "Field.h"
#include "Player.h"
#include "Game.h"

int main(){
    //SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "rus");       

    Game battle_sea;
    battle_sea.start_menu();       

    return 0;
}

