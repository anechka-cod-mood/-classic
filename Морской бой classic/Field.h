#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <iomanip>
#include "Win_Func.h"

using namespace std;

class Field {
private:
    int width;
    int length;
    char** field = nullptr;

    int pos_x;
    int pos_y;

public:   
    Field(int _width = 10, int _length = 10, int _x_pos = 0, int _y_pos = 0);
    void show(int x = 0, int y = 0);
    void placement(int x, int y, char _literal);

    char get_item(int x, int y);

    char& operator()(int x, int y);

    int get_width();
    int get_length();
    std::pair<int, int> get_pos_field();
    
};

#endif

