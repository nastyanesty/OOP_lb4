#ifndef COMMANDMAPPER_H
#define COMMANDMAPPER_H

#include <vector>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

// По умолчанию
enum class Command {Attack = 'a',
                    ViewAbilities = 'v', 
                    SaveGame = 's', 
                    LoadGame = 'l', 
                    Exit = 'q',
                    Unknown = 'u'};

// Класс комманд: установка по умолчанию, загрузка из файла, проверки, вывод доступных
class CommandMapper{
private:
    std::unordered_map<char, Command> key_to_command;
    std::unordered_map<Command, char> command_to_key;
    bool ValidateMapping(char key, Command command);

public:
    CommandMapper();
    void set_default_commands();
    void load_from_file(const std::string& filename);
    void check_full_mapping();
    Command string_to_command(const std::string& command_str);
    Command get_command(char key) const;
    void print_available_commands() const;
};

#endif //COMMANDMAPPER_H