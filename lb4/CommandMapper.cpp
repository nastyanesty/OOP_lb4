#include "CommandMapper.h"

// Проверка на дурака и дублирование
bool CommandMapper::ValidateMapping(char key, Command command) {
    if (key == '\0') {
        std::cerr << "Error: Key cannot be null or empty." << std::endl;
        return false;
    }

    if (key_to_command.find(key) != key_to_command.end()) {
        return false;
    }

    if (command_to_key.find(command) != command_to_key.end()) {
        return false;
    }

    return true;
}

// По умолчанию
CommandMapper::CommandMapper() { 
    set_default_commands(); 
}

// Если файлик пустой
void CommandMapper::set_default_commands(){
    key_to_command['a'] = Command::Attack;
    key_to_command['v'] = Command::ViewAbilities;
    key_to_command['s'] = Command::SaveGame;
    key_to_command['l'] = Command::LoadGame;
    key_to_command['q'] = Command::Exit;

    for (const auto& [key, cmd] : key_to_command){
        command_to_key[cmd] = key;
    }
}

// Загрузка из файла, если это возможно
void CommandMapper::load_from_file(const std::string& filename){
    std::ifstream file(filename);
    if (!file || !file.is_open() || file.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "The command file cannot be opened or is empty. The default commands are used." << std::endl;
        set_default_commands();
        return;
    }

    // Если возможно, очистка клавиш по умолчанию и загрузка
    key_to_command.clear();
    command_to_key.clear();
    char key;
    std::string command_str;
    while (file >> key >> command_str){
        Command command = string_to_command(command_str);
        if (ValidateMapping(key, command)){
            key_to_command[key] = command;
            command_to_key[command] = key;
        }else{
            std::cerr << "Invalid mapping in file. Skipping: " << key << " -> " << command_str << std::endl;
            continue;
        }        
    }
    check_full_mapping();
}

// Все ли клавиши заполнены
void CommandMapper::check_full_mapping() {
    std::vector<Command> all_commands = {Command::Attack, Command::ViewAbilities, Command::SaveGame,
                                            Command::LoadGame, Command::Exit};
    for (Command cmd : all_commands) {
        if (command_to_key.find(cmd) == command_to_key.end()) {
            std::cerr << "Base command is missing a key, it will be random." << std::endl;
            char key_char = rand();
            key_to_command[key_char] = cmd;
            command_to_key[cmd] = key_char;
        }
    }
}

// Очев
Command CommandMapper::string_to_command(const std::string& command_str){
    if (command_str == "Attack" || command_str == "attack") return Command::Attack;
    if (command_str == "ViewAbilities" || command_str == "viewabilities" || command_str == "view_abilities") return Command::ViewAbilities;
    if (command_str == "SaveGame" || command_str == "savegame" || command_str == "save_game") return Command::SaveGame;
    if (command_str == "LoadGame" || command_str == "loadgame" || command_str == "load_game") return Command::LoadGame;
    if (command_str == "Exit" || command_str == "exit") return Command::Exit;
    return Command::Unknown;
}

// Получаем команду
Command CommandMapper::get_command(char key) const{
    auto it = key_to_command.find(key);
    if (it != key_to_command.end()) {
        return it->second;
    }
    return Command::Unknown;
}

// Вывод доступных
void CommandMapper::print_available_commands() const {
    std::cout << "Available commands:" << std::endl;
    for (const auto& [key, cmd] : key_to_command) {
        std::cout << "Key: " << key << " -> Command: ";
        switch (cmd) {
            case Command::Attack: std::cout << "Attack"; break;
            case Command::ViewAbilities: std::cout << "ViewAbilities"; break;
            case Command::SaveGame: std::cout << "SaveGame"; break;
            case Command::LoadGame: std::cout << "LoadGame"; break;
            case Command::Exit: std::cout << "Exit"; break;
            default: std::cout << "Unknown";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}