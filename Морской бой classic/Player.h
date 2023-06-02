#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Field.h"

class Player {
private:
	std::string name;
	Field*		my_field	= nullptr;
	Field*		enemy_field	= nullptr;

	int count_hit = 0;

public:
	Player(std::string name = "player_default");
	void set_my_field(Field* game_field);
	void setup_enemy_field(Field* filed = nullptr);

	Field* get_my_field();
	Field* get_enemy_field();

	std::string get_name() {
		return name;
	}

	int& get_count_hit() {
		return count_hit;
	}

};

#endif