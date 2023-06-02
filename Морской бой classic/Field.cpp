#include "Field.h"

Field::Field(int _width, int _length, int _x_pos, int _y_pos) {

	//инициализируем поля класса
	width	= _width;
	length	= _length;
	pos_x	= _x_pos;
	pos_y	= _y_pos;

	//инициализируем массив поля
	field = new char* [length];
	for (int i = 0; i < length; i++) {
		field[i] = new char[width];
		for (int j = 0; j < width; j++) {
			field[i][j] = '0';
		}
	}

}

std::pair<int, int> Field::get_pos_field() {
	return std::make_pair(pos_x, pos_y);
}

char Field::get_item(int x, int y) {
	return field[y][x];
}

void Field::show(int x, int y) {
	
	for (int i = -1; i < length; i++) {

		set_pos_cursor(x, y++);

		if (i == -1) {
			for (int j = 0; j < width; j++) {
				if (j == 0) {					
					cout << "   ";
				}
				cout << (char)(j + 65) << " ";
			}
			cout << endl;
			continue;
		}

		cout << setw(2) << i + 1 << '|';
		for (int j = 0; j < width; j++) {

			if (field[i][j] == '~') {
				set_color_console(9);
				std::cout << field[i][j] << " ";
				set_color_console(7);
			}
			else if (field[i][j] == '¤') {
				//set_color_console(192);
				set_color_console(12);
				std::cout << field[i][j];
				set_color_console(7);
				std::cout << " ";
			}
			else {
				std::cout << field[i][j] << " ";
			}
			
		}
		std::cout << std::endl;
	}

}

void Field::placement(int x, int y, char _literal) {

	//сделать проверку на выход за пределы массива
	/*std::cout << "Placement into Field\n";
	std::cout 
		<< "y - 1 = " << y - 1 << ", "
		<< "x - 1 = " << x - 1 << std::endl;*/

	field[y][x] = _literal;

}

char& Field::operator()(int x, int y) {
	return field[y][x];
}

int Field::get_width() {
	return width;
}
int Field::get_length() {
	return length;
}