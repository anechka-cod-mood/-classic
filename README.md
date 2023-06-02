#include "Game.h"

Game::Game() {

	SetConsoleTitle(L"Морской Бой Classic");
}

void Game::start_menu() {

    set_mode();
    system("cls");
    if (mode == 1) {

        player_1        = new Player("Игрок номер 1");
        player_1_field  = new Field;
        cout << player_1->get_name() << " раставляет свои корабли\n";
        system("pause");        

        std::array<int, 4>* ptr = nullptr; //не удалять !!!
        placement(player_1_field, ptr);
        player_1->setup_enemy_field();
        clearConsole();

        player_1->set_my_field(player_1_field);

        player_2 = new Player("Игрок номер 2");
        player_2_field  = new Field;
        cout << player_2->get_name() << " раставляет свои корабли\n";
        system("pause");
        placement(player_2_field, ptr);
        player_2->setup_enemy_field();
        clearConsole();

        player_2->set_my_field(player_1_field);

    }
    else if (mode == 2) {

        player_1        = new Player("Игрок номер 1");
        player_1_field  = new Field;
        cout << player_1->get_name() << " раставляет свои корабли\n";
        system("pause");

        std::array<int, 4>* ptr = nullptr; //не удалять !!!
        placement(player_1_field, ptr);
        player_1->setup_enemy_field();
        clearConsole();

        player_1->set_my_field(player_1_field);

        player_2        = new Player("Компьютер 1");
        player_2_field  = new Field;        

        placement_bot(player_2_field, ptr);
        player_2->setup_enemy_field();
        player_2->set_my_field(player_2_field);        

    }

    run();

}

bool Game::move(Player* player, Field* enemy_field) {    

    cout << player->get_name() << " приготовиться!\n";
    system("pause");
    clearConsole();

    cout << player->get_name() << "! Стреляйте!\n";
    player->get_enemy_field()->show(0, 1);
    //player_2_field->show(0, 1);

    set_pos_cursor(31, 0);
    cout << "Ваш флот\n";
    player->get_my_field()->show(31, 1);
    //player_1_field->show(31, 1);

    auto result = fire(enemy_field, player->get_enemy_field());
    clearConsole();

    if (result == 5) {
        cout << player->get_name() << " - мимо\n";
    }
    else if (result == 3) {
        player->get_count_hit()++;
        cout << player->get_name() << " - попадание\n";
    }

    player->get_enemy_field()->show(0, 1);

    set_pos_cursor(31, 0);
    cout << "Ваш флот\n";
    player->get_my_field()->show(31, 1);

    system("pause");
    clearConsole();

    if (player->get_count_hit() >= 20) {
        return true;
    }
    else {
        return false;
    }

}

void Game::run() {

    if (mode == 1)
    {
        while (true)
        {
            player_1->set_my_field(player_1_field);
            if (move(player_1, player_2_field)) {
                cout << player_1->get_name() << " одержал победу!\n";
                break;
            }

            player_2->set_my_field(player_2_field);
            if (move(player_2, player_1_field)) {
                cout << player_2->get_name() << " одержал победу!\n";
                break;
            }
        }
    }
    else if (mode == 2) {
       
        while (true)
        {
            player_1->set_my_field(player_1_field);
            if (move(player_1, player_2_field)) {
                cout << player_1->get_name() << " одержал победу!\n";
                break;
            }

            player_2->set_my_field(player_2_field);
            if (move_bot(player_2, player_1_field)) {
                cout << player_2->get_name() << " одержал победу!\n";
                break;
            }
        }

    }

}

