#include "game/Game.h"
#include "lb4/GameManage.h"
#include "lb4/GameDisplay.h"

int main() {
    Game game;
    InputProcessor input_processor;
    GameManage<InputProcessor> game_manage(game, input_processor);
    FieldRendering field_render;
    GameDisplay<FieldRendering> game_display(game, field_render);
    
    game.StartGame();
    while (true) {
        try {
            game_manage.CallCommand();
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}