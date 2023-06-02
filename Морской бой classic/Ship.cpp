#include "Ship.h"

Ship::Ship(Field* field, int _x_pos, int _y_pos, std::array<int, 4>* check_crue) {
	
    x_pos = _x_pos;
    y_pos = _y_pos;
    orientation = Orientation::undifened;
    count_deck = 1;

    for (int pos_x = _x_pos + 1; pos_x < field->get_width(); pos_x++) {

        if ((*field)(pos_x, _y_pos) == '1') {
            orientation = Orientation::horizontal;
            count_deck++;

            if (count_deck >= 5) {
                throw std::logic_error("¬озможно не более четырех палуб");
            }

        }
        else if ((*field)(pos_x, _y_pos) == '0') {
            break;
        }

    }

    if (orientation != Orientation::horizontal)
    {
        for (int pos_y = _y_pos + 1; pos_y < field->get_length(); pos_y++) {

            if ((*field)(_x_pos, pos_y) == '1') {
                orientation = Orientation::vertical;
                count_deck++;

                if (count_deck >= 5) {
                    throw std::logic_error("¬озможно не более четырех палуб");
                }

            }
            else if ((*field)(_x_pos, pos_y) == '0') {
                break;
            }
        }
    }

    /*std::cout << "Pos_x: " << x_pos << " - " << y_pos << std::endl;
    std::cout << "Count deck: " << count_deck << std::endl;
    std::cout << "Orientation: " << (orientation == Orientation::horizontal ? "Horizontal\n" : "Vertical\n");*/

    if ((*check_crue)[get_count_deck() - 1] - 1 < 0) {

        if (orientation == Orientation::horizontal) {

            for (int x = x_pos; x < x_pos + count_deck; x++) {
                (*field)(x, y_pos) = '0';
            }

        }
        else if (orientation == Orientation::vertical) {

            for (int y = y_pos; y < y_pos + count_deck; y++) {
                (*field)(x_pos, y) = '0';
            }

        }
        else if (orientation == Orientation::undifened) {

            (*field)(x_pos, y_pos) = '0';

        }

        throw std::exception("„исло кораблей данного типа достигло максимума");
    }
    else {
        /*std::cout
            << "„исло палуб: " << get_count_deck() << std::endl
            << "—колько кораблей еще доступно: " << check_crue[get_count_deck() - 1] << std::endl;*/
        (*check_crue)[get_count_deck() - 1]--;
    }

}

void Ship::scan(Field* field) {

    int end_row;
    int end_colm;

    //сделать проверку если координата сканировани€ выходит за пределы пол€
    if (orientation == Orientation::horizontal) {
        end_row = y_pos + 2;
        end_colm = x_pos + 1 + count_deck;
    }
    else if (orientation == Orientation::vertical) {
        end_row = y_pos + 1 + count_deck;
        end_colm = x_pos + 2;
    }
    else if (orientation == Orientation::undifened) {
        end_row = y_pos + 2;
        end_colm = x_pos + 2;
    }
    else {
        throw std::exception("Ќ≈ возможно выполнить сканирование\n");
    } 

    if (end_colm > field->get_width()) {
        end_colm = field->get_width();
    }

    if (end_row > field->get_length()) {
        end_row = field->get_length();
    }
       
    /*std::cout << "end row: " << end_row << std::endl;
    std::cout << "end colm: " << end_colm << std::endl;*/

    //нужно проверить colm и row и end_row и end_colm на инициализацию на уголочках

    for (int row = (y_pos - 1 < 0? y_pos: y_pos - 1); row < end_row; row++) {
        for (int colm = (x_pos - 1 < 0? x_pos: x_pos - 1); colm < end_colm; colm++) {

            /*std::cout << "row: " << row << std::endl;
            std::cout << "colm: " << colm << std::endl;
            std::cout << "Field: " << (*field)(colm, row) << std::endl;*/

            if ((*field)(colm, row) == '1') {

                if (orientation == Orientation::horizontal){
                    
                    if (!(y_pos == row && x_pos <= colm && colm < x_pos + count_deck)) {
                        (*field)(colm, row) = '+';
                        //throw std::exception("Ќеверное размещение\n");
                    }
                    else {
                        (*field)(colm, row) = '2';
                    }

                }
                else if (orientation == Orientation::vertical) {

                    if (!(x_pos == colm && y_pos <= row && row < y_pos + count_deck)) {
                        (*field)(colm, row) = '+';
                        //throw std::exception("Ќеверное размещение\n");
                    }
                    else {
                        (*field)(colm, row) = '2';
                    }

                }
                else if (orientation == Orientation::undifened) {

                    if (!(x_pos == colm && y_pos == row)) {
                        (*field)(colm, row) = '+';
                        //throw std::exception("Ќеверное размещение\n");
                    }
                    else {
                        (*field)(colm, row) = '2';
                    }

                }

            }
            else if ((*field)(colm, row) == '0') {
                (*field)(colm, row) = '+';
            }

        }
    }

    //std::cout << "—канирование вокруг корабл€ прошло успешно\n\n";    

}

int Ship::get_count_deck() {
    return count_deck;
}