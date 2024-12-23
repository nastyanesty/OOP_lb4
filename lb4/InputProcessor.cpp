#include "InputProcessor.h"

// Загрузка из файла, если возможно
InputProcessor::InputProcessor(const std::string& new_filename){
    filename = new_filename;
    if (!filename.empty()){
        mapper.load_from_file(filename);
    }else{
        std::cout << "The file is empty. Default commands will be used." << std::endl;
    }   
};

// Считываем команду
Command InputProcessor::get_command() {
    std::string user_input;
    while (true) {
        try {
            std::cout << "Enter command: ";
            std::cin >> user_input;
            if (user_input.length() != 1) {
                throw std::invalid_argument("Invalid input. Please enter only a single character.");
            }
            char input = user_input[0];
            Command command = mapper.get_command(input);
            // Если команда не распознана
            if (command == Command::Unknown) {
                throw std::invalid_argument("The entered command is not recognized. Please enter a valid command.");
            }
            // Если команда норм бро
            return command;
        } catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            mapper.print_available_commands();
        }
    }
}
