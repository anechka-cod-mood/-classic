#include "Player.h"

Player::Player(std::string name)
	: name{name} {

}

Field* Player::get_my_field() {
	return my_field;
}

Field* Player::get_enemy_field() {
	return enemy_field;
}

void Player::setup_enemy_field(Field* field) { //немного некоректно работает

	if (field) {
		enemy_field = field;
	}
	else {
		if (enemy_field) {
			delete enemy_field;
			enemy_field = new Field;
		}
		else {
			enemy_field = new Field;
		}
	}

	for (int row = 0; row < enemy_field->get_length(); row++) {
		for (int colm = 0; colm < enemy_field->get_width(); colm++) {
			(*enemy_field)(colm, row) = '~';
		}
	}

}

void Player::set_my_field(Field* game_field) {

	try {
		my_field = new Field;
	}
	catch(std::exception& exc) {
		std::cout << exc.what();
	}

	for (int row = 0; row < my_field->get_length(); row++) {
		for (int colm = 0; colm < my_field->get_width(); colm++) {

			if ((*game_field)(colm, row) == '2' || (*game_field)(colm, row) == '1')
			{
				(*my_field)(colm, row) = 'п';
			}
			else if ((*game_field)(colm, row) == '0' || (*game_field)(colm, row) == '+'/* || (*game_field)(colm, row) == '5'*/) {
				(*my_field)(colm, row) = '~';
			}
			else if ((*game_field)(colm, row) == '3') {
				(*my_field)(colm, row) = '¤';
			}
			else if ((*game_field)(colm, row) == '5') {
				(*my_field)(colm, row) = '·';
			}

		}
	}

}