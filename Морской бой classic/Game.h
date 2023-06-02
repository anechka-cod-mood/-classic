#pragma once

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include <array>
#include <random>

#include "Field.h"
#include "Clear_Console.h"
#include "Ship.h"
#include "Player.h"

#include "Win_Func.h"

using namespace std;

class Game{
private:
	std::vector<Player*> players;

	Player* player_1 = nullptr;
	Player* player_2 = nullptr;

	Field* player_1_field = nullptr;
	Field* player_2_field = nullptr;

	std::vector<Ship> ships_player_1;

	int mode;

public:
	Game();
	void placement(Field* field, std::array<int, 4>*& check_crue);
	void placement_bot(Field* field, std::array<int, 4>*& check_crue);
	//bool check_count_ships(std::vector<Ship> ships_player);
	void add_player(Player* player);

	void run();
	bool move(Player*, Field* enemy);
	bool move_bot(Player*, Field* enemy);

	void set_mode();
	void start_menu();

	int fire(Field* field_invisible, Field* field_visible);

};

