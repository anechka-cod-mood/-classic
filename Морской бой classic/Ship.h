#pragma once
#include "Field.h"

#include <array>

enum Orientation {
	undifened,
	horizontal,
	vertical

};

class Ship
{
private:
	int count_deck;
	int orientation;
	int x_pos;
	int y_pos;

public:
	Ship(Field*, int x_pos, int y_pos, std::array<int, 4>* check_crue);
	void scan(Field*);
	int get_count_deck();

	void get_info() {
		std::cout
			<< "Число палуб: " << count_deck << std::endl
			<< "Ориентация: " << orientation << std::endl
			<< "x_pos: " << x_pos << std::endl
			<< "y_pos: " << y_pos << std::endl;

	}

};

