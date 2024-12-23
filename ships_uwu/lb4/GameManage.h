#ifndef GAMEMANAGE_H
#define GAMEMANAGE_H

#include <iostream>
#include "InputProcessor.h"
#include "Game.h"

// Шаблонный класс
template <typename InputProcessor>
// Класс управления игрой
class GameManage{
private:
    Game& game;
    InputProcessor& data;
public:
    GameManage(Game& new_game, InputProcessor& input_processor)
        : game(new_game), data(input_processor){}
    
    void CallCommand(){
        switch (data.get_command()) {
            case Command::Attack:
                std::cout << "You chose to attack the opponent's field.\n";
                game.AttackRound();
                break;
            case Command::ViewAbilities:
                std::cout << "The number of habilitation is being viewed..." << std::endl;
                std::cout << "You have " << game.GetUser().GetAbilCount() << " abilities in your manager.\n";
                break;
            case Command::SaveGame:
                std::cout << "Saving game...\n";
                game.SaveGame();
                std::cout << "Game saved successfully.\n";
                break;
            case Command::LoadGame:
                std::cout << "Loading saved game...\n";
                game.LoadGame();
                std::cout << "Game loaded successfully.\n";
                break;
            case Command::Exit:
                char choice;
                do {
                    std::cout << "Are you sure you want to get out? (y/n): ";
                    std::cin >> choice;
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
                        break;
                    }
                    choice = std::tolower(choice);
                    if (choice != 'y' && choice != 'n') {
                        std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
                    }
                } while (choice != 'y' && choice != 'n');

                if (choice == 'y' || choice == 'Y') {
                    std::cout << "Exiting the game...\n";
                    exit(0);
                }
                std::cout << "The game continues...\n"; 
                break;
            default:
                std::cout << "Unknown command cannot be executed.\n";
                break;
        }
    }
};

#endif //GAMEMANAGE_H