bool Game::move_bot(Player* bot, Field* enemy) {

    enum Mode_Fire {
        random,
        right, left,
        top, bottom
    };

    static int mode_fire = Mode_Fire::random;
    static int x_pos;
    static int y_pos;
    static int count_deck = 0;

    if (mode_fire == Mode_Fire::random) {

        count_deck = 0;
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution_pos(0, 9);

        x_pos = distribution_pos(generator);
        y_pos = distribution_pos(generator);
        
    }
    else if (mode_fire == Mode_Fire::right) {

        if (x_pos + 1 < 10) {
            x_pos++;
        }
        else {
            x_pos = x_pos - (count_deck - 1);
            mode_fire++;
            move_bot(bot, enemy);
        }

    }
    else if (mode_fire == Mode_Fire::left) {

        if (x_pos - 1 >= 0) {
            x_pos--;
        }
        else {
            x_pos = x_pos + (count_deck - 1);
            mode_fire++;
            move_bot(bot, enemy);
        }

    }
    else if (mode_fire == Mode_Fire::top) {

        if (y_pos - 1 >= 0) {
            y_pos--;
        }
        else {
            y_pos = y_pos + (count_deck - 1);
            mode_fire++;
            move_bot(bot, enemy);
        }

    }
    else if (mode_fire == Mode_Fire::bottom) {

        if (y_pos + 1 < 10) {
            y_pos++;
        }
        else {
            y_pos = y_pos - (count_deck - 1);
            mode_fire = Mode_Fire::random;
            move_bot(bot, enemy);
        }

    }

    if ((*enemy)(x_pos, y_pos) == '3' || (*enemy)(x_pos, y_pos) == '5') {
        move_bot(bot, enemy);
    }
    else if ((*enemy)(x_pos, y_pos) == '0' || (*enemy)(x_pos, y_pos) == '+') {
        enemy->placement(x_pos, y_pos, '5');

        if (mode_fire == Mode_Fire::bottom)
        {
            count_deck = 0;
            mode_fire = Mode_Fire::random;
        }
        else if (mode_fire == Mode_Fire::random) {
           
        }
        else if (mode_fire == Mode_Fire::left) {
            x_pos = x_pos + count_deck;
            mode_fire++;
        }
        else {
            mode_fire++;
        }
    }
    else if ((*enemy)(x_pos, y_pos) == '2') {

        if (mode_fire == Mode_Fire::random)
        {
            mode_fire++;
        }
        enemy->placement(x_pos, y_pos, '3');
        bot->get_count_hit()++;
        count_deck++;
    }

    if (bot->get_count_hit() >= 20) {
        return true;
    }
    else {
        return false;
    }

}

int Game::fire(Field* field_invisible, Field* field_visible) {

    std::pair<int, int> pos;

    while(true)
    {

        while (true) {
            pos = console_control();
            if (3 <= pos.first && pos.first < 23 && 2 <= pos.second && pos.second < 12) {
                //cout << "Pos: " << pos.first << " - " << pos.second << endl;
                break;
            }
            else {
                //cout << "Мимо поля\n";
            }
        }

        int x_pos = (pos.first - 3) / 2;
        int y_pos = pos.second - 2;

        //cout << "Field pos: " << x_pos << " - " << y_pos << " - ";

        auto item = field_invisible->get_item((pos.first - 3) / 2, pos.second - 2);

        //cout << "Item: " << item << endl;

        if (item == '0' || item == '+') {
            cout << "Мимо\n";
            (*field_visible)(x_pos, y_pos) = '·';
            return 5;
        }
        else if (item == '2') {
            cout << "Попадание\n";
            (*field_visible)(x_pos, y_pos) = '¤';
            field_invisible->placement((pos.first - 3) / 2, pos.second - 2, '3');
            return 3;
        }
        
    }

}

void Game::set_mode() {
       
    while (true) {

        std::cout << "Морской Бой: Classic\n";
        std::cout << "Выберете режим(1 - с игроком; 2 - с компьютером)\n";

        std::cin >> mode;

        if (std::cin.good() && (mode == 1 || mode == 2)) {
            break;
        }
        else {
            system("cls");
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }

    }

}

void Game::add_player(Player* player) {

    players.push_back(player);

}

