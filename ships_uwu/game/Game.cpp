#include "Game.h"

Game::Game(){
    std::cout << "Hi, it's sea battle :)\nLet sea battle decide how much of a pirate you are." << endl;
    std::cout << "First, enter the size of the field:" << endl;
    int field_size;
    std::cin >> field_size;
    while (true){
    try {
        // Проверка размера поля
        if (field_size <= 6 || field_size >= 100) {
            throw InvalidFieldSize();
        }

        break; // Выходим из цикла при корректном вводе

    } catch (const InvalidFieldSize& e) {
        cout << e.what() << "Error " << endl;
        std::cin.clear(); // Сбрасываем состояние ошибки
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер ввода
        cout << "Enter a new correct value (>6 or <100): " << endl;
        cin >> field_size;
    }}

    // создаем поле игрока и ботика
    auto user_field = std::make_shared<Field>(field_size);
    auto botik_field = std::make_shared<Field>(field_size);
    
    //делаем шип менеджер для игрока
    std::vector<int> all_ship_len;
    std::vector<int> all_ship_count;
    
    // потом генерим шип менеджер для бота исходя из длин кораблей
    std::cout << "Enter the length of the ship and their number like '4 1'" << std::endl;
    std::cout << "To finish input, enter '0 0'.\n";

    int length, count;
    while (true) {
        std::cout << "Enter length and count: ";

        // Проверяем ввод
        if (!(std::cin >> length >> count)) {
            std::cout << "Input error. Please enter two numbers separated by a space.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        // Проверяем команду завершения
        if (length == 0 && count == 0 ) {
            break;
        }

        // Проверяем корректность значений
        if (length < 1 || count < 0 || length >= field_size || count > field_size) {
            std::cout << "Error: ship length must be >= 1  and < field size and count >= 0. Repeat the entry.\n";
            continue;
        }

        // Сохраняем корректные данные
        all_ship_len.push_back(length);
        all_ship_count.push_back(count);
    }

    // Очищаем поток ввода от остатка, чтобы предотвратить пропуски
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Создаем ShipManager с помощью std::make_shared
    auto user_shipmanager = std::make_shared<ShipManager>(all_ship_count, all_ship_len);
    auto botik_shipmanager = std::make_shared<ShipManager>(all_ship_count, all_ship_len);

    user = std::make_shared<User>(user_field, botik_field, user_shipmanager);
    botik = std::make_shared<Bot>(botik_field, user_field, botik_shipmanager);

    destroy_bot_ship = 0;
    destroy_user_ship = 0;

}

void Game::UpdateGame() {
    // Обнуляем количество уничтоженных кораблей у пользователя
    destroy_user_ship = 0;
    botik->GetField().UpdateField();
    // Создаем новый менеджер кораблей
    std::vector<int> all_ships_length = {1, 2, 3, 4};
    std::vector<int> all_ships_count = {0, 0, 0, 0};

    auto all_ships = user->GetShipManager().GetAllShips();
    for (int i = 0; i<all_ships.size(); i++){
        // Извлекли длины кораблей
        auto len = all_ships[i].GetLength();
        all_ships_count[len-1]++;
        
    }
    auto new_ship_manager = std::make_shared<ShipManager>(all_ships_count, all_ships_length);
    // Обновляем состояние игрока-бота
    botik = std::make_shared<Bot>(botik->GetFieldPtr(), user->GetFieldPtr(), new_ship_manager);
    user->SetEnemyField(botik->GetFieldPtr());
    notify_observers();
}

void Game::StartGame(){
    std::cout << "\nGood luck, pirates :)" <<endl;
    if (user->GetField().IsEmpty()){
        // для начала перед боем нужно расставить корабли, как вы хотите это сделать - рандомно или сами
        std::cout << "Do you want to set up ships in random order or by yourself?\nEnter “0” if you want random and “1” if you want by yourself." << endl;
        while(true){
            try{
                int choise_placeship;
                std::cin >> choise_placeship;
                if (choise_placeship != 0 || choise_placeship !=1){
                    exception invalid_argument;
                } 
                if (choise_placeship == 0){
                    user->RandomPlaceShips();  
                    break;
                }else if (choise_placeship == 1){
                    user->PlaceShips(); 
                    break;
                } // Выход из цикла при успешной расстановке
            } catch (const std::invalid_argument& e) {
            std::cout << "Error: you have entered incorrect values. Try again. " << endl;
            }      
        }
    }
    
    std::cout << "The ships have been setted up." << endl;
    // У бота нет выбора, он ботик как бы
    botik->RandomPlaceShips();
    // Отрисовка полей
    notify_observers();
}

// Раунд: выбор атаки (или выбрать поражение), отрисовка полей
void Game::AttackRound() {
    bool validInput = false;
    while (!validInput) {
        try {
            // Ход пользователя
            int count_abil = user->GetAbilCount();
            std::cout << "Your move. Do you want to use the ability? (You have " << count_abil << " abilities) y/n" << std::endl;

            char choice;
            std::cin >> choice;

            // Проверка корректности ввода
            if (choice != 'y' && choice != 'n') {
                throw std::invalid_argument("Invalid input. Please enter 'y' or 'n'.");
            }

            // Если ввод корректный
            validInput = true;

            // Использование способности
            if (choice == 'y') {
                if (count_abil > 0) {
                    user->UsingAbilities();
                    std::cout << "Ability applied successfully." << std::endl;
                } else {
                    std::cout << "You have no abilities left." << std::endl;
                }
            }

            // Выполнение атаки
            notify_observers();
            if (user->AttackOpponent()) {
                destroy_user_ship++;
                std::cout << "You destroyed an enemy ship!" << std::endl;
            
            // Проверка окончания игры
                if (botik->GetCountShips() == destroy_user_ship) {
                    EndGame(1);
                }
            }

            // Ход бота
            std::cout << "Bot's move. Execution of the attack." << std::endl;
            if (botik->AttackOpponent()) {
                destroy_bot_ship++;
                std::cout << "Bot destroyed your ship!" << std::endl;

                // Проверка окончания игры
                if (user->GetCountShips() == destroy_bot_ship) {
                    EndGame(0);
                }
            }

            notify_observers();

        } catch (const std::invalid_argument& e) {
            std::cout << "Error: " << e.what() << " Try again." << std::endl;
            continue;
        } catch (const std::exception& e) {
            std::cout << "Unexpected error: " << e.what() << std::endl;
            break;
        }
    }
}

// Завершение игры
void Game::EndGame(int win_flag) {

    // Победа ботика - 0, победа юзера - 1
    if (win_flag == 0) {
        std::cout << "Bot has defeated you, ahaha. Maybe next time..." << std::endl;

        // Начинаем новую игру?
        char choise;
        while (true) {
            try {
                std::cout << "Do you want to start a new game? y/n: ";
                std::cin >> choise;

                // Проверяем корректность ввода
                if (choise != 'y' && choise != 'n') {
                    throw std::invalid_argument("Invalid input. Please enter 'y' or 'n'.");
                }

                // Если ввод корректный, выходим из цикла
                break;
            } catch (const std::invalid_argument& e) {
                std::cout << "Error: " << e.what() << " Try again." << std::endl;
            }
        }

        // Если пользователь хочет продолжить, то запускаем игру заново
        if (choise == 'y') {
            this->StartGame();
        } else {
            std::cout << "I hope you enjoyed this game. Have a nice day :)" << std::endl;
            exit(0);
        }
        
    } else {
        std::cout << "You've won! Yapi!" << std::endl;
        // Начинаем новую игру, но сохраняем положение кораблей у пользователя
        char choise;
        while (true) {
            try {
                std::cout << "Do you want to continue the game with your ships and an updated bot? y/n: ";
                std::cin >> choise;

                if (choise != 'y' && choise != 'n') {
                    throw std::invalid_argument("Invalid input. Please enter 'y' or 'n'.");
                }
                break;
            } catch (const std::invalid_argument& e) {
                std::cout << "Error: " << e.what() << " Try again." << std::endl;
            }
        }

        if (choise == 'y') {
            this->UpdateGame();
            this->StartGame();
        } else {
            std::cout << "I hope you enjoyed this game. Have a nice day :)" << std::endl;
            exit(0);
        }
    }
}

int Game::RetDestroyUserShip(){
    return destroy_user_ship;
}

int Game::RetDestroyBotShip(){
    return destroy_bot_ship;
}

User& Game::GetUser(){
    return *user;
}

void Game::SetUser(User& new_user){
    user = std::make_shared<User>(new_user);
}

Bot& Game::GetBot(){
    return *botik;
}

void Game::SetBot(Bot& new_bot){
    botik = std::make_shared<Bot>(new_bot);
}


//обновление дестрой шипов
void Game::SetDestrShips(int dest_user, int dest_bot){
    destroy_bot_ship = dest_bot;
    destroy_user_ship = dest_user;
}

// Сохранение игры
void Game::SaveGame(){
    game_state->SaveGame(user, botik, &destroy_user_ship, &destroy_user_ship);
    notify_observers();     
}

// Загрузка игры
void Game::LoadGame() {
    game_state->LoadGame(user, botik, &destroy_user_ship, &destroy_user_ship);
    notify_observers();    
}

// Оператор вывода
std::ostream& operator<<(std::ostream& out, Game& game) {
    out << game.RetDestroyUserShip() << '\n';
    out << game.RetDestroyBotShip() << '\n' ;
    out << game.GetUser(); // Предполагается, что для User уже реализован оператор вывода
    out << game.GetBot(); // Предполагается, что для Bot уже реализован оператор вывода

    return out;
}

// Оператор ввода
std::istream& operator>>(std::istream& in, Game& game) {
    int destroy_user_ship, destroy_bot_ship;
    
    // Вводим количество уничтоженных кораблей
    in >> destroy_user_ship;
    in >> destroy_bot_ship;
    game.SetDestrShips(destroy_user_ship, destroy_bot_ship);

    // Вводим объекты User и Bot
    in >> game.GetUser();  // Используем существующие объекты
    in >> game.GetBot();   // Используем существующие объекты

    return in;
}