void Game::placement_bot(Field* field, std::array<int, 4>*& check_crue) {
    
    if (!check_crue) {        
        check_crue = new std::array<int, 4>{
            4, 3, 2, 1
        };        
    }

    int count_deck = 0;
    for (int i = 0; i < check_crue->size(); i++) {
        count_deck += (*check_crue)[i] * (i + 1);
    }
    
    for (int i = 0; i < count_deck; i++) {
                
        std::random_device rd;
        std::mt19937 generator(rd());        
        std::uniform_int_distribution<int> distribution_pos(0, 9);
        std::uniform_int_distribution<int> distribution_orientation(1, 2);

        int x_pos = distribution_pos(generator);
        int y_pos = distribution_pos(generator);
        int orientation = distribution_orientation(generator);

        for (int j = 0; j < 4; j++) {

            if (0 <= x_pos && x_pos < field->get_width() && 0 <= y_pos && y_pos < field->get_length()) {

                if (field->get_item(x_pos, y_pos) == '2' || field->get_item(x_pos, y_pos) == '+') {
                    break;
                }

                field->placement(x_pos, y_pos, '1');
                                
            }
            else {                
                i--;
                break;
            }                

            if (orientation == Orientation::horizontal) {
                x_pos++;
            }
            else if (orientation == Orientation::vertical) {
                y_pos++;
            }

        }        

    }

    for (int row = 0; row < field->get_length(); row++) {
        for (int col = 0; col < field->get_width(); col++) {

            if ((*field)(col, row) == '1') try {

                Ship ship(field, col, row, check_crue);

                ship.scan(field);                            

                ships_player_1.push_back(ship);

            }
            catch (std::logic_error& exc) {
                //std::cout << exc.what() << std::endl;
            }
            catch (std::exception& exc) {
                //std::cout << exc.what() << std::endl;
                //field->show();
            }

        }
    }

    for (auto it = check_crue->begin(); it != check_crue->end(); it++) {
        
        if (*it != 0) {            
            placement_bot(field, check_crue);            
            break;
        }
    }

    if (check_crue) {        
        delete check_crue;
        check_crue = nullptr;        
    }
       

}

void Game::placement(Field* field, std::array<int, 4>*& check_crue) {
	
    clearConsole();
	//field->show();

    Player player;
    player.set_my_field(field);
    player.get_my_field()->show();

    cout << "\nРазместите Ваши корабли\n";

    if (!check_crue) {
        //cout << "Чек крю пустой\n";
        check_crue = new std::array<int, 4>{
            4, 3, 2, 1
        };
        //system("pause");
    }

    int count_deck = 0;
    for (int i = 0; i < check_crue->size(); i++) {
        count_deck += (*check_crue)[i] * (i + 1);
    }    
    //cout << "Число палуб: " << count_deck << endl;

    cout << "Вам необходимо выставить:\n";
    for (int i = 0; i < check_crue->size(); i++) {
        cout 
            << i + 1 << " - палубных: " << (*check_crue)[i] 
            << (i == check_crue->size() - 1 ? "" : "\n");
    }

    for (int i = 0; i < count_deck; i++) {

        auto coord = console_control();        

        int x_pos = (coord.first - 3) / 2;
        int y_pos = coord.second - 1;

        if (0 <= x_pos && x_pos < field->get_width() && 0 <= y_pos && y_pos < field->get_length()) {

            if (field->get_item(x_pos, y_pos) == '2' || field->get_item(x_pos, y_pos) == '+') {
                i--;
                continue;
            }

            field->placement(x_pos, y_pos, '1');

            clearConsole();
            //field->show();
            player.set_my_field(field);
            player.get_my_field()->show();

            cout << "Вам необходимо выставить:\n";
            for (int i = 0; i < check_crue->size(); i++) {
                cout 
                    << i + 1 << " - палубных: " << (*check_crue)[i] 
                    << (i == check_crue->size() - 1? "": "\n");
            }

            /*cout << "Сырые: " << coord.first << " - " << coord.second << endl;
            cout << "Обработанные: " << x_pos << " - " << y_pos << endl;*/
        }
        else {
            //cout << "Мимо поля\n";
            i--;
        }        
        
    }      

    for (int row = 0; row < field->get_length(); row++) {
        for (int col = 0; col < field->get_width(); col++) {

            if ((*field)(col, row) == '1') try {

                Ship ship(field, col, row, check_crue);

                ship.scan(field);
                //field->show();            

                ships_player_1.push_back(ship);

            }
            catch (std::logic_error& exc) {
                std::cout << exc.what() << std::endl;
            }
            catch (std::exception& exc) {
                //std::cout << exc.what() << std::endl;
                //field->show();
            }

        }
    } 

    for (auto it = check_crue->begin(); it != check_crue->end(); it++) {

        //cout << *it << endl;

        if (*it != 0) {
            /*cout << "Перед входом в рекурсию\n";
            system("pause");*/
            placement(field, check_crue);            
            //cout << "После выхода из функции\n";
            break;
        }
    }

    if (check_crue) {
        //cout << "Чек крю НЕ пустой перед удаление\n";
        delete check_crue;
        check_crue = nullptr;
        //cout << "Чек крю удален\n";
    }
    else {
        //cout << "Чек крю пустой\n";
    }
   

}
